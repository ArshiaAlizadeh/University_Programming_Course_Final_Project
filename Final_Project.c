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
void accountBalance(void);
void incomesStatisticsMenu(void);
void totalIncomesYear(void);
void totalIncomesInterval(void);
void expensesStatisticsMenu(void);
void totalExpensesYear(void);
void totalExpensesInterval(void);

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
        fwrite(&s, sizeof(struct profile), 1, f);
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
    printf("1. Main Menu\n2. EXIT\n0. Login Menu\n\n");
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
        fread(temp, sizeof(struct profile), 1, f);
        start = end = temp;
        while(feof(f) == 0)
        {
            temp = malloc(sizeof(struct profile));
            temp->link = NULL;
            fread(temp, sizeof(struct profile), 1, f);
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
            temp = end = start;
            while(temp != NULL)
            {
                end = temp->link;
                free(temp);
                temp = end;
            }
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
            strcpy(Name, temp->name);
            strcpy(LastName, temp->last_name);
            temp = end = start;
            while(temp != NULL)
            {
                end = temp->link;
                free(temp);
                temp = end;
            }
            mainMenu();
        }
    }
    else
    {
        while(temp != NULL)
        {
            end = temp->link;
            free(temp);
            temp = end;
        }
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

//This function receives income information and places it in file Incomes and goes to the next step based on the user's choice
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
        fwrite(&i, sizeof(struct income), 1, f);
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

//This function receives expense information and places it in file Expenses and goes to the next step based on the user's choice
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
        fwrite(&e, sizeof(struct expense), 1, f);
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

//This function displays the statistics page and goes to the next step based on the user's choice
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
        accountBalance();
    }
    else if(choice == '2')
    {
        incomesStatisticsMenu();
    }
        else if(choice == '3')
        {
            expensesStatisticsMenu();
        }
            else if(choice == '0')
            {
                mainMenu();
            }
}

