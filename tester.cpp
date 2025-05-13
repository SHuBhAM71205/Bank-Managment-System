#include<iostream>
#include<fstream>
#include"Account.h"
#include"File_M.h"
using namespace std;

int main()
{
    Saving s;
    ifstream i;
    i.open("FILES\\Saving.bin",ios::in);
    int id=1;
    load_from_bin("FILES\\Saving.bin",s,id);
    cout<<s.get_acc_no()<<endl;
    cout<<s.check_bal()<<endl;
    i.close();


}