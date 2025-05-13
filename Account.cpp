#include "Account.h"
#include <cstring>
using std::cin;
using std::cout;
using std::endl;


Account::Account(type t, double bal = 0)
{
    cout<<"1";
    s = Active;

    tp = t;
    balance=bal;
    created_at = getCurrentTimestamp();
    x=return_no_of_acc_present("FILES\\no_of_account.txt");
    account_no = ++x;
    cout<<account_no;
    update_no_of_acc("FILES\\no_of_account.txt",x);
    string s="FILES\\passbook\\" +to_string(account_no) + "p.txt";
    cout<<"passbook created"<<endl;
    ofstream o(s);
    o.close();
    cout<<endl<<endl<<"Ypur account number is:"<<" "<<account_no<<endl;
    userdata1(u1);
}
Account::Account()
{
    cout<<"in default construtor";
}


double Account::display_bal()
{
    return balance;
}

//--------------------------------------------------------------------------------------------

Saving::Saving(double bal) : Account(saving)
{
    s=Active;
    payment_limit = 10000;
    generate_pass_book();
    create_obj_in_file<Saving>("FILES\\Saving.bin", *this);
}

Saving::Saving() : Account()
{
}

bool Saving::credit(double amt)
{
    if (s == Active)
    {
        if (amt > 0 && amt <= payment_limit)
        {
            balance = balance + amt;
            cout<<balance;
            std::cout << "Transaction Successful" << endl;
            cout<<"your account bal :"<<balance<<endl;
            update_passbook(amt);
            update_to_trnsaction(amt);
            cout<<"c";
            bool b=save();
            cout<<b<<endl;
            return true;
        }
        else
        {
            cout << "Insufficent bal,Extra  charge may be apply." << endl;
            return false;
        }
    }
    else
    {
        cout << "Your Account has been fressed" << endl;
        return false;
    }
}

bool Saving::debit(double amt)
{
    if (s == Active)
    {
        if (amt > 0 && amt <= balance)
        {
            balance -= amt;
            std::cout << "Transaction Successful" << endl;
            update_passbook(-1 * amt);
            update_to_trnsaction(-1 * amt);
            return true;
        }
        else
        {
            std::cout << "your account balance is insufficient & negative balance in saving accont not allow" << endl;
            return false;
        }
    }
    else
    {
        cout << "Your account has been freesed" << endl;
        return false;
    }
}

double Saving::check_bal()
{
    return balance;
}

void Saving::generate_pass_book()
{
    string file_name = "FILES\\passbook\\"+to_string(account_no) + "p.txt";
    ofstream o;
    o.open(file_name, ios::app);
    o << "ACCOUNT NUMBER: " << account_no << "\n\n\n";
    o << "\t\t\t\t\tName:\t" << u1.surname << " " << u1.name << " " << u1.father_name << "\n\n";
    o << "\t\t\t\t\tFather Name:\t\t" << u1.father_name << "\n\n";
    o << "\t\t\t\t\tMother Name:\t\t" << u1.mother_name << "\n\n";
    o << "\t\t\t\t\tBirthday:\t\t\t" << u1.b_day << "-" << u1.b_month << "-" << u1.b_year << "\n\n";
    o << "\t\t\t\t\tAadhar number:\t\t" << u1.addharno << "\n\n";
    o << "\t\t\t\t\tPhone number:\t\t" << u1.phone_number << "\n\n";
    o << "\t\t\t\t\tAddress:\n\t\t\t\t\t\t\t\t\t\t" << u1.add.society_name << "\n";
    o << "\t\t\t\t\t\t\t\t\t\t" << u1.add.town_name << "\n\t\t\t\t\t\t\t\t\t\t" << u1.add.city_name << "\n\t\t\t\t\t\t\t\t\t\t" << u1.add.pin << ".\n";
    o << endl
      << endl
      << "--------------------------------------------------------------------------------------------------------------------" << endl;
    o.close();
}

bool Saving::save()
{
    return save_to_bin<Saving>("FILES\\Saving.bin", *this, account_no);

    // updateObject<Saving>("FILES\\Saving.bin",account_no,*this);
}

bool Saving::load(int acc_no)
{
    return load_from_bin<Saving>("FILES\\Saving.bin", *this, acc_no);
}

bool Saving::return_status()
{
    if (s == Active)
    {
        return true;
    }
    return false;
}

