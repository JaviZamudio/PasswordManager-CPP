#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

string encode(string target){
    for(int i = 0; i < target.length(); i++){
        if(target[i] != '\n') target[i] += 3;
    }
    return target;
}

string decode(string target){
    for(int i = 0; i < target.length(); i++){
        if(target[i] != '\n') target[i] -= 3;
    }
    return target;
}

void pause(){
    cout<<"\nPress any key to continue . . .";
    getch();
}

void wnSetup(string title = "PASSWORD MANAGER"){
	system("cls");
	cout<<"\n\t - - - "<<title<<" - - -\n\n";
}

void login(){
	string user = "";
    string pwd = "";

    ifstream ifile;
    ifile.open("sites.txt");

    getline(ifile,pwd);
    pwd = decode(pwd);

    ifile.close();

    if(pwd != ""){
        wnSetup("LOG-IN");
        cout<<"Write the master password: ";
        getline(cin,user);

        while(user != pwd){
            wnSetup("LOG-IN");
            cout<<"Incorrect >:(\n";
            cout<<"Write the wright password now!: ";
            getline(cin,user);
        }
    }
}