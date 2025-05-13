#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
int global_function_identifier;
struct pass
{
    char surname[20];
    char name[20];
    char father_name[20];
    char mother_name[20];
    int b_day, b_month, b_year;
    char phone_number[11];
    char addharno[13];

} u1; // contain data of user
struct address
{
    char society_name[50];
    char town_name[20];
    char city_name[20];
    char pin[7];
} add;
struct uspd
{
    char password[20];
    char UserNAme[20];
    unsigned long long acc_no;
    long data_total_balence;
    long loan_amount;
} uspd; // contain password

// declaration of the function
void acc_crt();
void login();
void opration();
void add_money();
void record_adder(long);
void trans_money();
void check_balence();
void get_acc_history();
void total_balence(long);
void page_changer();
unsigned long long generate_unique_16_digit_number();
void reset_pass();
void loan();
void delay(int);
// main body
void main()
{
    int choice;
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tWELCOME\n");
    printf("Enter:\n1 --> creating new account\n2 -->login\n0 to quit application\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        acc_crt();
    }
    else if (choice == 2)
    {
        login();
    }
    else if (choice == 0)
    {
        exit(0);
    }
}
// function for account creation
void acc_crt()
{
    int pass_size = 0;
    global_function_identifier = 1;
    struct pass u1; // initialization of two function
    struct uspd uspd;
    uspd.acc_no = generate_unique_16_digit_number();
    // system("cls");//clear the screan
    printf("--------------------CREATE BANK ACCOUNT-------------------\n");
    // start to ttake data from user
    printf("Enter your Surname: ");
    scanf("%s", u1.surname);

    printf("Enter your name: ");
    scanf("%s", u1.name);

    printf("Enter your Father's name: ");
    scanf("%s", u1.father_name);

    printf("Enter your Mother's name: ");
    scanf("%s", u1.mother_name);

    printf("Enter your birthday:\n");

    printf("day:");
    scanf("%d", &u1.b_day);

    printf("month:");
    scanf("%d", &u1.b_month);

    printf("year:");
    scanf("%d", &u1.b_year);

    printf("enter your Address : \n");
    fflush(stdin);
    printf("society or Housename:");
    fgets(add.society_name, sizeof(add.society_name), stdin);

    printf("Town: ");
    fgets(add.town_name, sizeof(add.town_name), stdin);
    printf("City: ");
    fgets(add.city_name, sizeof(add.city_name), stdin);
    printf("Pincode: ");
    fgets(add.pin, sizeof(add.pin), stdin);
    printf("Enter your addhar card number:\n");
    int i = 0;
    do
    { // check the addhar no
        if (i >= 12)
        {
            printf("The addhar card number should be 12 digit longer");
        }
        scanf("%s", u1.addharno);
        i = i + 1;
    } while (strlen(u1.addharno) != 12);
    fflush(stdin);
    printf("Enter your phone number:\n");
    scanf("%s", u1.phone_number);
    fflush(stdin);
    printf("Enter your user name:\n");
    scanf("%s", uspd.UserNAme);
    printf("Enter your password:\n");
    scanf("%s", &uspd.password);
    FILE *pas = NULL;
    FILE *us = NULL;
    pas = fopen("password.txt", "w");
    us = fopen("username.txt", "w");
    fprintf(pas, "%s", uspd.password);
    fprintf(us, "%s", uspd.UserNAme);
    fclose(pas);
    fclose(us);

    printf("\nREMEMBER YOUR ACCOUNT NO\n");
    printf("ACCOUNT NO:%lld\n", uspd.acc_no);
    // adding data to file
    FILE *ptr = NULL;
    ptr = fopen("userdata.txt", "w"); //
    fprintf(ptr, "ACCOUNT NUMBER:%lld\n\n\n", uspd.acc_no);
    fprintf(ptr, "\t\t\t\t\tName:\t\t\t\t\%s %s %s\n\n", u1.surname, u1.name, u1.father_name);
    fprintf(ptr, "\t\t\t\t\tFather Name:\t\t%s\n\n", u1.father_name);
    fprintf(ptr, "\t\t\t\t\tMother Name:\t\t%s\n\n", u1.mother_name);
    fprintf(ptr, "\t\t\t\t\tBirthday:\t\t\t%d-%d-%d\n\n", u1.b_day, u1.b_month, u1.b_year);
    fprintf(ptr, "\t\t\t\t\tAddhar number:\t\t%s\n\n", u1.addharno);
    fprintf(ptr, "\t\t\t\t\tPhone number:\t\t%s\n\n", u1.phone_number);
    fprintf(ptr, "\t\t\t\t\tAddress:\n\t\t\t\t\t\t\t\t\t\t%s", add.society_name);
    fprintf(ptr, "\t\t\t\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t%s\t\t\t\t\t\t\t\t\t\t%s.\n", add.town_name, add.city_name, add.pin);
    fclose(ptr);

    FILE *ptrpd = NULL;
    ptrpd = fopen("psd.txt", "w");
    fprintf(ptrpd, "%s\n%s", uspd.UserNAme, uspd.password);
    fclose(ptrpd);
    printf("\nwait for few second\n");
    delay(5);
    printf("\n<<<<<<<<<<<<<<<<<<<<<<<ACCOUNT SUCESSFULLY CREATED>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("\nenter r to redireect to login page \n\n");
    // giving exit char
    char exit_value = getch();
    if (exit_value == 'r')
    {
        login();
    }
    else if (exit_value != 10)
    {
        main();
    }
}
void opration()
{
    global_function_identifier = 2;
    system("cls");
    int opr_choices;
    printf("_____________________________________________________________________________________________________________________________\n");
    printf("Enter:\n1 --> to add money to account\n2 --> to transfer money to other account\n3 --> to check the balence\n4 --> to get the accout histoy \n5 --> to apply for loan \n");
    scanf("%d", &opr_choices);
    switch (opr_choices)
    {
    case 1:
        add_money();
        break;
    case 2:
        trans_money();
        break;
    case 3:
        check_balence();
        break;
    case 4:
        get_acc_history();
        break;
    case 5:
        loan();
    default:
        exit(0);
        break;
    }
}
void login()
{
    global_function_identifier = 3;
    FILE *comp_psd = fopen("password.txt", "r");
    FILE *comp_us = fopen("username.txt", "r");

    if (comp_psd == NULL || comp_us == NULL)
    {
        printf("Error opening files.\n");
        exit(1);
    }

    char temp_username[20];
    char temp_password[20];

    printf("--------------------------------------------LOGIN--------------------------------------\n");

    printf("Enter your username: ");
    scanf("%s", temp_username);
    printf("Enter your password: ");
    scanf("%s", temp_password);

    char usernameFromFile[20];
    char passwordFromFile[20];

    while (fscanf(comp_us, "%s", usernameFromFile) != EOF && fscanf(comp_psd, "%s", passwordFromFile) != EOF)
    {
        if (strcmp(temp_username, usernameFromFile) == 0 && strcmp(temp_password, passwordFromFile) == 0)
        {
            fclose(comp_psd);
            fclose(comp_us);
            system("cls");
            opration(); // Exit the function after successful login
            return;     // Exit the function after successful login
        }
        else
        {
            printf("\nWRONG PASSWORD OR USERNAME, TRY AGAIN\n");
            printf("\nFORGOT PASSWORD? ENTER 1 TO RESET PASSWORD OR 2 TO TRY AGAIN\n");
            int j;
            scanf("%d", &j);
            if (j == 1)
            {
                system("cls");
                reset_pass();
            }
            else if (j == 2)
            {
                fseek(comp_us, 0, SEEK_SET);  // Reset file pointer to the beginning
                fseek(comp_psd, 0, SEEK_SET); // Reset file pointer to the beginning
                continue;                     // Allow the user to try again
            }
            else
            {
                printf("Invalid option.\n");
                break;
            }
        }
    }

    printf("\nYour app will be closed.\n");
    fclose(comp_psd);
    fclose(comp_us);
    exit(0);
}

void add_money()
{
    fflush(stdin);
    long money_cr;
    int tst = 0;
    printf("Enter the amount you want to add to you account in rs\n");
    do
    {
        if (tst != 0)
        {
            printf("Enter valid amount..\n");
        }
        scanf("%ld", &money_cr);
        if (money_cr <= 0)
        {
            tst = 1;
        }
        else
        {
            tst = 0;
        }

    } while (tst > 0);
    printf("Wait for few second\n");
    delay(5);
    printf("transfer sucessfull\n");
    total_balence(money_cr);
    record_adder(money_cr);
    page_changer();
}
void trans_money()
{
    long trans_amt, credited_user_acc_no;
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("Enter the user account no to whome money is credited:");
    scanf("%ld", &credited_user_acc_no);
    printf("Enter the amount to be transfered:");
    scanf("%ld", &trans_amt);
    printf("wait for few second\n");
    delay(5);
    long trans_amt1 = -1 * trans_amt;
    total_balence(trans_amt1);
    record_adder(trans_amt1);
    page_changer();
}
void check_balence()
{
    printf("_____________________________________________________________________________________________________________________________\n");
    printf("\t\t\t\tBalence in your account is: %ld\n", uspd.data_total_balence);
    if (uspd.data_total_balence < 0)
    {
        printf("IF THE MINIMUM BALENCE IS NOT MAINTAIN THEN CHARGE WILL BE APPLY..\n");
    }
    page_changer();
}
void get_acc_history()
{
    int helper = 0;
    char c, exit_char;
    FILE *ptr = NULL;
    ptr = fopen("userdata.txt", "r");
    while (c != EOF)
    {
        c = fgetc(ptr);
        printf("%c", c);
    }
    printf("\t\tREMAINING BALENCE:%ld", uspd.data_total_balence);
    page_changer();
}
void loan()
{

    printf("\n______________________________________________________loan____________________________________________\n");
    printf("Enter the amount to apply for loan: ");
    scanf("%ld", &uspd.loan_amount);
    total_balence(uspd.loan_amount);
    page_changer();
}
int sr_no_count = 1;
void record_adder(long x)
{
    time_t current_time;
    time(&current_time);

    current_time = time(NULL);
    char date_string[20];
    FILE *ptr = NULL;
    ptr = fopen("userdata.txt", "a");
    fprintf(ptr, "-----------------------------------------------------------------------------------------\n");
    while (sr_no_count < 1)
    {
        fprintf(ptr, "\t\t\t\t\t\t\t\tACCOUNT HISTORY\n");
        sr_no_count = sr_no_count + 1;
    }
    fprintf(ptr, ">\tDATE:\t\t%s", ctime(&current_time));
    fprintf(ptr, "\tAMOUNT CREDIT:       Rs.%ld\n\n", x);
    fclose(ptr);
}
void total_balence(long x)
{
    uspd.data_total_balence = uspd.data_total_balence + x;
}
void page_changer()
{
    int exit_int;
start:
    printf("\nEnter:\n1--> to go back \n2--> to go to home\n3-->to exit the app\n");
    scanf("%d", &exit_int);
    switch (exit_int)
    {
    case 1:
        switch (global_function_identifier)
        {
        case 1:
            system("cls");
            acc_crt();
            break;

        case 2:
            system("cls");
            opration();
            break;
        case 3:
            system("cls");
            login();
            break;
        }
    case 2:
        system("cls");
        main();
        break;
    case 3:
        system("cls");
        exit(0);
        break;

    default:
        printf("Invalid Input\n");
        goto start;
        break;
    }
}
unsigned long long generate_unique_16_digit_number()
{
    // Seed the random number generator
    srand(time(NULL));

    // Generate the most significant digit (1 to 9)
    unsigned long long cardnumber = rand() % 9 + 1;

    // Add 15 more digits (which can also be 0)
    for (int i = 0; i < 15; i++)
    {
        cardnumber *= 10;
        cardnumber += rand() % 10;
    }

    return cardnumber;
}
void reset_pass()
{
    FILE *pas = NULL;
    FILE *us = NULL;
    pas = fopen("password.txt", "w");
    us = fopen("username.txt", "r");
    char chk_username[20];
    char re_username[20];
    char re_pass[20];
    printf("Enter your username\n");
    scanf("%s", re_username);
    fscanf(us, "%s", re_pass);
    if (re_username == re_pass)
    {
        printf("\n\nEnter your password:\n");
        scanf("%s", re_pass);
        fprintf(pas, "%s", re_pass);

        printf("PASSWORD UPDATE SUCESSFULLY DONE>>>..");
        fclose(pas);
        fclose(us);
    }
    else
    {
        printf("This app will be closed in 5 second");
        delay(5);
        exit(0);
    }
    page_changer();
}
void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;

    // Store the start time
    clock_t start_time = clock();

    // Loop until the required time is achieved
    while (clock() < start_time + milli_seconds)
        ; // Empty loop
}
