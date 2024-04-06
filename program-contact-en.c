#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

struct contact
{
    char name[100];
    char number[20];
    char email[100];
    char address[200];
} data;

void add();
void edit();
void search();
void view();
void remove_contact();
void remove_all();
void main_menu();
void line();
void exit_program();
char choice;

int main()
{
    system("COLOR 70");
    printf("\n|=======================================|");
    printf("\n|\t.::CONTACT ASSISTANT PROGRAM::.\t|");
    printf("\n|\t\tVersion 1.1\t\t|");
    printf("\n|                                       |");
    printf("\n|\t\tcreated by:\t\t|");
    printf("\n|                GROUP 1                |");
    printf("\n|\t    UDAYANA UNIVERSITY\t\t|");
    printf("\n|=======================================|\n\n");

    int i;
    printf("Starting Application ");
    char AppStarting[10] = ".....";
    for (i = 0; i < strlen(AppStarting); i++)
    {
        printf("%c", AppStarting[i]);
        Sleep(670);
    }
    system("cls");

    main_menu();
    return 0;
}

//-----------THIS IS THE MAIN MENU FUNCTION-------------
void main_menu()
{
    int menu = 1; // Initial menu selected
    int ch;       // To store the keyboard input

    do
    {
        system("cls");
        printf("\n============= Main Menu ==============\n\n");

        // Printing the menu with the current selection marked
        for (int i = 1; i <= 7; i++)
        {
            if (i == menu)
                printf("\t -> ");
            else
                printf("\t    ");

            switch (i)
            {
            case 1:
                printf("Add contact\n");
                break;
            case 2:
                printf("Edit contact\n");
                break;
            case 3:
                printf("Search contact\n");
                break;
            case 4:
                printf("View contacts\n");
                break;
            case 5:
                printf("Remove contact\n");
                break;
            case 6:
                printf("Remove all contacts\n");
                break;
            case 7:
                printf("Exit [ESC] \n");
                break;
            }
        }
        line();
        printf("\n");

        // Reading input from the user
        ch = getch();

        // Using up and down arrow for menu navigation
        if (ch == 224)
        {
            ch = getch();
            if (ch == 80)
            {
                if (menu < 7)
                    menu++;
                else
                    menu = 1;
            }
            else if (ch == 72)
            {
                if (menu > 1)
                    menu--;
                else
                    menu = 7;
            }
        }

        // Pressing enter to select a menu
        if (ch == 13)
        {
            switch (menu)
            { // select menu----
            case 1:
                system("cls");
                fflush(stdin); // clear buffer----
                add();
                break;
            case 2:
                system("cls");
                fflush(stdin);
                edit();
                break;
            case 3:
                system("cls");
                fflush(stdin);
                search();
                break;
            case 4:
                system("cls");
                fflush(stdin);
                view();
                break;
            case 5:
                system("cls");
                fflush(stdin);
                remove_contact();
                break;
            case 6:
                system("cls");
                fflush(stdin);
                remove_all();
                break;
            case 7:
                system("cls");
                exit_program();
                exit(0);
                break;
            }
        }
    } while (ch != 27); // Escape to exit the application
}

//-----------THIS IS THE FUNCTION TO ADD CONTACT-------------
void add()
{
    int i = 0;
    do
    {
        FILE *td;
        td = fopen("data.txt", "a");
        printf("\n============ Add Contact ============\n\n");

        printf("  Name: ");
        fflush(stdin);
        gets(data.name);
        for (i; i < strlen(data.name); i++)
        {
            data.name[i] = tolower(data.name[i]);
        }

        printf("  Number: ");
        fflush(stdin);
        scanf("%s", data.number);

        printf("  Email: ");
        fflush(stdin);
        scanf("%s", data.email);

        printf("  Address: ");
        fflush(stdin);
        gets(data.address);

        fwrite(&data, sizeof(struct contact), 1, td);
        printf("\nContact added successfully.....\n");
        fclose(td);

        printf("[1] Add another contact\n[0] Back to main menu\n ");
        choice = getch();
        system("cls");
    } while (choice == '1');
}

//-----------THIS IS THE FUNCTION TO VIEW CONTACTS-------------
void view()
{
    char select;
    do
    {
        FILE *td;
        td = fopen("data.txt", "r");
        printf("\n============= Contact List ==============");
        while (fread(&data, sizeof(struct contact), 1, td))
        {

            printf("\n\t Name : %s \n\t Number : %s\n\t Email : %s \n\t Address : %s \n", data.name, data.number, data.email, data.address);
            line();
        }

        fseek(td, 0, SEEK_END);
        if (ftell(td) == 0)
        {
            printf("\n\n\t..= Contacts are still empty =..\n");
        }

        fclose(td);

        printf("\n[0] Back to main menu\n ");
        select = getch();
        system("cls");
    } while (select != '0');
}

