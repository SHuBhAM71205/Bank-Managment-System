#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "./account/Account.h"
#include "./employee/Employee.h"
#include "./filemanagment/File_M.h"
using namespace std;
void delay(int);
void home_page();
void authentication(const int);
void Manager_interface();
void Loan_officer_interface();
void Bank_representative_interface();

template <typename T4>
void authentication2(T4 &o, const string& filename, int role) 
{
    system("cls");
    int attempts = 0;
    int id;
    string password;

    while (attempts < 3) 
    {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> password;

        // Search for the employee in the specified file
        if (search_obj(filename, id, o)!=-1) 
        {
            if (o.check_psw(password)) 
            {
                cout << "Authentication successful." << endl;

                switch (role) 
                {
                    case 1: 
                        system("cls");
                        Manager_interface(); 
                        break;
                    case 2: 
                     system("cls");
                        Loan_officer_interface(); 
                        break;
                    case 3: 
                        system("cls");
                        
                        Bank_representative_interface(); 
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

int main() {
    // Manager_interface();
    system("cls");
    home_page();
    return 0;
}

void home_page() {
    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\tWELCOME" << endl;
    cout << "\nSelect your post:" << endl;
    cout << "1. Branch Manager" << endl;
    cout << "2. Loan Officer" << endl;
    cout << "3. Bank Representative" << endl;
    cout << "0. To exit the app" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            system("cls");
            authentication(1);
            break;
        case 2:
            system("cls");
            authentication(2);
            break;
        case 3:
            system("cls");
            authentication(3);
            break;
        case 0:
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            home_page();
            break;
    }
}

void authentication(int role) {
    system("cls");
    Branch_manager m;
    Loan_officer lo;
    Bank_representative br;
    string filename;

    switch (role) {
        case 1:
            system("cls");
            filename = "..\\FILES/Branch_manager.bin";
            authentication2<Branch_manager>(m, filename, role);
            break;
        case 2:
            system("cls");

            filename = "..\\FILES/Loan_officer.bin";
            authentication2<Loan_officer>(lo, filename, role);
            break;
        case 3:
            system("cls");

            filename = "..\\FILES/Bank_representative.bin";
            authentication2<Bank_representative>(br, filename, role);
            break;
        default:
            system("cls");
            
            cout << "Invalid role selected." << endl;
            home_page();
            break;
    }
}

void Manager_interface() {
    system("cls");
    Branch_manager m;
    int choice;
    position p;

    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\tWELCOME - Branch Manager" << endl;
    cout << "\nSelect an option:" << endl;
    cout << "1. Add an employee" << endl;
    cout << "2. Show all transactions" << endl;
    cout << "3. Fire an employee" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int empType;
            double salary;
            system("cls");
            cout << "Select Employee Type:" << endl;
            cout << "1. Branch Manager" << endl;
            cout << "2. Loan Officer" << endl;
            cout << "3. Bank Representative" << endl;
            cout << "Enter your choice: ";
            cin >> empType;

            switch (empType) {
                case 1: p = branch_manager; break;
                case 2: p = loan_officer; break;
                case 3: p = bank_representative; break;
                default:
                    cout << "Invalid choice." << endl;
                    Manager_interface();
                    return;
            }

            cout << "Enter salary: ";
            cin >> salary;
            m.add_employee(p, salary);
            cout << "Employee added successfully." << endl;
            break;
        }

        case 2:
            int c;
            system("cls");
            cout<<"\n\n\n\n\\nEnter 0 to go back\n"<<endl<<endl;
            m.show_all_trnsaction();
            cin>>c;
            if(c==0)
            {
                break;
           }
           else
           {
            Manager_interface();
           }

        case 3: {
            int empId;
            cout << "Enter the employee ID to fire: ";
            cin >> empId;
            m.fire_employee(empId);
            cout << "Employee removed successfully." << endl;
            cin>>empId;
            break;
        }

        case 0:
            system("cls");
            home_page();
            break;

        default:
            cout << "Invalid choice." << endl;
            system("cls");
            Manager_interface();
            break;
    }
    Manager_interface();
}

void Loan_officer_interface() {
    system("cls");
    Loan_officer lo;
    int choice;

    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\tWELCOME - Loan Officer" << endl;
    cout << "1. Add Loan" << endl;
    cout << "2. Show All Loans" << endl;
    cout << "3. Show Loan of a Specific Customer" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int custId;
            double loanAmount;
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Loan Amount: ";
            cin >> loanAmount;
            lo.provide_loan(custId, loanAmount);
            cout << "Loan added successfully." << endl;
            break;
        }

        case 2:
            //lo.show_all_loans();
            break;

        case 3: {
            int custId;
            cout << "Enter Customer ID: ";
            cin >> custId;
            //lo.show_customer_loan(custId);
            break;
        }

        case 0:
            home_page();
            break;

        default:
            cout << "Invalid choice." << endl;
            Loan_officer_interface();
            break;
    }
    Loan_officer_interface();
}

void Bank_representative_interface() {
    Bank_representative br;
    int choice;

    system("cls");
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\tWELCOME - Bank Representative" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Block Account" << endl;
    cout << "3. Remove Account" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            system("cls");
            br.create_account();
            cout << "Account created successfully." << endl;
            break;

        case 2: {
            system("cls");
            int accId;
            cout << "Enter Account ID to block: ";
            cin >> accId;
            br.block_account(accId);
            cout << "Account blocked successfully." << endl;
            break;
        }

        case 3: {
            system("cls");
            int accId;
            cout << "Enter Account ID to remove: ";
            cin >> accId;
            br.remove_account(accId);
            cout << "Account removed successfully." << endl;
            delay(10000000);
            break;
        }

        case 0:
        system("cls");
            home_page();
            break;

        default:
            system("cls");
            cout << "Invalid choice." << endl;
            Bank_representative_interface();
            break;
    }
    Bank_representative_interface(); 
}



void delay(int number_of_sec) {
    int milli_sec = 1000 * number_of_sec;
    clock_t start_time = clock();
    while (clock() < start_time + milli_sec) {
        // Busy wait
    }
}
