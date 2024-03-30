#include "bank_functions.c"

// setting the cursor position

void gotoxy(int x, int y)
{

    for (int i = 0; i < y; i++)
        printf("\n");
    for (int j = 0; j < x; j++)
        printf(" ");
}

// main interface of bank management system

void main_interface()
{
    gotoxy(30, 10);
    printf("||WELCOME TO KESAR BANKING||");

    gotoxy(27, 2);
    printf("--> (1) Create Account");

    gotoxy(27, 1);
    printf("--> (2) Have a Account");

    gotoxy(27, 1);
    printf("--> (3) Exit");

    gotoxy(27, 2);
    printf("--> Select -- > ");
}

// registration form

void createAccount()
{
    char first_name[MAX], last_name[MAX],
        father_name[MAX], mother_name[MAX],
        password[MAX] = "pass", confirm_password[MAX] = "confirmpass";

    unsigned long long phone_number, money = 0;
    int id_value = 1;
    unsigned long long account_number;

    // ----------------------------------------
    system("cls");
    gotoxy(30, 10);
    printf("||WELCOME TO KESAR BANKING||");

    gotoxy(33, 2);
    printf("||Registration Form||");
    // ----------------------------------------

    FILE *fileptr;


    fileptr = fopen("documents\\Banking_Data.csv", "a+");

    if(fileptr == NULL)
    {
        system("mkdir documents");
        fileptr = fopen("documents\\Banking_Data.csv", "a+");
    }


    fseek(fileptr, 0, SEEK_END); // set cursor at end
    if (ftell(fileptr) == 0)     // return cursor position
    {
        fprintf(fileptr, "id,account_number,first_name,last_name,father_name,mother_name,phone_number,password,money,\n");
        id_value = 1;
    }
    else
    {
         id_value = getIdValue();
    }

    getuserinformation(first_name, last_name, father_name,
                       mother_name, password, confirm_password, &phone_number);

    account_number = ACC_NUM + id_value;

    while (money < MIN_MONEY || money > MAX_MONEY)
    {
        system("cls");
        gotoxy(30, 10);
        printf("How much money do you want to deposit intially ): - > ");
        scanf("%llu", &money);

        if (money < MIN_MONEY || money > MAX_MONEY)
        {

            gotoxy(30, 1);
            printf("Do you need minimum %d rupees bank balance!",MIN_MONEY);
            gotoxy(30,1);
            printf("and Maximum 9,99,99,99,999 rupees!!!");
            gotoxy(30, 2);
            printf("OTHER WISE PENALTY WILL CHARGE!!!");
            sleep(4);
        }
    }

    gotoxy(30, 10);
    printf("Your account have been created !!\n");
    gotoxy(30, 1);
    printf("Your account number is : %llu", account_number);
    gotoxy(30, 1);
    printf("Procced (press any key) : ");
    getch();

    fprintf(fileptr, "%d,%llu,%s,%s,%s,%s,%llu,%s,%llu      ,\n", id_value,
            account_number, first_name, last_name, father_name,
            mother_name, phone_number, password, money);

    fclose(fileptr);
}


void getdata(char *string)
{

    char c;
    int i = 0;

    fflush(stdin);
    while ((c = getchar()) != '\n')
        string[i++] = c;

    string[i] = '\0';
}


void getuserinformation(char *first_name, char *last_name, char *father_name,
                        char *mother_name, char *password,
                        char *confirm_password, unsigned long long *phone_number)
{
    gotoxy(33, 2);
    printf("First Name : - > ");
    getdata(first_name);

    gotoxy(33, 0);
    printf("Last Name : - > ");
    getdata(last_name);

    gotoxy(33, 0);
    printf("Father's Name : - > ");
    getdata(father_name);

    gotoxy(33, 0);
    printf("Mother's Name : - > ");
    getdata(mother_name);

    gotoxy(33, 0);
    printf("Phone Number : - > ");
    scanf("%lld", phone_number);

    while (strcmp(password, confirm_password) != 0)
    {
        gotoxy(33, 0);
        printf("Password : ");
        asterisk(password);

        gotoxy(33, 1);
        printf("Confirm Password : ");
        asterisk(confirm_password);
    }
}

