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
    cout<<"Tell me the E-mail or Username: ";
    getline(cin, site.accounts[site.nAccounts].username);
    cout<<"Tell me the Password: ";
	getline(cin,site.accounts[site.nAccounts].password);
    cout<<"(Optional)Tell me the Description of the account: ";
    getline(cin,site.accounts[site.nAccounts].description);
    
    site.nAccounts++;

    ofstream file;
    file.open("./data.txt",ios::app);
    file<<encrypt(site.toString());
    file.close();

	//a menu of sites to consult from
	file.open("./sites.txt",ios::app);
    file<<site.name<<endl;
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
		if(decrypt(fileLine) == site.name){
			inSite = true;
			found = true;
		}

		//read the content in the Site
		while(inSite){
			//asign user name
            getline(ifile, fileLine); 
            site.accounts[site.nAccounts].username = decrypt(fileLine).substr(11);
            //asign password
            getline(ifile, fileLine);
            site.accounts[site.nAccounts].password = decrypt(fileLine).substr(10);
			//check if there's a description
			getline(ifile,fileLine);
			fileLine = decrypt(fileLine);

			if(fileLine != "-" && fileLine != ""){
				site.accounts[site.nAccounts].description = fileLine.substr(13);
				getline(ifile,fileLine);
				fileLine = decrypt(fileLine);
			}
			//if site is over . . .
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
        cout<<site.toString();
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
        if(decrypt(fileLine) == ""){
            break;
        }
       
        sites[nSites].name = decrypt(fileLine);
        inSite = true;

        //if is the site needed declare pos
        if(sites[nSites].name == name) pos = nSites;

        //while in the site, register accounts
        while(inSite){
            int nAccounts = sites[nSites].nAccounts;

            //account email
            getline(ifile, fileLine);
            sites[nSites].accounts[nAccounts].username = decrypt(fileLine).substr(11);
            //account password
            getline(ifile, fileLine);
            sites[nSites].accounts[nAccounts].password = decrypt(fileLine).substr(10);
            //check if there's a description
            getline(ifile, fileLine);
            fileLine = decrypt(fileLine);

            if(fileLine != "-" && fileLine != ""){
                sites[nSites].accounts[nAccounts].description = fileLine.substr(13);
                getline(ifile,fileLine);
                fileLine = decrypt(fileLine);
            }

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
        cout<<"Tell me the E-mail or Username: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].username);
        cout<<"Tell me the Password: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].password);
        cout<<"(Optional)Tell me the Description of the account: ";
        getline(cin, sites[pos].accounts[sites[pos].nAccounts].description);
        sites[pos].nAccounts++;
        
        //rewrite the accounts txt file
        ofstream ofile;
        ofile.open("./data.txt");
        for(int i = 0; i < nSites; i++){
            ofile<<encrypt(sites[i].toString());
        }

        cout<<"\nEverything Saved :)";
    }
    else{
        cout<<"The site doesn't exist";
    }

}