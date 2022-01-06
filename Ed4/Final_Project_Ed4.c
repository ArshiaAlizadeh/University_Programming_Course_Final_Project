#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

void loginMenu(void);
void signUp(void);
void login(void);
void mainMenu(void);
void income(void);
void expense(void);
void statisticsMenu(void);

char Name[30], LastName[40];

struct profile{
    char name[30];
    char last_name[40];
    char national_code[11];
    char mobile_number[12];
    char email[50];
    char password[30];
    struct profile *link;
};

struct date{
    char year[5];
    char month[3];
    char day[3];
};

struct income{
    char amount[10];
    char source[20];
    struct date date;
    char description[100];
    struct income *link;
};

struct expense{
    char amount[10];
    char item[30];
    struct date date;
    char description[100];
    struct expense *link;
};

typedef enum
{
    BLACK = 0, BLUE = 1, GREEN = 2,
    AQUA = 3, RED = 4, PURPLE =5,
    YELLOW = 6, WHITE = 7, GRAY = 8,
    LIGHT_BLUE = 9, LIGHT_GREEN = 10,
    LIGHT_AQUA = 11, LIGHT_RED = 12,
    LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15
} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground)
{
    Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    BufferInfo bufferInfo;
    if(!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
        return 0;
    Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
    SetConsoleTextAttribute(consoleHandle, color);
    return 1;
}

void main()
{
    loginMenu();
}

//This function displays the login page and goes to the next step based on the user's choice
void loginMenu(void)
{
    char choice;
    system("cls");
    printf("Welcome To ARSHIA Accounting Soft-ware\n\n");
    printf("1. Sign Up\n2. Login\n3. EXIT\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3')
    {
        system("cls");
        printf("Welcome To ARSHIA Accounting Soft-ware\n\n");
        printf("1. Sign Up\n2. Login\n3. EXIT\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        signUp();
    }
    else if(choice == '2')
    {
        login();
    }
        else if(choice == '3')
        {
            exit(0);
        }
}

//This function receives user  information and places it in file Profiles and goes to the next step based on the user's choice
void signUp(void)
{
    struct profile s;
    s.link = NULL;
    int i=0;
    char password[30], password2[30], ch, choice;
    system("cls");
    printf("--------------- Sign Up ---------------\n\n");
    printf("Enter your name: ");
    gets(s.name);
    printf("Enter your last name: ");
    gets(s.last_name);
    printf("Enter your national code: ");
    gets(s.national_code);
    printf("Enter your mobile number: ");
    gets(s.mobile_number);
    printf("Enter your email: ");
    gets(s.email);
    printf("Enter your password: ");
    while(1)
    {
        ch = getch();
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
        {
            password[i] = ch;
            i++;
            printf("*");
        }
        if(ch=='\b'&&i>=1)
        {
            printf("\b \b");
            i--;
        }
        if(ch=='\r')
        {
            password[i] = '\0';
            i = 0;
            printf("\n");
            break;
        }
    }
    printf("Re-enter your password: ");
    while(1)
    {
        ch = getch();
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
        {
            password2[i] = ch;
            i++;
            printf("*");
        }
        if(ch=='\b'&&i>=1)
        {
            printf("\b \b");
            i--;
        }
        if(ch=='\r')
        {
            password2[i] = '\0';
            i = 0;
            printf("\n");
            break;
        }
    }
    if(strcmp(password, password2) == 0)
    {
        strcpy(s.password, password);
    }
    else
    {
        while(strcmp(password, password2) != 0)
        {
            setTextColor(RED);
            printf("\nERROR: The password is incorrect! Try again!\n\n");
            setTextColor(WHITE);
            printf("Enter your password: ");
            while(1)
            {
                ch = getch();
                if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
                {
                    password[i] = ch;
                    i++;
                    printf("*");
                }
                if(ch=='\b'&&i>=1)
                {
                    printf("\b \b");
                    i--;
                }
                if(ch=='\r')
                {
                    password[i] = '\0';
                    i = 0;
                    printf("\n");
                    break;
                }
            }
            printf("Re-enter your password: ");
            while(1)
            {
                ch = getch();
                if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
                {
                    password2[i] = ch;
                    i++;
                    printf("*");
                }
                if(ch=='\b'&&i>=1)
                {
                    printf("\b \b");
                    i--;
                }
                if(ch=='\r')
                {
                    password2[i] = '\0';
                    i = 0;
                    printf("\n");
                    break;
                }
            }
        }
        strcpy(s.password, password);
    }
    FILE *f;
    f = fopen("Profiles.txt", "a");
    if(f != NULL)
    {
        fprintf(f, "%s", s.name);
        fputc('\n', f);
        fprintf(f, "%s", s.last_name);
        fputc('\n', f);
        fprintf(f, "%s", s.national_code);
        fputc('\n', f);
        fprintf(f, "%s", s.mobile_number);
        fputc('\n', f);
        fprintf(f, "%s", s.email);
        fputc('\n', f);
        fprintf(f, "%s", s.password);
        fputc('\n', f);
        fclose(f);
        setTextColor(GREEN);
        printf("\nSign Up completed successfully!\n\n");
        setTextColor(WHITE);
        printf("----------------------------------------\n\n");
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    printf("1. Main Menu\n2. EXIT\n0. Previous Page\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '0')
    {
        setTextColor(RED);
        printf("\nERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        strcpy(Name, s.name);
        strcpy(LastName, s.last_name);
        mainMenu();
    }
    else if(choice == '0')
    {
        loginMenu();
    }
        else
        {
            exit(0);
        }
}

//This function checks the user information and goes to the main menu if it is correct
void login(void)
{
    char choice;
    int exist = 0;
    struct profile *start, *end, *temp;
    FILE *f;
    f = fopen("Profiles.txt", "r");
    if(f != NULL)
    {
        temp = malloc(sizeof(struct profile));
        temp->link = NULL;
        fscanf(f, "%s", temp->name);
        fscanf(f, "%s", temp->last_name);
        fscanf(f, "%s", temp->national_code);
        fscanf(f, "%s", temp->mobile_number);
        fscanf(f, "%s", temp->email);
        fscanf(f, "%s", temp->password);
        start = end = temp;
        while(feof(f) == 0)
        {
            temp = malloc(sizeof(struct profile));
            temp->link = NULL;
            fscanf(f, "%s", temp->name);
            fscanf(f, "%s", temp->last_name);
            fscanf(f, "%s", temp->national_code);
            fscanf(f, "%s", temp->mobile_number);
            fscanf(f, "%s", temp->email);
            fscanf(f, "%s", temp->password);
            end->link = temp;
            end = temp;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    int i=0;
    char userName[12], password[31], ch;
    system("cls");
    printf("--------------- Login ---------------\n\n");
    setTextColor(RED);
    printf(">>> ATTENTION: \"User name\" is your national code by default <<<\n\n");
    setTextColor(WHITE);
    printf("Enter your user name: ");
    gets(userName);
    temp = start;
    while(temp != NULL)
    {
        if(strcmp(temp->national_code, userName) == 0)
        {
            exist = 1;
            break;
        }
        temp = temp->link;
    }
    if(exist == 1)
    {
        printf("Enter your password: ");
        while(1)
        {
            ch = getch();
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
            {
                password[i] = ch;
                i++;
                printf("*");
            }
            if(ch=='\b'&&i>=1)
            {
                printf("\b \b");
                i--;
            }
            if(ch=='\r')
            {
                password[i] = '\0';
                i = 0;
                printf("\n");
                break;
            }
        }
        if(strcmp(temp->password, password) == 0)
        {
            strcpy(Name, temp->name);
            strcpy(LastName, temp->last_name);
            mainMenu();
        }
        else
        {
            while(strcmp(temp->password, password) != 0)
            {
                setTextColor(RED);
                printf("\nERROR: The password is incorrect! Try again!\n\n");
                setTextColor(WHITE);
                printf("Enter your password: ");
                while(1)
                {
                    ch = getch();
                    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
                    {
                        password[i] = ch;
                        i++;
                        printf("*");
                    }
                    if(ch=='\b'&&i>=1)
                    {
                        printf("\b \b");
                        i--;
                    }
                    if(ch=='\r')
                    {
                        password[i] = '\0';
                        i = 0;
                        printf("\n");
                        break;
                    }
                }
            }
            mainMenu();
        }
    }
    else
    {
        setTextColor(RED);
        printf("\nERROR: User name not found!\n\n");
        setTextColor(WHITE);
        printf("1. Try again!\n2. Sign Up\n3. EXIT\n\n");
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
        while(choice != '1' && choice != '2' && choice != '3')
        {
            setTextColor(RED);
            printf("\nERROR: The number entered is invalid! Try again!\n\n");
            setTextColor(WHITE);
            printf(">>Please Enter Your Choice: ");
            choice = getchar();
            fflush(stdin);
        }
        if(choice == '1')
        {
            login();
        }
        else if(choice == '2')
        {
            signUp();
        }
            else
            {
                exit(0);
            }
    }
}

//This function displays the main page and goes to the next step based on the user's choice
void mainMenu(void)
{
    char choice;
    system("cls");
    printf("--------------- Main Menu ---------------\n\n");
    printf("1. Incomes\n2. Expenses\n3. Statistics\n4. Settings\n5. Sign Out\n6. EXIT\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6')
    {
        system("cls");
        printf("--------------- Main Menu ---------------\n\n");
        printf("1. Incomes\n2. Expenses\n3. Statistics\n4. Settings\n5. Sign Out\n6. EXIT\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        income();
    }
    else if(choice == '2')
    {
        expense();
    }
        else if(choice == '3')
        {
            statisticsMenu();
        }
            else if(choice == '4')
            {
                printf("Go to the Settings");
            }
                else if(choice == '5')
                {
                    loginMenu();
                }
                    else
                    {
                        exit(0);
                    }
}

//This function receives income  information and places it in file Incomes and goes to the next step based on the user's choice
void income(void)
{
    char choice, fileName[80];
    struct income i;
    i.link = NULL;
    system("cls");
    printf("--------------- Income ---------------\n\n");
    printf("Please specify your income type:\n\n");
    printf("1. Programming Salary\n2. YARANEH\n3. Pocket Money\n4. University Grant\n\n0. Main Menu\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0')
    {
        system("cls");
        printf("--------------- Income ---------------\n\n");
        printf("Please specify your income type:\n\n");
        printf("1. Programming Salary\n2. YARANEH\n3. Pocket Money\n4. University Grant\n\n0. Main Menu\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        strcpy(i.source, "Programming Salary");
    }
    else if(choice == '2')
    {
        strcpy(i.source, "YARANEH");
    }
        else if(choice == '3')
        {
            strcpy(i.source, "Pocket Money");
        }
            else if(choice == '4')
            {
                strcpy(i.source, "University Grant");
            }
                else
                {
                    mainMenu();
                }
    printf("\nPlease specify the amount of Income(In term of Rials): ");
    gets(i.amount);
    printf("Please specify the date of Income(YYYY/MM/DD): ");
    scanf("%4s/%2s/%2s", i.date.year, i.date.month, i.date.day);
    fflush(stdin);
    printf("Please enter the description: ");
    gets(i.description);
    strcat(fileName, "Incomes_");
    strcat(fileName, Name);
    strcat(fileName, LastName);
    strcat(fileName, ".txt");
    FILE *f;
    f = fopen(fileName, "a");
    if(f != NULL)
    {
        fprintf(f, "%s", i.amount);
        fputc('\n', f);
        fprintf(f, "%s", i.source);
        fputc('\n', f);
        fprintf(f, "%s", i.date.year);
        fputc('\n', f);
        fprintf(f, "%s", i.date.month);
        fputc('\n', f);
        fprintf(f, "%s", i.date.day);
        fputc('\n', f);
        fprintf(f, "%s", i.description);
        fputc('\n', f);
        fclose(f);
        setTextColor(GREEN);
        printf("\nSuccessfully recorded!\n\n");
        setTextColor(WHITE);
        printf("----------------------------------------\n\n");
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    printf("1. Another Income\n2. Main Menu\n3. EXIT\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3')
    {
        setTextColor(RED);
        printf("\nERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        income();
    }
    else if(choice == '2')
    {
        mainMenu();
    }
        else
        {
            exit(0);
        }
}

//This function receives expense  information and places it in file Expenses and goes to the next step based on the user's choice
void expense(void)
{
    char choice, fileName[80];
    struct expense e;
    e.link = NULL;
    system("cls");
    printf("--------------- Expense ---------------\n\n");
    printf("Please specify your expense item:\n\n");
    printf("1. Clothing\n2. Transportation\n3. Tuition Fees\n4. Entertainment\n5. Mobile and Internet Bill\n6. Medical Expenses\n7. Donate to Charity\n\n0. Main Menu\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7' && choice != '0')
    {
        system("cls");
        printf("--------------- Expense ---------------\n\n");
        printf("Please specify your expense item:\n\n");
        printf("1. Clothing\n2. Transportation\n3. Tuition Fees\n4. Entertainment\n5. Mobile and Internet Bill\n6. Medical Expenses\n7. Donate to Charity\n\n0. Main Menu\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        strcpy(e.item, "Clothing");
    }
    else if(choice == '2')
    {
        strcpy(e.item, "Transportation");
    }
        else if(choice == '3')
        {
            strcpy(e.item, "Tuition Fees");
        }
            else if(choice == '4')
            {
                strcpy(e.item, "Entertainment");
            }
                else if(choice == '5')
                {
                    strcpy(e.item, "Mobile and Internet Bill");
                }
                    else if(choice == '6')
                    {
                        strcpy(e.item, "Medical Expenses");
                    }
                        else if(choice == '7')
                        {
                            strcpy(e.item, "Donate to Charity");
                        }
                            else
                            {
                                mainMenu();
                            }
    printf("\nPlease specify the amount of Expense(In term of Rials): ");
    gets(e.amount);
    printf("Please specify the date of Expense(YYYY/MM/DD): ");
    scanf("%4s/%2s/%2s", e.date.year, e.date.month, e.date.day);
    fflush(stdin);
    printf("Please enter the description: ");
    gets(e.description);
    strcat(fileName, "Expenses_");
    strcat(fileName, Name);
    strcat(fileName, LastName);
    strcat(fileName, ".txt");
    FILE *f;
    f = fopen(fileName, "a");
    if(f != NULL)
    {
        fprintf(f, "%s", e.amount);
        fputc('\n', f);
        fprintf(f, "%s", e.item);
        fputc('\n', f);
        fprintf(f, "%s", e.date.year);
        fputc('\n', f);
        fprintf(f, "%s", e.date.month);
        fputc('\n', f);
        fprintf(f, "%s", e.date.day);
        fputc('\n', f);
        fprintf(f, "%s", e.description);
        fputc('\n', f);
        fclose(f);
        setTextColor(GREEN);
        printf("\nSuccessfully recorded!\n\n");
        setTextColor(WHITE);
        printf("----------------------------------------\n\n");
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    printf("1. Another Expense\n2. Main Menu\n3. EXIT\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3')
    {
        setTextColor(RED);
        printf("\nERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        expense();
    }
    else if(choice == '2')
    {
        mainMenu();
    }
        else
        {
            exit(0);
        }
}

void statisticsMenu(void)
{
    char choice;
    system("cls");
    printf("--------------- Statistics Menu ---------------\n\n");
    printf("1. Account Balance\n2. Incomes Statistics\n3. Expenses Statistics\n\n0. Main Menu\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '0')
    {
        system("cls");
        printf("--------------- Statistics Menu ---------------\n\n");
        printf("1. Account Balance\n2. Incomes Statistics\n3. Expenses Statistics\n\n0. Main Menu\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        printf("Go to the Account Balance!");
    }
    else if(choice == '2')
    {
        printf("Go to the Incomes Statistics!");
    }
        else if(choice == '3')
        {
            printf("Go to the Expenses Statistics!");
        }
            else if(choice == '0')
            {
                mainMenu();
            }
}