void asterisk(char *pass)
{
    int i = 0;
    char c;
    while ((c = getch()) != '\r' && i <= 99)
    {
        if (c == '\b' && i == 0)
            continue;

        else if (c == '\b' && i >= 1)
            printf("\b \b", i--);

        else
            printf("*", pass[i++] = c);
    }
    pass[i] = '\0';
}

int getIdValue()
{
    char c;
    int count = 0;

    FILE *fileptr;

    fileptr = fopen("documents\\Banking_Data.csv", "r");

    while ((c = getc(fileptr)) != EOF)
    {
        if (c == '\n')
            count++;
    }
    fclose(fileptr);
    return count;
}

void sleep(int seconds)
{
    int milliseconds = seconds * 1000;

    time_t start_time = clock();
    while (start_time + milliseconds > clock());
}

void haveAccount()
{
    unsigned long long account_number;
    char password[MAX];
    int check_user = -1;
    char c;
    int counter = 0,select;

    system("cls");
    gotoxy(30, 10);
    printf("||WELCOME TO KESAR BANKING||");

    gotoxy(30, 1);
    printf("Account Number : ");
    scanf("%llu", &account_number);

    int id = checkAccountIsExist(account_number);
  
    if (id)
    {
        gotoxy(30, 0);
        printf("Password : ");
        asterisk(password);
        if(checkPassword(id,password))
        {
            while(1)
            {
                bank_menu();
                scanf("%d",&select);

                switch (select)
                {
                    case 1:
                        checkBalance(id);
                        break;

                    case 2:
                        depositMoney(id);
                        break;

                    case 3:
                        withDraw(id);
                        break;

                    case 4:
                        system("cls");
                        gotoxy(30, 10);
                        printf("Exit !!");
                        return;

                    default:
                        gotoxy(30, 1);
                        printf("Option is not available!!");
                        sleep(1);
                }
            }
        }
        else
        {
            gotoxy(30,1);
            printf("Wrong Password!!!");
            sleep(2);
        }
        
    }

    else
    {
        gotoxy(30, 10);
        printf("You donot have an Account!!!");
        sleep(2);
    }
}


int checkAccountIsExist(unsigned long long account_number)
{
    FILE *fileptr;
    int id = 0, counter = 0;
    char c;
    int previous = counter;

    fileptr = fopen("documents\\Banking_Data.csv", "r");

    while ((c = getc(fileptr)) != EOF)
    {
        if (counter > previous)
        {
            if (c == ',')
            {
                previous++;
                if ((account_number - ACC_NUM) == id)
                {
                    return id;
                }
                id = 0;
                continue;
            }
            id = (id * 10) + (c - 48);
        }
        if (c == '\n')
        {
            previous = counter;
            counter++;
        }
    }
    fclose(fileptr);

    return 0;
}

bool checkPassword(int id, char *password)
{
    char c;
    int counter = 0, comma_counter = 0, i = 0;

    FILE *fileptr;
    fileptr = fopen("documents\\Banking_Data.csv","r");

    while((c = getc(fileptr)) != EOF && counter <= id)
    {
        if(id == counter)
        {

            if(c == ',')
            {
                comma_counter++;
            }

            if(comma_counter == 7 && c != ',')
            {
                if(password[i++] != c)
                    return false;
            }  
                
        }
        if(c == '\n')
        {
            counter++;
        }
    }
    fclose(fileptr);
    return true;
}

void bank_menu()
{
    system("cls");
    gotoxy(30, 10);
    printf("||WELCOME TO KESAR BANKING||");

    gotoxy(27, 2);
    printf("--> (1) Check Balance");

    gotoxy(27, 1);
    printf("--> (2) Deposit Money");

    gotoxy(27,1);
    printf("--> (3) Withdraw Money");

    gotoxy(27,1);
    printf("--> (4) Exit");

    gotoxy(27, 2);
    printf("--> Select -- > ");  
}