bool Saving::delete_acc()
{
    return deleteObject<Saving>("FILES\\Saving.bin", account_no, *this);
}

bool Saving::check_psw(const string psw)
{
    return psw == u1.password;
}
bool Saving::check_id(int i)
{
    return (i == account_no);
}

void  Saving::update_status(status s1)
{
    s=s1;
}

//--------------------------------------------------------------------------------------------

Fix_deposit_account::Fix_deposit_account(float mp, float ir, double fa) : Account(fix_deposit), maturation_period(mp), intrest_rate(ir), fix_amount(fa)
{
    s=Active;
    create_obj_in_file<Fix_deposit_account>("FILES\\Fix_deposit_account.bin", *this);
    generate_pass_book();
}

Fix_deposit_account::Fix_deposit_account() : Account()
{
}

bool Fix_deposit_account::debit(double amt)
{
    if (s == Active)
    {
        if (amt > 0 && amt <= balance)
        {
            balance -= amt;
            std::cout << "Transaction Successful" << endl;
            update_passbook(-1 * amt);
            update_to_trnsaction(-1 * amt);
            return true;
        }
        else
        {
            std::cout << "your account balance is insufficient & negative balance in saving accont not allow" << endl;
            return false;
        }
    }
    else
    {
        cout << "Your account has been freesed" << endl;
        return false;
    }
}

void Fix_deposit_account::cal_rate()
{
    balance = (intrest_rate * (balance + fix_amount)) / 100;
}

bool Fix_deposit_account::broke_fd()
{
    balance = fix_amount;
    fix_amount = 0;
    intrest_rate = 0;
}

void Fix_deposit_account::generate_pass_book()
{
    string file_name = "FILES\\passbook\\"+to_string(account_no) + "p.txt";
    ofstream o;
    o.open(file_name, ios::app);
    o << "ACCOUNT NUMBER: " << account_no << "\n\n\n";
    o << "\t\t\t\t\tName:\t\t\t\t" << u1.surname << " " << u1.name << " " << u1.father_name << "\n\n";
    o << "\t\t\t\t\tFather Name:\t\t" << u1.father_name << "\n\n";
    o << "\t\t\t\t\tMother Name:\t\t" << u1.mother_name << "\n\n";
    o << "\t\t\t\t\tBirthday:\t\t\t" << u1.b_day << "-" << u1.b_month << "-" << u1.b_year << "\n\n";
    o << "\t\t\t\t\tAadhar number:\t\t" << u1.addharno << "\n\n";
    o << "\t\t\t\t\tPhone number:\t\t" << u1.phone_number << "\n\n";
    o << "\t\t\t\t\tAddress:\n\t\t\t\t\t\t\t\t\t\t" << u1.add.society_name << "\n";
    o << "\t\t\t\t\t\t\t\t\t\t" << u1.add.town_name << "\t\t\t\t\t\t\t\t\t\t" << u1.add.city_name << "\t\t\t\t\t\t\t\t\t\t" << u1.add.pin << ".\n";
    o << endl
      << endl
      << "--------------------------------------------------------------------------------------------------------------------" << endl;
    o.close();
}

bool Fix_deposit_account::save()
{
    return save_to_bin<Fix_deposit_account>("FILES\\Fix_deposit_account.bin", *this, account_no);
}

bool Fix_deposit_account::load(int acc_no)
{
    return load_from_bin<Fix_deposit_account>("FILES\\Fix_deposit_account.bin", *this, acc_no);
}

bool Fix_deposit_account::return_status()
{
    if (s == Active)
    {
        return true;
    }
    return false;
}

double Fix_deposit_account::check_bal()
{
    return balance;
}

void  Fix_deposit_account::show_trans()
{
    string file_name = "FILES\\passbook\\"+to_string(account_no) + "p.txt";
    ifstream i;
    i.open(file_name, ios::in);
    char c;
    while (!i.eof())
    {
        i.get(c);
        cout<<c;
    }
    i.close();
}

void  Saving::show_trans()
{
    string file_name = "FILES\\passbook\\"+to_string(account_no) + "p.txt";
    ifstream i;
    i.open(file_name, ios::in);
    char c;
    while (!i.eof())
    {
        i.get(c);
        cout<<c;
    }
    i.close();
}

