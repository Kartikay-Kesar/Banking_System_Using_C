#include "functions\bank_function_declarations.c"

// main

int main()
{
    short select;

    while (1)
    {
        system("cls");
        main_interface();
        scanf("%hd", &select);

        switch (select)
        {
        case 1:
            createAccount();
            break;

        case 2:
            haveAccount();
            break;

        case 3:
            system("cls");
            gotoxy(30, 10);
            printf("Visit Again!!!");
            sleep(1);
            exit(0);

        default:
            gotoxy(30, 1);
            printf("Option is not available!!");
            sleep(1);
        }
    }
    return 0;
}