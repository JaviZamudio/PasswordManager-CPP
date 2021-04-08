#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <windows.h>

#include "./structs.h"
#include "./functions.h"

using namespace std;

void addSite(){
    Site site;

	//ask for the site info
    cout<<"Tell me the Name of the site: ";
	getline(cin, site.name);

    cout<<"Tell me the Email: ";
    getline(cin, site.accounts[site.nAccounts].email);
    if(site.accounts[site.nAccounts].email == "") 
        site.accounts[site.nAccounts].email = "none";

    cout<<"Tell me the Username: ";
    getline(cin, site.accounts[site.nAccounts].username);
    if(site.accounts[site.nAccounts].username == "") 
        site.accounts[site.nAccounts].username = "none";

    cout<<"Tell me the Password: ";
	getline(cin,site.accounts[site.nAccounts].password);
    if(site.accounts[site.nAccounts].password == "") 
        site.accounts[site.nAccounts].password = "none";

    cout<<"(Optional)Tell me the Description of the account: ";
    getline(cin,site.accounts[site.nAccounts].description);
    if(site.accounts[site.nAccounts].description == "") 
        site.accounts[site.nAccounts].description = "none";
    
    site.nAccounts++;

    ofstream file;
    file.open("./data.txt",ios::app);
    file<<encode(site.toString());
    file.close();

	//a menu of sites to consult from
	file.open("./sites.txt",ios::app);
    file<<encode(site.name)<<endl;
    file.close();

    cout<<"\nEverything saved";
}

void getAccounts(){
    //initialization file and site
    Site site;
    ifstream ifile;
    ifile.open("./data.txt");

    //asking for the site to find
    cout<<"Tell me the name of the site: ";
    getline(cin, site.name);

    //searching for the site
    string fileLine;    
    bool inSite = false;
    bool found = false;
    while(!ifile.eof()){
		//get a line to evaluate
		getline(ifile,fileLine);
		//if it matches the site needed
		if(decode(fileLine) == site.name){
			inSite = true;
			found = true;
		}

		//read the content in the Site
		while(inSite){
			//asign email
            getline(ifile, fileLine); 
            site.accounts[site.nAccounts].email = decode(fileLine).substr(7);
			//asign user name
            getline(ifile, fileLine); 
            site.accounts[site.nAccounts].username = decode(fileLine).substr(11);
            //asign password
            getline(ifile, fileLine);
            site.accounts[site.nAccounts].password = decode(fileLine).substr(10);
			//asign the descryption
			getline(ifile,fileLine);
            site.accounts[site.nAccounts].description = decode(fileLine.substr(13));

            //check if there's another site
            getline(ifile,fileLine);
            fileLine = decode(fileLine);

            if(fileLine == ""){
                inSite = false;
            }

			//increase the amount of sites
			site.nAccounts++;
		}
		
		//if we found and finished registering
		if(found){
			//stop searching
			break;
		}
    }

	//tell if we find something
    if(found){
        cout<<"\nSite Found!\n\n";
        cout<<site.toShow();
    }
    else{
        cout<<"\nThe site "<<site.name<<" doesn't exist";
    }

	//close file
    ifile.close();
}

void addAccount(){
	int nSites = 0;
	Site sites[50];
	string name;

	//ask for the site
	cout<<"Tell me the name of the site: ";
	getline(cin, name);

	//read file and get all sites
	ifstream ifile;
	ifile.open("./data.txt", ios::in);

	string fileLine;
	bool inSite;
	int pos = -1;
	while(!ifile.eof()){
		//site name
		getline(ifile,fileLine);
        if(decode(fileLine) == ""){
            break;
        }
       
        sites[nSites].name = decode(fileLine);
        inSite = true;

        //if is the site needed declare pos
        if(sites[nSites].name == name) pos = nSites;

        //while in the site, register accounts
        while(inSite){
            int nAccounts = sites[nSites].nAccounts;

            //account email
            getline(ifile, fileLine);
            sites[nSites].accounts[nAccounts].email = decode(fileLine).substr(7);
            //account username
            getline(ifile, fileLine);
            sites[nSites].accounts[nAccounts].username = decode(fileLine).substr(11);
            //account password
            getline(ifile, fileLine);
            sites[nSites].accounts[nAccounts].password = decode(fileLine).substr(10);
            //account description
            getline(ifile, fileLine);
            sites[nSites].accounts[nAccounts].description = decode(fileLine).substr(13);

            getline(ifile,fileLine);
            fileLine = decode(fileLine);
            
            if(fileLine == ""){
                inSite = false;
            }

            sites[nSites].nAccounts++;
        }
        nSites++;
	}

	ifile.close();

	//if site exists, ask for the account
    if(pos >= 0){
        cout<<"Tell me the Email: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].email);
        if(sites[pos].accounts[sites[pos].nAccounts].email == "")
        sites[pos].accounts[sites[pos].nAccounts].email = "none";
        
        cout<<"Tell me the Username: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].username);
        if(sites[pos].accounts[sites[pos].nAccounts].username == "")
        sites[pos].accounts[sites[pos].nAccounts].username = "none";

        cout<<"Tell me the Password: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].password);
        if(sites[pos].accounts[sites[pos].nAccounts].password == "")
        sites[pos].accounts[sites[pos].nAccounts].password = "none";
        
        cout<<"(Optional)Tell me the Description of the account: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].description);
        if(sites[pos].accounts[sites[pos].nAccounts].description == "")
        sites[pos].accounts[sites[pos].nAccounts].description = "none";
        
        sites[pos].nAccounts++;
        
        //rewrite the accounts txt file
        ofstream ofile;
        ofile.open("./data.txt");
        for(int i = 0; i < nSites; i++){
            ofile<<encode(sites[i].toString());
        }
        ofile.close();

        cout<<"\nEverything Saved :)";
    }
    else{
        cout<<"The site doesn't exist";
    }
}

void getAllSites(){
    ifstream ifile;
    ifile.open("./sites.txt");
    
    string fileLine = "";
    getline(ifile, fileLine);
    
    while (!ifile.eof())
    {
        fileLine = "";
        getline(ifile, fileLine);

        cout<<decode(fileLine)<<endl;
    }

    ifile.close();
}

void setPassword(){
    ifstream ifile;
    ifile.open("./sites.txt");

    //get the previos password
    string prevPwd = "";
    getline(ifile, prevPwd);
    prevPwd = decode(prevPwd);

    //getting the content of the sites
    string content = "";
    while(!ifile.eof()){
        string fileLine = "";
        getline(ifile, fileLine);

        if(fileLine != "")
            content += fileLine + "\n";
    }
    ifile.close();

    //ask for the the previous password
    if(prevPwd != ""){
        string user;
        cout<<"Write the previous password: ";
        getline(cin,user);

        while(user != prevPwd){
            wnSetup("SET/CHANGE PASSWORD");
            cout<<"Incorrect >:(\n";
            cout<<"Write the right password now!: ";
            getline(cin,user);
        }
    }

    //ask for the new password
    string newPwd = "";
    cout<<"Tell me the new password: ";
    getline(cin,newPwd);

    //write everything into the file
    ofstream ofile;
    ofile.open("./sites.txt");
    ofile<<encode(newPwd)<<endl;
    ofile<<content;
    ofile.close();
}
