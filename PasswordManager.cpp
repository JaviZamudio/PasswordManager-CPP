#include "./header.h"

int main(){
	system("title - - PASSWORD MANAGER - -");

	login();

    while(true){
        wnSetup();
        //show menu
        cout<<"\tWELCOME\n";
        cout<<"1) Get a Site\n";
        cout<<"2) Add a Site\n";
        cout<<"3) Add Account to a Site\n";
        cout<<"4) Show all Site names\n";
        cout<<"5) Set/Modify Password\n";
        cout<<"0) Exit\n";
        cout<<"Option: ";
        int option;
        cin>>option;
        fflush(stdin);

        //evaluate options
        switch(option){
            //add a site to the file
            case 1:{
                wnSetup("GET SITE");
				getAccounts();
                break;
            }
            case 2:{
                wnSetup("ADD SITE");
				addSite();
                break;
            }
            case 3:{
                wnSetup("ADD ACCOUNT TO A SITE");
                addAccount();
                break;
            }
            case 4:{
                wnSetup("ALL SITES");
                getAllSites();
                break;
            }
            case 5:{
                wnSetup("SET/CHANGE PASSWORD");
                setPassword();
                break;
            }
            case 0:{
                exit(1);
                break;
            }
            default:{
				wnSetup();
                cout<<"Write a right option . . .";
            }
        }
        pause();
    }

    getch();
    return 0;
}
    