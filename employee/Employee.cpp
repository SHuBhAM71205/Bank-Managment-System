#include "Employee.h"
using std::cin;
using std::cout;
using std::endl;


Employee::Employee(double salery, position p)
{
    x= return_no_of_acc_present("..\\FILES\\no_of_employee.txt");
    this->p = p;
    this->salery = salery;
    employee_id = ++x;
    update_no_of_acc("..\\FILES\\no_of_employee.txt",x);
    strcpy(joined_at, getCurrentTimestamp().c_str());
    cout<<endl<<endl<<"Ypur id number is:"<<" "<<employee_id<<endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    employee_data1(e1);
}

Employee::Employee()
{
}

//----------------------------------------------------------------------
Loan_officer::Loan_officer(double s) : Employee(s, loan_officer)
{
    create_obj_in_file<Loan_officer>("..\\FILES\\Loan_officer.bin",*this);
}

Loan_officer::Loan_officer()
{

}

void Loan_officer::provide_loan(int acc_no, double amt)
{
    Saving s;
    if (search_obj<Saving>("..\\FILES\\Saving.bin",acc_no,s))
    {
        if(s.return_status())
        {
            s.credit(amt);
        }
        else
        {
           cout<<"Account is inactive"<<endl<<"loan cant be allocated";
        }
    }
    else
    {
        cout<<"no account found or"<<endl;
    }
}

bool Loan_officer::save()
{
    save_to_bin<Loan_officer>("..\\FILES\\Loan_officer.bin", *this, employee_id);
}

bool Loan_officer::load(int emp_no)
{
    load_from_bin<Loan_officer>("..\\FILES\\Loan_officer.bin", *this, emp_no);
}

bool Loan_officer::check_psw(string psw)
{
    return psw == e1.password;
}
bool Loan_officer::check_id(int i)
{
    return i == employee_id;
}
//----------------------------------------------------------------------
Branch_manager::Branch_manager(double s) : Employee(s, branch_manager)
{
    create_obj_in_file<Branch_manager>("..\\FILES\\Branch_manager.bin",*this);
}

Branch_manager::Branch_manager() 
{

}

void Branch_manager::add_employee(position p, double salery)
{
    if (p == bank_representative)
    {
        Bank_representative b(salery);
        b.save();
    }
    else if (p == branch_manager)
    {
        Branch_manager m(salery);
        m.save();
    }
    else if (p == loan_officer)
    {
        Loan_officer l(salery);
        l.save();
    }
}

void Bank_representative::block_account(int id)
{
    Account a;
    Saving sa;
    Fix_deposit_account f;
    if(load_from_bin<Saving>("..\\FILES\\Saving.bin",sa,id))
    {
        sa.update_status(Block);
        save_to_bin<Saving>("..\\FILES\\Saving.bin",sa,id);
    }
    else if(load_from_bin<Fix_deposit_account>("..\\FILES\\Fix_deposit_account.bin",f,id))
    {
        f.update_status(Block);
        save_to_bin<Fix_deposit_account>("..\\FILES\\Fix_deposit_account.bin",f,id);
    }
    else
    {
        cout<<"Account not found"<<endl;
    }
}

void Branch_manager::fire_employee(int id)
{
    Employee e;
    Loan_officer lo;
    Bank_representative br;
    Branch_manager m;
    if(load_from_bin<Loan_officer>("..\\FILES\\Loan_officer.bin",lo,id))
    {
        deleteObject<Loan_officer>("..\\FILES\\Loan_officer.bin",id,lo);
    }
    else  if(load_from_bin<Bank_representative>("..\\FILES\\Bank_representative.bin",br,id))
    {
        deleteObject<Bank_representative>("..\\FILES\\Bank_representative.bin",id,br);
    }
    else if(load_from_bin<Branch_manager>("..\\FILES\\Branch_manager.bin",m,id))
    {
        deleteObject<Branch_manager>("..\\FILES\\Branch_manager.bin",id,m);
    }
    else
    {
        cout<<"Account doesnot exist"<<endl;
    }
}