//-----------THIS IS THE FUNCTION TO SEARCH CONTACTS-------------
void search()
{
    char target[100];
    char *result;
    system("cls");

    do
    {
        int i = 0;
        fflush(stdin);
        FILE *td;
        td = fopen("data.txt", "r");
        printf("\n============= Search Contacts ==============\n");
        printf("\tEnter the contact you want to search for: ");
        gets(target);

        for (i; i < strlen(target); i++)
        {
            target[i] = tolower(target[i]);
            if (isspace(target[i]) || strlen(target) == 0)
            {
                line();
                printf("\n\t   Input is empty\n");
                line();
            }
            else
            {
                while (fread(&data, sizeof(struct contact), 1, td))
                {
                    result = strstr(data.name, target);
                    if (result)
                    {
                        printf("\n\t Name : %s \n\t Number : %s\n\t Email : %s\n \t Address : %s\n", data.name, data.number, data.email, data.address);
                        line();
                    }
                }
                if (!result)
                {
                    line();
                    printf("\n\t      No data\n");
                    line();
                }
            }
        }

        printf("\n[1] Search for another contact\n[0] Back to main menu\n ");
        choice = getch();
        fclose(td);
        system("cls");
    } while (choice == '1');
}

//-----------THIS IS THE FUNCTION TO REMOVE CONTACTS-------------
void remove_contact()
{
    do
    {
        fflush(stdin);
        FILE *td;
        FILE *tdcopy;
        char target[30];
        int found = 0;
        int result;

        td = fopen("data.txt", "r");
        tdcopy = fopen("copy.txt", "w");
        printf("\n============= Remove Contact =============\n");
        printf("Enter the name of the contact you want to remove: ");
        scanf("%[^\n]", &target);
        while (fread(&data, sizeof(struct contact), 1, td))
        {
            result = strcmp(target, data.name);
            if (result == 0)
            {
                found++;
            }
            else
            {
                fwrite(&data, sizeof(struct contact), 1, tdcopy);
            }
        }
        fclose(td);
        fclose(tdcopy);

        if (found)
        {
            remove("data.txt");
            rename("copy.txt", "data.txt");
            printf("\nContact successfully removed.....\n");
        }
        else
        {
            printf("\nContact name not found!\n");
        }

        printf("\n[1] Remove another contact\n[0] Back to main menu\n ");
        choice = getch();
        system("cls");

    } while (choice == '1');
}

//-----------THIS IS THE FUNCTION TO REMOVE ALL CONTACTS-------------
void remove_all()
{
    fflush(stdin);
    FILE *td;
    FILE *tdcopy;
    char target[30];
    int found = 0;
    int result;
    char select;
    td = fopen("data.txt", "r");
    tdcopy = fopen("copy.txt", "w");
    printf("\n========== Remove All Contacts ==========\n");
    printf("Are you sure you want to delete all contacts?\n[y] Delete All Contacts\n[n] Cancel\nChoice: ");
    scanf(" %c", &select);

    if (select == 'y')
    {

        while (fread(&data, sizeof(struct contact), 1, td))
        {

            fwrite(&data, sizeof(struct contact), 0, tdcopy);
        }

        fclose(td);
        fclose(tdcopy);

        remove("data.txt");
        rename("copy.txt", "data.txt");

        printf("\nAll contacts successfully deleted.....\n");
        printf("\n[0] Back to main menu\n ");
        scanf(" %c", &select);
        system("cls");
        if (select == '0')
        {
        }
    }
    else
    {
        main_menu();
    }
}

//-----------THIS IS THE FUNCTION TO EDIT CONTACTS-------------
void edit()
{

    do
    {
        fflush(stdin);
        FILE *td;
        FILE *tdcopy;
        char target[30];
        int found = 0;
        int result;

        td = fopen("data.txt", "r");
        tdcopy = fopen("copy.txt", "w");
        printf("\n============= Edit Contact ==============\n");
        printf("Enter the name of the contact you want to edit: ");
        scanf("%[^\n]", &target);
        while (fread(&data, sizeof(struct contact), 1, td))
        {
            result = strcmp(target, data.name);
            if (result == 0)
            {
                found++;
                printf("  New Name: ");
                fflush(stdin);
                gets(data.name);

                printf("  New Number: ");
                fflush(stdin);
                scanf("%s", data.number);

                printf("  New Email: ");
                fflush(stdin);
                scanf("%s", data.email);

                printf("  New Address: ");
                fflush(stdin);
                scanf("%s", data.address);
                fwrite(&data, sizeof(struct contact), 1, tdcopy);
            }
            else
            {
                fwrite(&data, sizeof(struct contact), 1, tdcopy);
            }
        }
        fclose(td);
        fclose(tdcopy);

        if (found)
        {
            remove("data.txt");
            rename("copy.txt", "data.txt");
            printf("\nContact successfully changed.....\n");
        }
        else
        {
            printf("\nContact name not found!");
        }
        printf("\n[1] Search for another contact\n[0] Back to main menu\n ");
        choice = getch();
        system("cls");

    } while (choice == '1');
}

//-----------THIS IS THE LINE FUNCTION-------------
void line()
{
    int i = 0;
    for (i; i < 40; i++)
    {
        printf("-");
    }
}

void exit_program()
{
    int i;
    printf("=========== Thank You ===========\n\nClosing the application");
    char AppStarting[10] = ".....";
    for (i = 0; i < strlen(AppStarting); i++)
    {
        printf("%c", AppStarting[i]);
        Sleep(500);
    }
    system("cls");
}
