#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "./filemanagment/File_M.h"
using namespace std;


typedef enum acc_type
{
    current,
    saving,
    salery,
    fix_deposit
} type;
typedef enum acc_status
{
    Active,
    Block
} status;

typedef struct user_data
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
    char password [20];
} user_data;

class Account
{
    int x;

protected:
    double balance;
    int account_no;
    user_data u1;
    type tp;
    status s;
    string created_at;
    

public:

    Account(type, double);
    Account();
    double display_bal();
    
};

class Saving : public Account
{
    int payment_limit;

public:
    Saving(double);
    Saving();
    void generate_pass_book();
    bool save();
    bool load(int acc_no);
    bool return_status();
    bool credit(double);
    bool debit(double);
    double check_bal();
    bool delete_acc();
    bool check_id(int);
    bool check_psw(string);
    void update_status(status);
    int get_acc_no();
    void show_trans();
    void update_passbook(double);
};

class Fix_deposit_account : public Account
{
    float maturation_period;
    float intrest_rate;
    double fix_amount;

public:
    Fix_deposit_account(float, float, double);
    Fix_deposit_account();
    void generate_pass_book();
    bool save();
    bool load(int acc_no);
    bool debit(double);
    void cal_rate();
    bool broke_fd();
    bool return_status();
    bool delete_acc();
    bool check_id(int);
    bool check_psw(string);
    void update_status(status);
    int get_acc_no();
    double check_bal();
    void show_trans();
    void update_passbook(double);
};

inline string getCurrentTimestamp();

bool update_to_trnsaction(double amt);

void userdata1(user_data &);
#endif // ACCOUNT_H
