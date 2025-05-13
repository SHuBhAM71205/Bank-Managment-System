#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <cstring>
#include<cctype>
#include <string>
#include <cstdio>
#include <string>
#include "../filemanagment/File_M.h"
#include "../account/Account.h"
using namespace std;

typedef enum position
{
    loan_officer,
    branch_manager,
    bank_representative
} position;

typedef struct employee_data
{
    char surname[20];
    char name[20];
    char father_name[20];
    char mother_name[20];
    int b_day, b_month, b_year;
    char phone_number[11];
    char addharno[13];
    struct address
    {
        char society_name[50];
        char town_name[20];
        char city_name[20];
        char pin[7];
    } add;
    char  password[20];

public:
} employee_data;

class Employee
{
protected:
    int x;
    int employee_id;
    employee_data e1;
    double salery;
    position p;
    char joined_at[10];

public:
    Employee(double, position);
    Employee();
};

class Loan_officer : public Employee
{
public:
    Loan_officer(double);
    Loan_officer();
    void provide_loan(int, double);
    bool save();
    bool load(int);
    bool check_psw(string);
    bool check_id(int);
    int get_acc_no();
};

class Branch_manager : public Employee
{

public:
    Branch_manager(double);
    Branch_manager();
    void fire_employee(int);
    void add_employee(position, double);
    void show_all_trnsaction();
    bool save();
    bool load(int);
    bool check_psw(string);
    bool check_id(int);
    char * ret_pas_id(int &,employee_data &);
    int get_acc_no();
};

class Bank_representative : public Employee
{
public:
    Bank_representative(double);
    Bank_representative();
    void create_account();
    bool save();
    bool load(int);
    bool check_psw(string);
    bool check_id(int);
    void block_account(int);
    void remove_account(int);
    int get_acc_no();
    
};

inline string getCurrentTimestamp();
void employee_data1(employee_data &);
#endif