void Bank_representative::remove_account(int id)
{
    
    Account a;
    Saving sa;
    Fix_deposit_account f;
    if(load_from_bin<Saving>("..\\FILES\\Saving.bin",sa,id))
    {
        sa.delete_acc();
    }
    else  if(load_from_bin<Fix_deposit_account>("..\\FILES\\Fix_deposit_account.bin",f,id))
    {
        f.delete_acc();
    }
    else
    {
        cout<<"Account doesnot exist"<<endl;
    }
}

void Branch_manager::show_all_trnsaction()
{
    ifstream i("..\\FILES\\TRANSCTION.txt");
    string s1;
    if(i.is_open())
    {
        while (!i.eof())
        {
            i>>s1;
            cout<<s1;
        }

    i.close();
    }
    else
    {
        FileException("..\\FILES\\TRANSCTION.txt");
    }
    
}

bool Branch_manager::save()
{
    save_to_bin<Branch_manager>("..\\FILES\\Branch_manager.bin", *this, employee_id);
}

bool Branch_manager::load(int emp_no)
{
    load_from_bin<Branch_manager>("..\\FILES\\Branch_manager.bin", *this, emp_no);
}

bool Branch_manager::check_psw(string psw)
{
    return psw == e1.password;
}
bool Branch_manager::check_id(int i)
{
    return (i == employee_id);
}
//----------------------------------------------------------------------
Bank_representative::Bank_representative(double s) : Employee(s, bank_representative)
{
    create_obj_in_file<Bank_representative>("..\\FILES\\Bank_representative.bin",*this);
}

Bank_representative::Bank_representative() 
{

}

void Bank_representative::create_account()
{
    string t1;
    type t;
    cout<<"Enter the type of the account you want to create : "<<endl;
    cin>>t1;
    if (t1=="saving"||t1=="Saving")
    {
        t=saving;
        Saving s(500);
        s.save();
        cout<<"Account created sucessfully"<<endl;
    }
    else if (t1=="Fix_deposit" || t1=="fix_deposit"  || t1=="Fix_Deposit" || t1=="FIX_DEPOSIT")

    {
        t=fix_deposit;
        float mp,ir;
        double fa;
        cout<<"Enter the maturity period of the account : "<<endl;
        cin>>mp;
        cout<<"Enter the interest rate of the account : "<<endl;
        cin>>ir;
        cout<<"Enter the fix  deposit amount : "<<endl;
        cin>>fa;
        Fix_deposit_account fd(mp,ir,fa);
        fd.save();
    }
    else{
        cout<<"Invalid account type"<<endl;
    }
}

bool Bank_representative::save()
{
    save_to_bin<Bank_representative>("..\\FILES\\Bank_representative.bin", *this, employee_id);
}

bool Bank_representative::load(int emp_no)
{
    load_from_bin<Bank_representative>("..\\FILES\\Bank_representative.bin", *this, emp_no);
}

bool Bank_representative::check_psw(string psw)
{
    return psw == e1.password;
}

bool Bank_representative::check_id(int i)
{
    return i == employee_id;
}

//----------------------------------------------------------------------
void employee_data1(employee_data & e)
{
    std::cout << "--------------------Add BANK EMPLOYEE-------------------\n";
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

        if (!strcmp(pass1 , pass2)) {
            strcpy(e.password,pass1); 
            break; 
        } else {
            std::cout << "Passwords do not match. Please try again." << std::endl;
        }
        
    } while (true); 
    
    std::cout << "Password set successfully!" << std::endl;
    cout<<pass1<<endl;
    cout<<"your password is:"<<endl;
    cout<<e.password<<endl;
}

string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}



char * Branch_manager::ret_pas_id(int & i,employee_data & u)
{
    i=employee_id;
    return e1.password;
}

int Branch_manager::get_acc_no()
{
    return employee_id;
}

int Loan_officer::get_acc_no()
{
    return employee_id;
}

int Bank_representative::get_acc_no()
{
    return employee_id;
}