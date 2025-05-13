#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "./account/Account.h"
#include "./filemanagment/File_M.h"
using namespace std;


// Function declarations
void login();
void trans_money(int);
void reset_pass();
void delay(int);
void home_page();
void authentication(int);
void Saving_account_interface(int);
void Fd_account_interface(int);

template <typename T4>
void authentication2(T4 &o, const string &filename, int role)
{
    system("cls");
    int attempts = 0;
    int id;
    string password;

    while (attempts < 3)
    {
        cout << "Enter account no.: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> password;

        // Search for the employee in the specified file
        if (search_obj(filename,id, o) != -1)
        {
            if (o.check_psw(password))
            {
                cout << "Authentication successful." << endl;

                switch (role)
                {
                case 1:
                    system("cls");
                    Saving_account_interface(id);
                    break;
                case 2:
                    system("cls");
                    Fd_account_interface(id);
                    break;
                }
                return;
            }
            else
            {
                cout << "Invalid password." << endl;
            }
        }
        else
        {
            cout << "ID does not exist." << endl;
        }

        attempts++;
        cout << 3 - attempts << " attempts left." << endl;
    }

    cout << "All attempts completed. Try again later." << endl;
    home_page();
}

void home_page()
{
    int choice;
    cout << "------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\tWELCOME TO NET BANKING SYSTEM\n";
    cout << "Enter:\n1 --> Login\n0 --> Quit Application\n";
    cin >> choice;

    if (choice == 1)
    {
        login();
    }
    else
    {
        exit(0);
    }

}

int  main()
{
    home_page();
    return 0;
}

void authentication(int role)
{
    Saving s;
    Fix_deposit_account fd;

    system("cls");
    string filename;

    switch (role)
    {
    case 1:
        system("cls");
        filename = "..\\FILES\\Saving.bin";
        authentication2<Saving>(s, filename, role);
        break;
    case 2:
        system("cls");

        filename = "..\\FILES\\Fix_deposit_account.bin";
        authentication2<Fix_deposit_account>(fd, filename, role);
        break;
    default:
        system("cls");

        cout << "Invalid role selected." << endl;
        delay(7);
        login();
        break;
    }
}

void login()
{
    int acc_no;
    cout << "Enter your account number: ";
    cin >> acc_no;
    int c;
    cout << "Enter :\n 1 for saving account\n 2 for Fix Deposit Account " << endl;
    cin >> c;
    if (c == 1)
    {
        authentication(1);
    }
    else if (c == 2)
    {
        authentication(2);
    }
    else
    {
        cout << "Invalid choice";
        delay(7);
        login();
    }
}



void trans_money(int i)
{
    if (i == 1)
    {
        int acc;
        int amt;
        cout << "Enter the amount to be transfered" << endl;
        cin >> amt;
        cout << "Enter the beneficial account no." << endl;
        cin >> acc;
    }
    else if (i == 2)
    {
        cout << "transfer of money is not allow in fd account" << endl;
    }

}



void Saving_account_interface(int id)
{
    Saving s1;
    s1.load(id);
    if(search_obj("..\\FILES\\Saving.bin",id,s1)!=-1)
    {
        load_from_bin("..\\FILES\\Saving.bin",s1,id);
    }
    else{
        cout<<"error"<<endl;
    }
    char c;
    int i = 1;
    int sel;
    cout << "-----------------------------WELCOME------------------------------" << endl
         << endl;
    cout << "-----------------------------SAVING ACCOUNT-------------------------" << endl
         << endl;
    cout << "select::\n1 for  deposit\n2 for withdraw of money to wallet\n3 for check balance\n4 for show all tansaction\n5 for transfer money\n 0 to go back" << endl;
    cin >> sel;
    switch (sel)
    {
    case 1:
        double money_cr;
        cout << "Enter the amount you want to add: ";
        cin >> money_cr;

        if (money_cr > 0 )
        {
            s1.credit(money_cr);
            cout << "Money added successfully!\n";
        }
        else
        {
            cout << "Failed to add money.\n";
        }
        s1.save();
        cout<<"S";
        break;

    case 2:

        double amt;
        cout << "Enter the amount : " << endl;
        cin >> amt;
        s1.debit(amt);
        s1.display_bal();
        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        s1.save();
        break;

    case 3:

        cout << "Current balance: " << s1.display_bal() << "\n";
        if (s1.display_bal() < 0)
        {
            cout << "Low balance. Additional charges may apply.\n";
        }

        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        s1.save();
        break;

    case 4:

        system("cls");
        s1.show_trans();

        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        s1.save();
        break;

    case 5:

         int acc;
        double amt1;
        cout << "Enter the amount to be transfered" << endl;
        cin >> amt;
        cout << "Enter the beneficial account no." << endl;
        cin >> acc;
        s1.debit(amt);
        

        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        s1.save();
        break;
    
    case 0:

        home_page();
        break;
    }
    Saving_account_interface(s1.get_acc_no());
}

void Fd_account_interface(int id)

{
    Fix_deposit_account fda;
    fda.load(id);
    char c;
    int i = 2;
    cout << "select::\n1 for withdraw amount\n\n2 for check balance\n3 for show all tansaction\n4 to broke fd\n 0 to go back" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        double amt;
        cout << "Enter the amount : " << endl;
        cin >> amt;
        fda.debit(amt);
        fda.display_bal();
        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        fda.save();
        break;
    case 2:
        cout << "Current balance: " << fda.display_bal() << "\n";
        if (fda.display_bal() < 0)
        {
            cout << "Low balance. Additional charges may apply.\n";
        }

        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        fda.save();
        break;
    case 3:
        system("cls");
        fda.show_trans();

        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        fda.save();
        break;
    case 4:
       
        fda.broke_fd();
        cout << endl
             << endl;
        cout << "Press any key to continue...";
        cin >> c;
        break;
    case 0:
        home_page();
        break;
    }
    Fd_account_interface(fda.get_acc_no());
}

void delay(int number_of_sec)
{
    int milli_sec = 1000 * number_of_sec;
    clock_t start_time = clock();
    while (clock() < start_time + milli_sec)
        ;
}