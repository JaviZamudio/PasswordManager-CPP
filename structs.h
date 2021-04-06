#include <iostream>
using namespace std;

struct Account{
    string email = "";
    string username = "";
    string password = "";
    string description = "";

    string toString(){
        string result = "";
        result += "Email: " + email;
        result += "\nUser Name: " + username;
        result += "\nPassword: " + password;
        result += "\nDescription: " + description;

        return result;
    }

    string toShow(){
        string result = "";
        if(email != "none") result += "Email: " + email;
        if(username != "none") result += "\nUser Name: " + username;
        if(password != "none") result += "\nPassword: " + password;
        if(description != "none") result += "\nDescription: " + description;

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

    string toShow(){
        string result = name + "\n";

        for(int i = 0; i < nAccounts; i++){
            result += accounts[i].toShow();
			if(i < nAccounts - 1) result += "\n-";
			result += "\n";
        }

        result += "\n";

        return result;
    }
};