void checkBalance(int id)
{
    char c;
    int counter = 0, comma_counter = 0, i = 0;

    FILE *fileptr;
    fileptr = fopen("documents\\Banking_Data.csv","r");

    gotoxy(30,1);
    printf("Balance : ");

    while((c = getc(fileptr)) != EOF && counter <= id)
    {
        if(id == counter)
        {

            if(c == ',')
            {
                comma_counter++;
            }

            if(comma_counter == 8 && c != '\n' && c != ',' && c != ' ')
            {
                printf("%c",c);
            }  
                
        }
        if(c == '\n')
        {
            counter++;
        }
    }
    fclose(fileptr);
    
    printf(" rupees");
    gotoxy(30,2);
    printf("Proceed (press any key) : ");
    getch();
}

//fetching money for deposit 

unsigned long long fetchMoney(int id)
{
    char c;
    int counter = 0, comma_counter = 0, i = 0;
    unsigned long long present_money = 0;

    FILE *fileptr;
    fileptr = fopen("documents\\Banking_Data.csv","r");

    while((c = getc(fileptr)) != EOF && counter <= id)
    {
        if(id == counter)
        {

            if(c == ',')
            {
                comma_counter++;
            }

            if(comma_counter == 8 && c != '\n' && c != ',' && c != ' ')
            {
                present_money = (present_money * 10) + (c - 48);
            }  
                
        }
        if(c == '\n')
        {
            counter++;
        }
    }
    fclose(fileptr);
    
    return present_money;
}

void depositMoney(int id)
{
    FILE *fileptr;
    fileptr = fopen("documents\\Banking_Data.csv","r+");

    unsigned long long deposit_money;
        
    char c;
    int counter = 0, comma_counter = 0, i = 0,position = 0;

    while((c = getc(fileptr)) != EOF && counter <= id)
    {
        if(id == counter)
        {
            if(comma_counter == 8)
            {
                break;
            }
            if(c == ',')
                comma_counter++;
        }

        if(c == '\n')
        {
            comma_counter = 0;
            counter++;
                // position++;
        }
        position++;
    }

    unsigned long long mo = fetchMoney(id);
    
    money_exceed:
        gotoxy(30,1);
        printf("Enter money : - > ");
        scanf("%llu",&deposit_money);

    if((unsigned long long)MAX_MONEY < (mo + deposit_money))
    {
        gotoxy(30,1);
        printf("Your money exceeded from %llu",MAX_MONEY);
        goto money_exceed;
    }

    fseek(fileptr,position+id,SEEK_SET);
    fprintf(fileptr,"%llu",mo+deposit_money);

    gotoxy(30,1);
    printf("Operation Done Successfully!!");
    sleep(2);
    fclose(fileptr);
}

void withDraw(int id)
{
    FILE *fileptr;
    fileptr = fopen("documents\\Banking_Data.csv","r+");

    unsigned long long withdraw_money;
    
    char c;
    int counter = 0, comma_counter = 0, i = 0,position = 0;

     while((c = getc(fileptr)) != EOF && counter <= id)
    {
        if(id == counter)
        {
            if(comma_counter == 8)
            {
                break;
            }
            if(c == ',')
                comma_counter++;
        }

        if(c == '\n')
        {
            comma_counter = 0;
            counter++;
            // position++;
        }
        position++;
    }  
    
    fseek(fileptr,position+id,SEEK_SET);
    char getstring[15];

    while((c = getc(fileptr)) != ' ')
    {
        getstring[i++] = c;
    }
    getstring[i] = '\0';

    fseek(fileptr,position+id,SEEK_SET);
    
    for(int m = 0; m < strlen(getstring); m++)
    {
        fprintf(fileptr," ");
    }

    unsigned long long mo = fetchMoney(id);

    money_decrease:
        gotoxy(30,1);
        printf("Enter money : - > ");
        scanf("%llu",&withdraw_money);

    if(MIN_MONEY > (long long)(mo - withdraw_money))
    {   gotoxy(30,1);
        printf("Your money decrease from %llu",MIN_MONEY);
        goto money_decrease;
    }

    fseek(fileptr,position+id,SEEK_SET);
    fprintf(fileptr,"%llu",mo-withdraw_money);

    gotoxy(30,1);
    printf("Operation Done!!");
    sleep(2);
    fclose(fileptr);
}