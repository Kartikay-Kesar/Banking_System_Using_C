#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define MAX 50
#define MIN_MONEY 1000
#define MAX_MONEY 9999999999
#define ACC_NUM 300000000

typedef enum
{
    false, 
    true
} bool;

// bool create_column_header = false;

void gotoxy(int, int);
void sleep(int);
void main_interface();
void createAccount();
int getIdValue();
void getdata(char *);
void getuserinformation(char *, char *, char *, char *, char *, char *, unsigned long long *);
void asterisk(char *);
void haveAccount();

int checkAccountIsExist(unsigned long long);
bool checkPassword(int, char*);
void bank_menu();
void checkBalance(int);
unsigned long long fetchMoney(int);
void depositMoney(int);
void withDraw(int);