//This function displays the user account balance and goes to the next step based on the user's choice
void accountBalance(void)
{
    system("cls");
    printf("--------------- Account Balance ---------------\n\n");
    char incomesFileName[80] = "Incomes_";
    strcat(incomesFileName, Name);
    strcat(incomesFileName, LastName);
    strcat(incomesFileName, ".txt");
    struct income *startIncome, *endIncome, *tempIncome;
    FILE *f;
    f = fopen(incomesFileName, "r");
    if(f != NULL)
    {
        tempIncome = malloc(sizeof(struct income));
        tempIncome->link = NULL;
        fread(tempIncome, sizeof(struct income), 1, f);
        startIncome = endIncome = tempIncome;
        while(feof(f) == 0)
        {
            tempIncome = malloc(sizeof(struct income));
            tempIncome->link = NULL;
            fread(tempIncome, sizeof(struct income), 1, f);
            endIncome->link = tempIncome;
            endIncome = tempIncome;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    char expensesFileName[80] = "Expenses_";
    strcat(expensesFileName, Name);
    strcat(expensesFileName, LastName);
    strcat(expensesFileName, ".txt");
    struct expense *startExpense, *endExpense, *tempExpense;
    f = fopen(expensesFileName, "r");
    if(f != NULL)
    {
        tempExpense = malloc(sizeof(struct expense));
        tempExpense->link = NULL;
        fread(tempExpense, sizeof(struct expense), 1, f);
        startExpense = endExpense = tempExpense;
        while(feof(f) == 0)
        {
            tempExpense = malloc(sizeof(struct expense));
            tempExpense->link = NULL;
            fread(tempExpense, sizeof(struct expense), 1, f);
            endExpense->link = tempExpense;
            endExpense = tempExpense;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    int amount, sumIncomes=0, sumExpenses=0, accountBalance;
    tempIncome = startIncome;
    while(tempIncome != NULL)
    {
        amount = atoi(tempIncome->amount);
        sumIncomes += amount;
        tempIncome = tempIncome->link;
    }
    tempExpense = startExpense;
    while(tempExpense != NULL)
    {
        amount = atoi(tempExpense->amount);
        sumExpenses += amount;
        tempExpense = tempExpense->link;
    }
    accountBalance = sumIncomes - sumExpenses;
    setTextColor(AQUA);
    printf(">> ");
    setTextColor(WHITE);
    printf("Account Balance: ");
    if(accountBalance > 0)
    {
        setTextColor(GREEN);
        printf("%d", accountBalance);
        setTextColor(WHITE);
        printf(" Rials\n\n");
    }
    else if(accountBalance < 0)
    {
        setTextColor(RED);
        printf("%d", accountBalance);
        setTextColor(WHITE);
        printf(" Rials\n\n");
        setTextColor(RED);
        printf("ATTENTION: The negative sign means that your expenses have been more than your incomes!\n\n");
        setTextColor(WHITE);
    }
    else
    {
        printf("%d Rials\n\n", accountBalance);
    }
    printf("-----------------------------------------------\n\n");
    tempIncome = endIncome = startIncome;
    while(tempIncome != NULL)
    {
        endIncome = tempIncome->link;
        free(tempIncome);
        tempIncome = endIncome;
    }
    tempExpense = endExpense = startExpense;
    while(tempExpense != NULL)
    {
        endExpense = tempExpense->link;
        free(tempExpense);
        tempExpense = endExpense;
    }
    char choice;
    printf("1. Statistics Menu\n2. EXIT\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2')
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
        statisticsMenu();
    }
    else
    {
        exit(0);
    }
}

//This function displays the incomes statistics menu and goes to the next step based on the user's choice
void incomesStatisticsMenu(void)
{
    char choice;
    system("cls");
    printf("--------------- Incomes Statistics Menu ---------------\n\n");
    printf("1. The total incomes of a certain year\n2. The total incomes in a history interval\n3. The total of a certain type of income in a history interval\n");
    printf("4. The ratio of different incomes to each other\n5. The details of incomes in a history interval\n6. The most income in a history interval\n");
    printf("7. Search in the incomes description field\n\n0. Statistics Menu\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7' && choice != '0')
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
        totalIncomesYear();
    }
    else if(choice == '2')
    {
        totalIncomesInterval();
    }
        else if(choice == '3')
        {
            printf("Go to the total of a certain type of income in a history interval");
        }
            else if(choice == '4')
            {
                printf("Go to the ratio of different incomes to each other");
            }
                else if(choice == '5')
                {
                    printf("Go to the details of incomes in a history interval");
                }
                    else if(choice == '6')
                    {
                        printf("Go to the most income in a history interval");
                    }
                        else if(choice == '7')
                        {
                            printf("Go to the search in the incomes description field");
                        }
                            else
                            {
                                statisticsMenu();
                            }
}

//This function displays the total incomes of a certain year and goes to the next step based on the user's choice
void totalIncomesYear(void)
{
    int len, exist=0, sumIncomes=0, amount;
    char year[5], choice;
    system("cls");
    printf("--------------- Incomes Statistics ---------------\n\n");
    printf("Please enter your desired year: ");
    gets(year);
    len = strlen(year);
    while(len != 4)
    {
        system("cls");
        printf("--------------- Incomes Statistics ---------------\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered must contain 4 digits!\n\n");
        setTextColor(WHITE);
        printf("Please enter your desired year: ");
        gets(year);
        len = strlen(year);
    }
    char incomesFileName[80] = "Incomes_";
    strcat(incomesFileName, Name);
    strcat(incomesFileName, LastName);
    strcat(incomesFileName, ".txt");
    struct income *startIncome, *endIncome, *tempIncome;
    FILE *f;
    f = fopen(incomesFileName, "r");
    if(f != NULL)
    {
        tempIncome = malloc(sizeof(struct income));
        tempIncome->link = NULL;
        fread(tempIncome, sizeof(struct income), 1, f);
        startIncome = endIncome = tempIncome;
        while(feof(f) == 0)
        {
            tempIncome = malloc(sizeof(struct income));
            tempIncome->link = NULL;
            fread(tempIncome, sizeof(struct income), 1, f);
            endIncome->link = tempIncome;
            endIncome = tempIncome;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    tempIncome = startIncome;
    while(tempIncome != NULL)
    {
        if(strcmp(tempIncome->date.year, year) == 0)
        {
            exist = 1;
            break;
        }
        tempIncome = tempIncome->link;
    }
    if(exist == 1)
    {
        tempIncome = startIncome;
        while(tempIncome != NULL)
        {
            if(strcmp(tempIncome->date.year, year) == 0)
            {
                amount = atoi(tempIncome->amount);
                sumIncomes += amount;
            }
            tempIncome = tempIncome->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("Total incomes in the year %s: ", year);
        printf("%d Rials\n\n", sumIncomes);
        printf("--------------------------------------------------\n\n");
        tempIncome = endIncome = startIncome;
        while(tempIncome != NULL)
        {
            endIncome = tempIncome->link;
            free(tempIncome);
            tempIncome = endIncome;
        }
        printf("1. Incomes Statistics Menu\n2. EXIT\n\n");
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
        while(choice != '1' && choice != '2')
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
            incomesStatisticsMenu();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        tempIncome = endIncome = startIncome;
        while(tempIncome != NULL)
        {
            endIncome = tempIncome->link;
            free(tempIncome);
            tempIncome = endIncome;
        }
        setTextColor(RED);
        printf("\nERROR: In the year %s no income was recorded!\n\n", year);
        setTextColor(WHITE);
        printf("1. Try again!\n2. EXIT\n\n0. Incomes Statistics Menu\n\n");
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
            totalIncomesYear();
        }
        else if(choice == '0')
        {
            incomesStatisticsMenu();
        }
            else
            {
                exit(0);
            }
    }
}

//This function displays the total incomes of a history interval and goes to the next step based on the user's choice
void totalIncomesInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0, sumIncomes=0, amount;
    char beginningYear[5], beginningMonth[3], beginningDay[3], endYear[5], endMonth[3], endDay[3], choice;
    system("cls");
    printf("--------------- Incomes Statistics ---------------\n\n");
    printf("Please enter the beginning of the interval(YYYY/MM/DD): ");
    scanf("%4s/%2s/%2s", beginningYear, beginningMonth, beginningDay);
    fflush(stdin);
    printf("Please enter the end of the interval(YYYY/MM/DD): ");
    scanf("%4s/%2s/%2s", endYear, endMonth, endDay);
    fflush(stdin);
    beginningYearInt = atoi(beginningYear);
    beginningMonthInt = atoi(beginningMonth);
    beginningDayInt = atoi(beginningDay);
    endYearInt = atoi(endYear);
    endMonthInt = atoi(endMonth);
    endDayInt = atoi(endDay);
    if(beginningYearInt == endYearInt)
    {
        if(beginningMonthInt == endMonthInt)
        {
            if(beginningDayInt <= endDayInt)
            {
                correct = 1;
            }
        }
        else if(beginningMonthInt < endMonthInt)
        {
            correct = 1;
        }
    }
    else if(beginningYearInt < endYearInt)
    {
        correct = 1;
    }
    while(correct == 0)
    {
        system("cls");
        printf("--------------- Incomes Statistics ---------------\n\n");
        setTextColor(RED);
        printf("ERROR: The beginning date of the interval must be before the end date of the interval!\n\n");
        setTextColor(WHITE);
        printf("Please enter the beginning of the interval(YYYY/MM/DD): ");
        scanf("%4s/%2s/%2s", beginningYear, beginningMonth, beginningDay);
        fflush(stdin);
        printf("Please enter the end of the interval(YYYY/MM/DD): ");
        scanf("%4s/%2s/%2s", endYear, endMonth, endDay);
        fflush(stdin);
        beginningYearInt = atoi(beginningYear);
        beginningMonthInt = atoi(beginningMonth);
        beginningDayInt = atoi(beginningDay);
        endYearInt = atoi(endYear);
        endMonthInt = atoi(endMonth);
        endDayInt = atoi(endDay);
        if(beginningYearInt == endYearInt)
        {
            if(beginningMonthInt == endMonthInt)
            {
                if(beginningDayInt <= endDayInt)
                {
                    correct = 1;
                }
            }
            else if(beginningMonthInt < endMonthInt)
            {
                correct = 1;
            }
        }
        else if(beginningYearInt < endYearInt)
        {
            correct = 1;
        }
    }
    char incomesFileName[80] = "Incomes_";
    strcat(incomesFileName, Name);
    strcat(incomesFileName, LastName);
    strcat(incomesFileName, ".txt");
    struct income *startIncome, *endIncome, *tempIncome;
    FILE *f;
    f = fopen(incomesFileName, "r");
    if(f != NULL)
    {
        tempIncome = malloc(sizeof(struct income));
        tempIncome->link = NULL;
        fread(tempIncome, sizeof(struct income), 1, f);
        startIncome = endIncome = tempIncome;
        while(feof(f) == 0)
        {
            tempIncome = malloc(sizeof(struct income));
            tempIncome->link = NULL;
            fread(tempIncome, sizeof(struct income), 1, f);
            endIncome->link = tempIncome;
            endIncome = tempIncome;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    tempIncome = startIncome;
    while(tempIncome != NULL)
    {
        ok = 0;
        yearInt = atoi(tempIncome->date.year);
        monthInt = atoi(tempIncome->date.month);
        dayInt = atoi(tempIncome->date.day);
        if(beginningYearInt == yearInt)
        {
            if(beginningMonthInt == monthInt)
            {
                if(beginningDayInt <= dayInt)
                {
                    ok = 1;
                }
            }
            else if(beginningMonthInt < monthInt)
            {
                ok = 1;
            }
        }
        else if(beginningYearInt < yearInt)
        {
            ok = 1;
        }
        if(ok == 1)
        {
            if(endYearInt == yearInt)
            {
                if(endMonthInt == monthInt)
                {
                    if(endDayInt >= dayInt)
                    {
                        exist = 1;
                        ok = 0;
                        break;
                    }
                }
                else if(endMonthInt > monthInt)
                {
                    exist = 1;
                    ok = 0;
                    break;
                }
            }
            else if(endYearInt > yearInt)
            {
                exist = 1;
                ok = 0;
                break;
            }
        }
        tempIncome = tempIncome->link;
    }
    if(exist == 1)
    {
        tempIncome = startIncome;
        while(tempIncome != NULL)
        {
            ok = 0;
            yearInt = atoi(tempIncome->date.year);
            monthInt = atoi(tempIncome->date.month);
            dayInt = atoi(tempIncome->date.day);
            if(beginningYearInt == yearInt)
            {
                if(beginningMonthInt == monthInt)
                {
                    if(beginningDayInt <= dayInt)
                    {
                        ok = 1;
                    }
                }
                else if(beginningMonthInt < monthInt)
                {
                    ok = 1;
                }
            }
            else if(beginningYearInt < yearInt)
            {
                ok = 1;
            }
            if(ok == 1)
            {
                if(endYearInt == yearInt)
                {
                    if(endMonthInt == monthInt)
                    {
                        if(endDayInt >= dayInt)
                        {
                            amount = atoi(tempIncome->amount);
                            sumIncomes += amount;
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        amount = atoi(tempIncome->amount);
                        sumIncomes += amount;
                    }
                }
                else if(endYearInt > yearInt)
                {
                    amount = atoi(tempIncome->amount);
                    sumIncomes += amount;
                }
            }
            tempIncome = tempIncome->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("Total incomes between %s/%s/%s and %s/%s/%s: ", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        printf("%d Rials\n\n", sumIncomes);
        printf("--------------------------------------------------\n\n");
        tempIncome = endIncome = startIncome;
        while(tempIncome != NULL)
        {
            endIncome = tempIncome->link;
            free(tempIncome);
            tempIncome = endIncome;
        }
        printf("1. Incomes Statistics Menu\n2. EXIT\n\n");
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
        while(choice != '1' && choice != '2')
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
            incomesStatisticsMenu();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        tempIncome = endIncome = startIncome;
        while(tempIncome != NULL)
        {
            endIncome = tempIncome->link;
            free(tempIncome);
            tempIncome = endIncome;
        }
        setTextColor(RED);
        printf("\nERROR: No income was recorded between %s/%s/%s and %s/%s/%s!\n\n", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        setTextColor(WHITE);
        printf("1. Try again!\n2. EXIT\n\n0. Incomes Statistics Menu\n\n");
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
            totalIncomesInterval();
        }
        else if(choice == '0')
        {
            incomesStatisticsMenu();
        }
            else
            {
                exit(0);
            }
    }
}

//This function displays the expense statistics menu and goes to the next step based on the user's choice
void expensesStatisticsMenu(void)
{
    char choice;
    system("cls");
    printf("--------------- Expenses Statistics Menu ---------------\n\n");
    printf("1. The total expenses of a certain year\n2. The total expenses in a history interval\n3. The total of a certain type of expense in a history interval\n");
    printf("4. The ratio of different expenses to each other\n5. The details of expenses in a history interval\n6. The most expense in a history interval\n");
    printf("7. Search in the expenses description field\n\n0. Statistics Menu\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7' && choice != '0')
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
        totalExpensesYear();
    }
    else if(choice == '2')
    {
        totalExpensesInterval();
    }
        else if(choice == '3')
        {
            printf("Go to the total of a certain type of expense in a history interval");
        }
            else if(choice == '4')
            {
                printf("Go to the ratio of different expenses to each other");
            }
                else if(choice == '5')
                {
                    printf("Go to the details of expenses in a history interval");
                }
                    else if(choice == '6')
                    {
                        printf("Go to the most expense in a history interval");
                    }
                        else if(choice == '7')
                        {
                            printf("Go to the search in the expenses description field");
                        }
                            else
                            {
                                statisticsMenu();
                            }
}

//This function displays the total expenses of a certain year and goes to the next step based on the user's choice
void totalExpensesYear(void)
{
    int len, exist=0, sumExpenses=0, amount;
    char year[5], choice;
    system("cls");
    printf("--------------- Expenses Statistics ---------------\n\n");
    printf("Please enter your desired year: ");
    gets(year);
    len = strlen(year);
    while(len != 4)
    {
        system("cls");
        printf("--------------- Expenses Statistics ---------------\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered must contain 4 digits!\n\n");
        setTextColor(WHITE);
        printf("Please enter your desired year: ");
        gets(year);
        len = strlen(year);
    }
    char expensesFileName[80] = "Expenses_";
    strcat(expensesFileName, Name);
    strcat(expensesFileName, LastName);
    strcat(expensesFileName, ".txt");
    struct expense *startExpense, *endExpense, *tempExpense;
    FILE *f;
    f = fopen(expensesFileName, "r");
    if(f != NULL)
    {
        tempExpense = malloc(sizeof(struct expense));
        tempExpense->link = NULL;
        fread(tempExpense, sizeof(struct expense), 1, f);
        startExpense = endExpense = tempExpense;
        while(feof(f) == 0)
        {
            tempExpense = malloc(sizeof(struct expense));
            tempExpense->link = NULL;
            fread(tempExpense, sizeof(struct expense), 1, f);
            endExpense->link = tempExpense;
            endExpense = tempExpense;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    tempExpense = startExpense;
    while(tempExpense != NULL)
    {
        if(strcmp(tempExpense->date.year, year) == 0)
        {
            exist = 1;
            break;
        }
        tempExpense = tempExpense->link;
    }
    if(exist == 1)
    {
        tempExpense = startExpense;
        while(tempExpense != NULL)
        {
            if(strcmp(tempExpense->date.year, year) == 0)
            {
                amount = atoi(tempExpense->amount);
                sumExpenses += amount;
            }
            tempExpense = tempExpense->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("Total expenses in the year %s: ", year);
        printf("%d Rials\n\n", sumExpenses);
        printf("---------------------------------------------------\n\n");
        tempExpense = endExpense = startExpense;
        while(tempExpense != NULL)
        {
            endExpense = tempExpense->link;
            free(tempExpense);
            tempExpense = endExpense;
        }
        printf("1. Expenses Statistics Menu\n2. EXIT\n\n");
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
        while(choice != '1' && choice != '2')
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
            expensesStatisticsMenu();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        tempExpense = endExpense = startExpense;
        while(tempExpense != NULL)
        {
            endExpense = tempExpense->link;
            free(tempExpense);
            tempExpense = endExpense;
        }
        setTextColor(RED);
        printf("\nERROR: In the year %s no expense was recorded!\n\n", year);
        setTextColor(WHITE);
        printf("1. Try again!\n2. EXIT\n\n0. Expenses Statistics Menu\n\n");
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
            totalExpensesYear();
        }
        else if(choice == '0')
        {
            expensesStatisticsMenu();
        }
            else
            {
                exit(0);
            }
    }
}

//This function displays the total expenses of a history interval and goes to the next step based on the user's choice
void totalExpensesInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0, sumExpenses=0, amount;
    char beginningYear[5], beginningMonth[3], beginningDay[3], endYear[5], endMonth[3], endDay[3], choice;
    system("cls");
    printf("--------------- Expenses Statistics ---------------\n\n");
    printf("Please enter the beginning of the interval(YYYY/MM/DD): ");
    scanf("%4s/%2s/%2s", beginningYear, beginningMonth, beginningDay);
    fflush(stdin);
    printf("Please enter the end of the interval(YYYY/MM/DD): ");
    scanf("%4s/%2s/%2s", endYear, endMonth, endDay);
    fflush(stdin);
    beginningYearInt = atoi(beginningYear);
    beginningMonthInt = atoi(beginningMonth);
    beginningDayInt = atoi(beginningDay);
    endYearInt = atoi(endYear);
    endMonthInt = atoi(endMonth);
    endDayInt = atoi(endDay);
    if(beginningYearInt == endYearInt)
    {
        if(beginningMonthInt == endMonthInt)
        {
            if(beginningDayInt <= endDayInt)
            {
                correct = 1;
            }
        }
        else if(beginningMonthInt < endMonthInt)
        {
            correct = 1;
        }
    }
    else if(beginningYearInt < endYearInt)
    {
        correct = 1;
    }
    while(correct == 0)
    {
        system("cls");
        printf("--------------- Expenses Statistics ---------------\n\n");
        setTextColor(RED);
        printf("ERROR: The beginning date of the interval must be before the end date of the interval!\n\n");
        setTextColor(WHITE);
        printf("Please enter the beginning of the interval(YYYY/MM/DD): ");
        scanf("%4s/%2s/%2s", beginningYear, beginningMonth, beginningDay);
        fflush(stdin);
        printf("Please enter the end of the interval(YYYY/MM/DD): ");
        scanf("%4s/%2s/%2s", endYear, endMonth, endDay);
        fflush(stdin);
        beginningYearInt = atoi(beginningYear);
        beginningMonthInt = atoi(beginningMonth);
        beginningDayInt = atoi(beginningDay);
        endYearInt = atoi(endYear);
        endMonthInt = atoi(endMonth);
        endDayInt = atoi(endDay);
        if(beginningYearInt == endYearInt)
        {
            if(beginningMonthInt == endMonthInt)
            {
                if(beginningDayInt <= endDayInt)
                {
                    correct = 1;
                }
            }
            else if(beginningMonthInt < endMonthInt)
            {
                correct = 1;
            }
        }
        else if(beginningYearInt < endYearInt)
        {
            correct = 1;
        }
    }
    char expensesFileName[80] = "Expenses_";
    strcat(expensesFileName, Name);
    strcat(expensesFileName, LastName);
    strcat(expensesFileName, ".txt");
    struct expense *startExpense, *endExpense, *tempExpense;
    FILE *f;
    f = fopen(expensesFileName, "r");
    if(f != NULL)
    {
        tempExpense = malloc(sizeof(struct expense));
        tempExpense->link = NULL;
        fread(tempExpense, sizeof(struct expense), 1, f);
        startExpense = endExpense = tempExpense;
        while(feof(f) == 0)
        {
            tempExpense = malloc(sizeof(struct expense));
            tempExpense->link = NULL;
            fread(tempExpense, sizeof(struct expense), 1, f);
            endExpense->link = tempExpense;
            endExpense = tempExpense;
        }
        fclose(f);
    }
    else
    {
        printf("File could not be opened!");
        exit(0);
    }
    tempExpense = startExpense;
    while(tempExpense != NULL)
    {
        ok = 0;
        yearInt = atoi(tempExpense->date.year);
        monthInt = atoi(tempExpense->date.month);
        dayInt = atoi(tempExpense->date.day);
        if(beginningYearInt == yearInt)
        {
            if(beginningMonthInt == monthInt)
            {
                if(beginningDayInt <= dayInt)
                {
                    ok = 1;
                }
            }
            else if(beginningMonthInt < monthInt)
            {
                ok = 1;
            }
        }
        else if(beginningYearInt < yearInt)
        {
            ok = 1;
        }
        if(ok == 1)
        {
            if(endYearInt == yearInt)
            {
                if(endMonthInt == monthInt)
                {
                    if(endDayInt >= dayInt)
                    {
                        exist = 1;
                        ok = 0;
                        break;
                    }
                }
                else if(endMonthInt > monthInt)
                {
                    exist = 1;
                    ok = 0;
                    break;
                }
            }
            else if(endYearInt > yearInt)
            {
                exist = 1;
                ok = 0;
                break;
            }
        }
        tempExpense = tempExpense->link;
    }
    if(exist == 1)
    {
        tempExpense = startExpense;
        while(tempExpense != NULL)
        {
            ok = 0;
            yearInt = atoi(tempExpense->date.year);
            monthInt = atoi(tempExpense->date.month);
            dayInt = atoi(tempExpense->date.day);
            if(beginningYearInt == yearInt)
            {
                if(beginningMonthInt == monthInt)
                {
                    if(beginningDayInt <= dayInt)
                    {
                        ok = 1;
                    }
                }
                else if(beginningMonthInt < monthInt)
                {
                    ok = 1;
                }
            }
            else if(beginningYearInt < yearInt)
            {
                ok = 1;
            }
            if(ok == 1)
            {
                if(endYearInt == yearInt)
                {
                    if(endMonthInt == monthInt)
                    {
                        if(endDayInt >= dayInt)
                        {
                            amount = atoi(tempExpense->amount);
                            sumExpenses += amount;
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        amount = atoi(tempExpense->amount);
                        sumExpenses += amount;
                    }
                }
                else if(endYearInt > yearInt)
                {
                    amount = atoi(tempExpense->amount);
                    sumExpenses += amount;
                }
            }
            tempExpense = tempExpense->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("Total expenses between %s/%s/%s and %s/%s/%s: ", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        printf("%d Rials\n\n", sumExpenses);
        printf("--------------------------------------------------\n\n");
        tempExpense = endExpense = startExpense;
        while(tempExpense != NULL)
        {
            endExpense = tempExpense->link;
            free(tempExpense);
            tempExpense = endExpense;
        }
        printf("1. Expenses Statistics Menu\n2. EXIT\n\n");
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
        while(choice != '1' && choice != '2')
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
            expensesStatisticsMenu();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        tempExpense = endExpense = startExpense;
        while(tempExpense != NULL)
        {
            endExpense = tempExpense->link;
            free(tempExpense);
            tempExpense = endExpense;
        }
        setTextColor(RED);
        printf("\nERROR: No expense was recorded between %s/%s/%s and %s/%s/%s!\n\n", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        setTextColor(WHITE);
        printf("1. Try again!\n2. EXIT\n\n0. Expenses Statistics Menu\n\n");
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
            totalIncomesInterval();
        }
        else if(choice == '0')
        {
            expensesStatisticsMenu();
        }
            else
            {
                exit(0);
            }
    }
}