bool Fix_deposit_account::delete_acc()
{
    return deleteObject<Fix_deposit_account>("FILES\\Fix_deposit_account.bin", account_no, *this);
}

bool Fix_deposit_account::check_psw(const string psw)
{
    return psw == u1.password;
}
bool Fix_deposit_account::check_id(int i)
{
    return i == account_no;
}

void  Fix_deposit_account::update_status(status s1)
{
    s=s1;
}
//--------------------------------------------------------------------------------------------

string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void userdata1(user_data & e)
{
    std::cout << "--------------------Add Account Detail-------------------\n";
    // start to ttake data from user
    std::cout << "Enter your Surname: ";
    std::cin >> e.surname;

    std::cout << "Enter your name: ";
    std::cin >> e.name;

    std::cout << "Enter your Father's name: ";
    std::cin >> e.father_name;

    std::cout << "Enter your Mother's name: ";
    std::cin >> e.mother_name;

    std::cout << "Enter your birthday:\n";

    std::cout << "day:";
    std::cin >> e.b_day;

    std::cout << "month:";
    std::cin >> e.b_month;

    std::cout << "year:";
    std::cin >> e.b_year;

    std::cout << "enter your Address : \n";
    std::cout << "1>society or Housename:";
    std::cin.getline(e.add.society_name, 100);
    std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    std::cout << "2>Town: ";
    std::cin.getline(e.add.town_name, 100);
    std::cout << "3>City: ";
    std::cin.getline(e.add.city_name, 20);
    std::cout << "4>Pincode:";
    std::cin.getline(e.add.pin, 20);
    std::cout << "5>Enter your addhar card number:\n";
    int i = 0;
    char pass1[20],pass2[20];
    do
    { // check the addhar no
        if (i >= 12)
        {
            std::cout << "The addhar card number should be 12 digit longer";
        }
        std::cin >> e.addharno;
        i = i + 1;
    } while (strlen(e.addharno) != 12);
    std::cout << "Enter your phone number:\n";
    std::cin >> e.phone_number;
    do
    {
        std::cout << "Enter the password: ";
        std::cin >> pass1;
        std::cout << "Enter password again: ";
        std::cin >> pass2;

        if (!strcmp(pass1, pass2)) {
            strcpy(e.password,pass1);
            break; 
        } else {
            std::cout << "Passwords do not match. Please try again." << std::endl;
        }
        
    } while (true); 
    std::cout << "Password set successfully!" << std::endl;
    cout<<" Enter the min balance  to be credited to your account"<<endl;
    

}
bool update_to_trnsaction(double amt)
{
     ofstream o("FILES\\TRANSACTIONS.txt", ios::app);
    if (!o) return false;  // Check if file opened successfully
    
    o << "Transaction amount: " << amt << " on " << getCurrentTimestamp() << endl;
    o.close();
    return true;
}


int Fix_deposit_account::get_acc_no()
{
    
    return account_no;
}


int Saving::get_acc_no()
{
    return account_no;
}

void Saving::update_passbook(double amt)
{
    string file_name ="FILES\\passbook\\" +to_string(account_no) + "p.txt";
    ofstream o;
    o.open(file_name, ios::app);
    o << "\nDATE::\t\t\t\t" << getCurrentTimestamp() << endl;
    if (amt < 0)
    {
        o << "\tAMOUNT DEBIT::\t\t\t" << -1 * amt << endl;
    }
    else
    {
        o << "AMOUNT CREDIT::\t\t\t" << amt << endl;
    }
    o << "REMAIN_AMT:" <<"\t\t\t" <<balance << endl
      << endl;
    o << "-------------------------------------------------------------------------------";
    o.close();   
}

void Fix_deposit_account::update_passbook(double amt)
{
    string file_name ="FILES\\passbook\\" +to_string(account_no) + "p.txt";
    ofstream o;
    o.open(file_name, ios::app);
    o << "\n\tDATE::\t\t\t\t" << getCurrentTimestamp() << endl;
    if (amt < 0)
    {
        o << "\tAMOUNT DEBIT::\t\t" << -1 * amt << endl;
    }
    else
    {
        o << "AMOUNT CREDIT::\t\t\t" << amt << endl;
    }
    o << "REMAIN_AMT:" <<"\t\t\t\t" <<balance << endl
      << endl;
    o << "-------------------------------------------------------------------------------";
    o.close(); 
}
