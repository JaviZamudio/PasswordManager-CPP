#include <iostream>
using namespace std;

struct Account{
    string username = "";
    string password = "";
    string description = "";

    string toString(){
        string result = "User Name: " + username + "\n";
        result += "Password: " + password;
        if(description != "") result += "\nDescription: " + description;

        return result;
    }
};

struct Site
{
    string name = "";
    Account accounts[10];
    int nAccounts = 0;

    string toString(){
        string result = name + "\n";

        for(int i = 0; i < nAccounts; i++){
            result += accounts[i].toString();
			if(i < nAccounts - 1) result += "\n-";
			result += "\n";
        }

        result += "\n";

        return result;
    }
};