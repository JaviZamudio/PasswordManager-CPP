#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void pause(){
    cout<<"\nPress any key to continue . . .";
    getch();
}

void wnSetup(string title = "PASSWORD MANAGER"){
	system("cls");
	cout<<"\n\t - - - "<<title<<" - - -\n\n";
}

void login(string pwd = "admin"){
	string user = "";

	wnSetup("LOG-IN");
	cout<<"Write the password: ";
	getline(cin,user);

	while(user != pwd){
		wnSetup("LOG-IN");
		cout<<"Incorrect >:(\n";
		cout<<"Write the wright password now!: ";
		getline(cin,user);
	}
}

string encrypt(string target){
    for(int i = 0; i < target.length(); i++){
        if(target[i] != '\n') target[i] += 3;
    }
    return target;
}

string decrypt(string target){
    for(int i = 0; i < target.length(); i++){
        if(target[i] != '\n') target[i] -= 3;
    }
    return target;
}