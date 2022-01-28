#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>

void loginMenu(void);
int checkFormatName(char *x);
int checkFormatNationalCode(char *x);
int checkFormatMobileNumber(char *x);
int checkFormatEmail(char *x);
int checkFormatPassword(char *x);
int checkFormatAmount(char *x);
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
void totalCertainIncomeInterval(void);
void ratioIncomesInterval(void);
void detailsIncomesInterval(void);
void mostIncomeInterval(void);
void wordSearchIncomesDescription(void);
void expensesStatisticsMenu(void);
void totalExpensesYear(void);
void totalExpensesInterval(void);
void totalCertainExpenseInterval(void);
void ratioExpensesInterval(void);
void detailsExpensesInterval(void);
void mostExpenseInterval(void);
void wordSearchExpensesDescription(void);
void settings(void);

char Name[30], LastName[40], NationalCode[11];

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

//This function receives a string(name or last name) and checks its format(returns 1 if the string format is correct, otherwise returns 0)
int checkFormatName(char *x)
{
    int a;
    if(*x == '\0')
    {
        return 0;
    }
    else
    {
        while(*x != '\0')
        {
            a = isalpha(*x);
            if(a == 0)
            {
                return 0;
                break;
            }
            x++;
        }
        return 1;
    }
}

//This function receives a string(national code) and checks its format(returns 0: if the national code has at least one non-numeric character, returns 1: if national code is not 10 digits, return 2: if national code is correct)
int checkFormatNationalCode(char *x)
{
    int d, n=0;
    if(*x == '\0')
    {
        return 1;
    }
    else
    {
        while(*x != '\0')
        {
            n++;
            d = isdigit(*x);
            if(d == 0)
            {
                return 0;
                break;
            }
            x++;
        }
        if(n == 10)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}

//This function receives a string(mobile number) and checks its format(returns 0: if the mobile number has at least one non-numeric character, returns 1: if mobile number is not 11 digits, return 2: if mobile number is correct)
int checkFormatMobileNumber(char *x)
{
    int d, n=0;
    if(*x == '\0')
    {
        return 1;
    }
    else
    {
        while(*x != '\0')
        {
            n++;
            d = isdigit(*x);
            if(d == 0)
            {
                return 0;
                break;
            }
            x++;
        }
        if(n == 11)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}

//This function receives a string(email) and checks its format(returns 0: if the email does not end at @gmail.com, return 1: if email is correct)
int checkFormatEmail(char *x)
{
    int i=0;
    char gmail[11];
    if(*x == '\0')
    {
        return 0;
    }
    else
    {
        while(*x != '\0')
        {
            if(*x == '@')
            {
                while(*x != '\0')
                {
                    gmail[i] = *x;
                    i++;
                    x++;
                }
                gmail[i] = '\0';
                if(strcmp(gmail, "@gmail.com") == 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            x++;
        }
    }
}

//This function receives a string(password) and checks its format(returns 0: if the password has not at least one digit and one uppercase and one lowercase, returns 1: if password does not have at least 6 characters, return 2: if password is correct)
int checkFormatPassword(char *x)
{
    int digit=0, uppercase=0, lowercase=0, n=0;
    if(*x == '\0')
    {
        return 1;
    }
    else
    {
        while(*x != '\0')
        {
            n++;
            if(1 == isdigit(*x))
            {
                digit = 1;
            }
            else if(1 == isupper(*x))
            {
                uppercase = 1;
            }
            else if(2 == islower(*x))
            {
                lowercase = 1;
            }
            x++;
        }
        if(n < 6)
        {
            return 1;
        }
        else if((digit != 1) || (uppercase != 1) || (lowercase != 1))
        {
            return 0;
        }
        else
        {
            return 2;
        }
    }
}

//This function receives a string(amount) and checks its format(returns 0: if the amount has at least one non-numeric character, return 1: if amount is correct)
int checkFormatAmount(char *x)
{
    int d;
    if(*x == '\0')
    {
        return 0;
    }
    else
    {
        while(*x != '\0')
        {
            d = isdigit(*x);
            if(d == 0)
            {
                return 0;
                break;
            }
            x++;
        }
        return 1;
    }
}

//This function receives user information and places it in file Profiles and goes to the next step based on the user's choice
void signUp(void)
{
    struct profile s;
    s.link = NULL;
    int i=0, j=1, res, lenPassword;
    char name[30], last_name[40], national_code[11], mobile_number[12], email[50], password[30], password2[30], codedPassword[30], ch, choice;
    system("cls");
    printf("--------------- Sign Up ---------------\n\n");
    printf("Enter your name: ");
    gets(name);
    res = checkFormatName(name);
    if(res == 1)
    {
        strcpy(s.name, name);
    }
    else
    {
        while(res == 0)
        {
            setTextColor(RED);
            printf("\nERROR: The name entered must contain only characters!\n\n");
            setTextColor(WHITE);
            printf("Enter your name: ");
            gets(name);
            res = checkFormatName(name);
        }
        strcpy(s.name, name);
    }
    printf("Enter your last name: ");
    gets(last_name);
    res = checkFormatName(last_name);
    if(res == 1)
    {
        strcpy(s.last_name, last_name);
    }
    else
    {
        while(res == 0)
        {
            setTextColor(RED);
            printf("\nERROR: The last name entered must contain only characters!\n\n");
            setTextColor(WHITE);
            printf("Enter your last name: ");
            gets(last_name);
            res = checkFormatName(last_name);
        }
        strcpy(s.last_name, last_name);
    }
    printf("Enter your national code: ");
    gets(national_code);
    res = checkFormatNationalCode(national_code);
    if(res == 2)
    {
        strcpy(s.national_code, national_code);
    }
    else
    {
        while(res != 2)
        {
            if(res == 1)
            {
                setTextColor(RED);
                printf("\nERROR: The national code entered must contain 10 digits!\n\n");
                setTextColor(WHITE);
            }
            else
            {
                setTextColor(RED);
                printf("\nERROR: The national code entered must contain only digits!\n\n");
                setTextColor(WHITE);
            }
            printf("Enter your national code: ");
            gets(national_code);
            res = checkFormatNationalCode(national_code);
        }
        strcpy(s.national_code, national_code);
    }
    printf("Enter your mobile number: ");
    gets(mobile_number);
    res = checkFormatMobileNumber(mobile_number);
    if(res == 2)
    {
        strcpy(s.mobile_number, mobile_number);
    }
    else
    {
        while(res != 2)
        {
            if(res == 1)
            {
                setTextColor(RED);
                printf("\nERROR: The mobile number entered must contain 11 digits!\n\n");
                setTextColor(WHITE);
            }
            else
            {
                setTextColor(RED);
                printf("\nERROR: The mobile number entered must contain only digits!\n\n");
                setTextColor(WHITE);
            }
            printf("Enter your mobile number: ");
            gets(mobile_number);
            res = checkFormatMobileNumber(mobile_number);
        }
        strcpy(s.mobile_number, mobile_number);
    }
    printf("Enter your email: ");
    gets(email);
    res = checkFormatEmail(email);
    if(res == 1)
    {
        strcpy(s.email, email);
    }
    else
    {
        while(res == 0)
        {
            setTextColor(RED);
            printf("\nERROR: The email entered must end at \"@gmail.com\"!\n\n");
            setTextColor(WHITE);
            printf("Enter your email: ");
            gets(email);
            res = checkFormatEmail(email);
        }
        strcpy(s.email, email);
    }
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
    res = checkFormatPassword(password);
    if(res == 2)
    {
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
                printf("\nERROR: The re-password is incorrect! Try again!\n\n");
                setTextColor(WHITE);
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
    }
    else
    {
        while(res != 2)
        {
            if(res == 1)
            {
                setTextColor(RED);
                printf("\nERROR: The password entered must contain at least 6 characters!\n\n");
                setTextColor(WHITE);
            }
            else
            {
                setTextColor(RED);
                printf("\nERROR: The password entered must contain at least one digit, one uppercase and one lowercase letter!\n\n");
                setTextColor(WHITE);
            }
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
            res = checkFormatPassword(password);
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
                printf("\nERROR: The re-password is incorrect! Try again!\n\n");
                setTextColor(WHITE);
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
    }
    lenPassword = strlen(password);
    for(i=0; i<lenPassword; i++)
    {
        codedPassword[i] = password[i] + j;
        j++;
    }
    codedPassword[i] = '\0';
    strcpy(s.password, codedPassword);
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
    int exist = 0, j=0, k=1, error=0, minutes, seconds, lenPassword;
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
    char userName[12], password[31], codedPassword[31], ch;
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
        k=1;
        lenPassword = strlen(password);
        for(j=0; j<lenPassword; j++)
        {
            codedPassword[j] = password[j] + k;
            k++;
        }
        codedPassword[j] = '\0';
        if(strcmp(temp->password, codedPassword) == 0)
        {
            strcpy(Name, temp->name);
            strcpy(LastName, temp->last_name);
            strcpy(NationalCode, temp->national_code);
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
            while(strcmp(temp->password, codedPassword) != 0)
            {
                error++;
                if(error == 5)
                {
                    system("cls");
                    printf("--------------- Login ---------------\n\n");
                    setTextColor(RED);
                    printf(">> ERROR: Try again in 15 minutes! <<\n\n");
                    setTextColor(WHITE);
                    printf("Remaining time: ");
                    for(minutes=14; minutes>=0; minutes--)
                    {
                        printf("%2d:", minutes);
                        for(seconds=59; seconds>=0; seconds--)
                        {
                            printf("%-2d", seconds);
                            Sleep(1000);
                            printf("\b\b");
                        }
                        printf("\b\b\b");
                    }
                    login();
                }
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
                k=1;
                lenPassword = strlen(password);
                for(j=0; j<lenPassword; j++)
                {
                    codedPassword[j] = password[j] + k;
                    k++;
                }
                codedPassword[j]  = '\0';
            }
            strcpy(Name, temp->name);
            strcpy(LastName, temp->last_name);
            strcpy(NationalCode, temp->national_code);
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
                settings();
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
    int res;
    char choice, fileName[80], checkAmount[10];
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
    gets(checkAmount);
    res = checkFormatAmount(checkAmount);
    if(res == 1)
    {
        strcpy(i.amount, checkAmount);
    }
    else
    {
        while(res == 0)
        {
            setTextColor(RED);
            printf("\nERROR: The amount entered must contain only digits!\n\n");
            setTextColor(WHITE);
            printf("Please specify the amount of Income(In term of Rials): ");
            gets(checkAmount);
            res = checkFormatAmount(checkAmount);
        }
        strcpy(i.amount, checkAmount);
    }
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
    int res;
    char choice, fileName[80], checkAmount[10];
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
    gets(checkAmount);
    res = checkFormatAmount(checkAmount);
    if(res == 1)
    {
        strcpy(e.amount, checkAmount);
    }
    else
    {
        while(res == 0)
        {
            setTextColor(RED);
            printf("\nERROR: The amount entered must contain only digits!\n\n");
            setTextColor(WHITE);
            printf("Please specify the amount of Expense(In term of Rials): ");
            gets(checkAmount);
            res = checkFormatAmount(checkAmount);
        }
        strcpy(e.amount, checkAmount);
    }
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
    printf("4. The ratio of different incomes to each other in a history interval\n5. The details of incomes in a history interval\n6. The most income in a history interval\n");
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
            totalCertainIncomeInterval();
        }
            else if(choice == '4')
            {
                ratioIncomesInterval();
            }
                else if(choice == '5')
                {
                    detailsIncomesInterval();
                }
                    else if(choice == '6')
                    {
                        mostIncomeInterval();
                    }
                        else if(choice == '7')
                        {
                            wordSearchIncomesDescription();
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

//This function displays the total of a certain type of income of a history interval and goes to the next step based on the user's choice
void totalCertainIncomeInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0, sumIncomes=0, amount;
    char beginningYear[5], beginningMonth[3], beginningDay[3], endYear[5], endMonth[3], endDay[3], incomeType[20], choice;
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
    printf("\nPlease specify income type:\n\n");
    printf("1. Programming Salary\n2. YARANEH\n3. Pocket Money\n4. University Grant\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4')
    {
        printf("\nPlease specify income type:\n\n");
        printf("1. Programming Salary\n2. YARANEH\n3. Pocket Money\n4. University Grant\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        strcpy(incomeType, "Programming Salary");
    }
    else if(choice == '2')
    {
        strcpy(incomeType, "YARANEH");
    }
        else if(choice == '3')
        {
            strcpy(incomeType, "Pocket Money");
        }
            else if(choice == '4')
            {
                strcpy(incomeType, "University Grant");
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
                        if(strcmp(incomeType, tempIncome->source) == 0)
                        {
                            exist = 1;
                            ok = 0;
                            break;
                        }
                    }
                }
                else if(endMonthInt > monthInt)
                {
                    if(strcmp(incomeType, tempIncome->source) == 0)
                    {
                        exist = 1;
                        ok = 0;
                        break;
                    }
                }
            }
            else if(endYearInt > yearInt)
            {
                if(strcmp(incomeType, tempIncome->source) == 0)
                {
                    exist = 1;
                    ok = 0;
                    break;
                }
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
                            if(strcmp(incomeType, tempIncome->source) == 0)
                            {
                                amount = atoi(tempIncome->amount);
                                sumIncomes += amount;
                            }
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        if(strcmp(incomeType, tempIncome->source) == 0)
                        {
                            amount = atoi(tempIncome->amount);
                            sumIncomes += amount;
                        }
                    }
                }
                else if(endYearInt > yearInt)
                {
                    if(strcmp(incomeType, tempIncome->source) == 0)
                    {
                        amount = atoi(tempIncome->amount);
                        sumIncomes += amount;
                    }
                }
            }
            tempIncome = tempIncome->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("Total income from %s between %s/%s/%s and %s/%s/%s: ", incomeType, beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
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
        printf("\nERROR: No income from %s was recorded between %s/%s/%s and %s/%s/%s!\n\n", incomeType, beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
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
            totalCertainIncomeInterval();
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

//This function displays the ratio of different incomes to each other in a history interval and goes to the next step based on the user's choice
void ratioIncomesInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0;
    int sumIncomes=0, sumProgrammingSlary=0, sumYARANEH=0, sumPocketMoney=0, sumUniversityGrant=0, amount;
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
                            if(strcmp(tempIncome->source, "Programming Salary") == 0)
                            {
                                sumProgrammingSlary += amount;
                            }
                            else if(strcmp(tempIncome->source, "YARANEH") == 0)
                            {
                                sumYARANEH += amount;
                            }
                                else if(strcmp(tempIncome->source, "Pocket Money") == 0)
                                {
                                    sumPocketMoney += amount;
                                }
                                    else if(strcmp(tempIncome->source, "University Grant") == 0)
                                    {
                                        sumUniversityGrant += amount;
                                    }
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        amount = atoi(tempIncome->amount);
                        sumIncomes += amount;
                        if(strcmp(tempIncome->source, "Programming Salary") == 0)
                            {
                                sumProgrammingSlary += amount;
                            }
                            else if(strcmp(tempIncome->source, "YARANEH") == 0)
                            {
                                sumYARANEH += amount;
                            }
                                else if(strcmp(tempIncome->source, "Pocket Money") == 0)
                                {
                                    sumPocketMoney += amount;
                                }
                                    else if(strcmp(tempIncome->source, "University Grant") == 0)
                                    {
                                        sumUniversityGrant += amount;
                                    }
                    }
                }
                else if(endYearInt > yearInt)
                {
                    amount = atoi(tempIncome->amount);
                    sumIncomes += amount;
                    if(strcmp(tempIncome->source, "Programming Salary") == 0)
                        {
                            sumProgrammingSlary += amount;
                        }
                        else if(strcmp(tempIncome->source, "YARANEH") == 0)
                        {
                            sumYARANEH += amount;
                        }
                            else if(strcmp(tempIncome->source, "Pocket Money") == 0)
                            {
                                sumPocketMoney += amount;
                            }
                                else if(strcmp(tempIncome->source, "University Grant") == 0)
                                {
                                    sumUniversityGrant += amount;
                                }
                }
            }
            tempIncome = tempIncome->link;
        }
        float ratioProgrammingSalary, ratioYARANEH, ratioPocketMoney, ratioUniversityGrant;
        ratioProgrammingSalary = ((float)sumProgrammingSlary / sumIncomes) * 100;
        ratioYARANEH = ((float)sumYARANEH / sumIncomes) * 100;
        ratioPocketMoney = ((float)sumPocketMoney / sumIncomes) * 100;
        ratioUniversityGrant = ((float)sumUniversityGrant / sumIncomes) * 100;
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("The ratio of different incomes to each other between %s/%s/%s and %s/%s/%s: ", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        setTextColor(AQUA);
        printf("\n\n> ");
        setTextColor(WHITE);
        printf("Programming Salary = %.2f%%", ratioProgrammingSalary);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("YARANEH = %.2f%%", ratioYARANEH);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Pocket Money = %.2f%%", ratioPocketMoney);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("University Grant = %.2f%%\n\n", ratioUniversityGrant);
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
            ratioIncomesInterval();
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

//This function displays the details of incomes in a history interval and goes to the next step based on the user's choice
void detailsIncomesInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0;
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
        setTextColor(AQUA);
        printf("\n Amount      | Source             | Date       | Description\n");
        setTextColor(WHITE);
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
                            printf(" %-12s", tempIncome->amount);
                            setTextColor(AQUA);
                            printf("|");
                            setTextColor(WHITE);
                            printf(" %-19s", tempIncome->source);
                            setTextColor(AQUA);
                            printf("|");
                            setTextColor(WHITE);
                            printf(" %s/%s/%s ", tempIncome->date.year, tempIncome->date.month, tempIncome->date.day);
                            setTextColor(AQUA);
                            printf("|");
                            setTextColor(WHITE);
                            printf(" %s\n", tempIncome->description);
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        printf(" %-12s", tempIncome->amount);
                        setTextColor(AQUA);
                        printf("|");
                        setTextColor(WHITE);
                        printf(" %-19s", tempIncome->source);
                        setTextColor(AQUA);
                        printf("|");
                        setTextColor(WHITE);
                        printf(" %s/%s/%s ", tempIncome->date.year, tempIncome->date.month, tempIncome->date.day);
                        setTextColor(AQUA);
                        printf("|");
                        setTextColor(WHITE);
                        printf(" %s\n", tempIncome->description);
                    }
                }
                else if(endYearInt > yearInt)
                {
                    printf(" %-12s", tempIncome->amount);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %-19s", tempIncome->source);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s/%s/%s ", tempIncome->date.year, tempIncome->date.month, tempIncome->date.day);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s\n", tempIncome->description);
                }
            }
            tempIncome = tempIncome->link;
        }
        printf("\n--------------------------------------------------\n\n");
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
            detailsIncomesInterval();
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

//This function displays the most income in a history interval and goes to the next step based on the user's choice
void mostIncomeInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0, mostIncome=0, amount;
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
                            if(amount >= mostIncome)
                            {
                                mostIncome = amount;
                            }
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        amount = atoi(tempIncome->amount);
                        if(amount >= mostIncome)
                        {
                            mostIncome = amount;
                        }
                    }
                }
                else if(endYearInt > yearInt)
                {
                    amount = atoi(tempIncome->amount);
                    if(amount >= mostIncome)
                    {
                        mostIncome = amount;
                    }
                }
            }
            tempIncome = tempIncome->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("The most income between %s/%s/%s and %s/%s/%s: ", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        printf("%d Rials\n\n", mostIncome);
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
            mostIncomeInterval();
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

//This function displays incomes that have the user desired word in their description field and goes to the next step based on the user's choice
void wordSearchIncomesDescription(void)
{
    int exist=0, i=0, j=0, k=0, a=0, b=0, choice;
    char description[100], descriptionWords[50][30], word[30], userWord[30], ch;
    system("cls");
    printf("--------------- Incomes Statistics ---------------\n\n");
    printf("Please enter a search term: ");
    scanf("%s", userWord);
    fflush(stdin);
    strcpy(word, userWord);
    strlwr(word);
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
        memset(descriptionWords, 0, sizeof(descriptionWords));
        strcpy(description, tempIncome->description);
        ch = description[i];
        i++;
        while(ch != '\r')
        {
            ch = tolower(ch);
            descriptionWords[j][k] = ch;
            k++;
            ch = description[i];
            i++;
            while(ch != ' ' && ch != '\r')
            {
                ch = tolower(ch);
                descriptionWords[j][k] = ch;
                k++;
                ch = description[i];
                i++;
            }
            descriptionWords[j][k] = '\0';
            if(ch == ' ')
            {
                k=0;
                j++;
                ch = description[i];
                i++;
            }
        }
        for(i=0; i<50; i++)
        {
            if(strcmp(word, descriptionWords[i]) == 0)
            {
                exist = 1;
                break;
            }
        }
        i=0;
        j=0;
        k=0;
        tempIncome = tempIncome->link;
    }
    if(exist == 1)
    {
        setTextColor(AQUA);
        printf("\n Amount      | Source             | Date       | Description\n");
        setTextColor(WHITE);
        tempIncome = startIncome;
        while(tempIncome != NULL)
        {
            memset(descriptionWords, 0, sizeof(descriptionWords));
            strcpy(description, tempIncome->description);
            ch = description[i];
            i++;
            while(ch != '\r')
            {
                ch = tolower(ch);
                descriptionWords[j][k] = ch;
                k++;
                ch = description[i];
                i++;
                while(ch != ' ' && ch != '\r')
                {
                    ch = tolower(ch);
                    descriptionWords[j][k] = ch;
                    k++;
                    ch = description[i];
                    i++;
                }
                descriptionWords[j][k] = '\0';
                if(ch == ' ')
                {
                    k=0;
                    j++;
                    ch = description[i];
                    i++;
                }
            }
            for(i=0; i<50; i++)
            {
                if(strcmp(word, descriptionWords[i]) == 0)
                {
                    printf(" %-12s", tempIncome->amount);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %-19s", tempIncome->source);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s/%s/%s ", tempIncome->date.year, tempIncome->date.month, tempIncome->date.day);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s\n", tempIncome->description);
                    break;
                }
            }
            i=0;
            j=0;
            k=0;
            tempIncome = tempIncome->link;
        }
        printf("\n--------------------------------------------------\n\n");
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
        printf("\nERROR: The word \"%s\" was not found!\n\n", userWord);
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
            wordSearchIncomesDescription();
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
    printf("4. The ratio of different expenses to each other in a history interval\n5. The details of expenses in a history interval\n6. The most expense in a history interval\n");
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
            totalCertainExpenseInterval();
        }
            else if(choice == '4')
            {
                ratioExpensesInterval();
            }
                else if(choice == '5')
                {
                    detailsExpensesInterval();
                }
                    else if(choice == '6')
                    {
                        mostExpenseInterval();
                    }
                        else if(choice == '7')
                        {
                            wordSearchExpensesDescription();
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
            totalExpensesInterval();
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

//This function displays the total of a certain type of expense of a history interval and goes to the next step based on the user's choice
void totalCertainExpenseInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0, sumExpenses=0, amount;
    char beginningYear[5], beginningMonth[3], beginningDay[3], endYear[5], endMonth[3], endDay[3], expenseType[25], choice;
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
    printf("\nPlease specify expense type:\n\n");
    printf("1. Clothing\n2. Transportation\n3. Tuition Fees\n4. Entertainment\n5. Mobile and Internet Bill\n6. Medical Expenses\n7. Donate to Charity\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7')
    {
        printf("\nPlease specify expense type:\n\n");
        printf("1. Clothing\n2. Transportation\n3. Tuition Fees\n4. Entertainment\n5. Mobile and Internet Bill\n6. Medical Expenses\n7. Donate to Charity\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    if(choice == '1')
    {
        strcpy(expenseType, "Clothing");
    }
    else if(choice == '2')
    {
        strcpy(expenseType, "Transportation");
    }
        else if(choice == '3')
        {
            strcpy(expenseType, "Tuition Fees");
        }
            else if(choice == '4')
            {
                strcpy(expenseType, "Entertainment");
            }
                else if(choice == '5')
                {
                    strcpy(expenseType, "Mobile and Internet Bill");
                }
                    else if(choice == '6')
                    {
                        strcpy(expenseType, "Medical Expenses");
                    }
                        else if(choice == '7')
                        {
                            strcpy(expenseType, "Donate to Charity");
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
                        if(strcmp(expenseType, tempExpense->item) == 0)
                        {
                            exist = 1;
                            ok = 0;
                            break;
                        }
                    }
                }
                else if(endMonthInt > monthInt)
                {
                    if(strcmp(expenseType, tempExpense->item) == 0)
                    {
                        exist = 1;
                        ok = 0;
                        break;
                    }
                }
            }
            else if(endYearInt > yearInt)
            {
                if(strcmp(expenseType, tempExpense->item) == 0)
                {
                    exist = 1;
                    ok = 0;
                    break;
                }
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
                            if(strcmp(expenseType, tempExpense->item) == 0)
                            {
                                amount = atoi(tempExpense->amount);
                                sumExpenses += amount;
                            }
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        if(strcmp(expenseType, tempExpense->item) == 0)
                        {
                            amount = atoi(tempExpense->amount);
                            sumExpenses += amount;
                        }
                    }
                }
                else if(endYearInt > yearInt)
                {
                    if(strcmp(expenseType, tempExpense->item) == 0)
                    {
                        amount = atoi(tempExpense->amount);
                        sumExpenses += amount;
                    }
                }
            }
            tempExpense = tempExpense->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("Total expense from %s between %s/%s/%s and %s/%s/%s: ", expenseType, beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
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
        printf("\nERROR: No expense from %s was recorded between %s/%s/%s and %s/%s/%s!\n\n", expenseType, beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
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
            totalCertainExpenseInterval();
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

//This function displays the ratio of different expenses to each other in a history interval and goes to the next step based on the user's choice
void ratioExpensesInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0;
    int sumExpenses=0, sumClothing=0, sumTransportation=0, sumTuitionFees=0, sumEntertainment=0, sumMobileAndInternetBill=0, sumMedicalExpenses=0, sumDonateToCharity=0, amount;
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
                            if(strcmp(tempExpense->item, "Clothing") == 0)
                            {
                                sumClothing += amount;
                            }
                            else if(strcmp(tempExpense->item, "Transportation") == 0)
                            {
                                sumTransportation += amount;
                            }
                                else if(strcmp(tempExpense->item, "Tuition Fees") == 0)
                                {
                                    sumTuitionFees += amount;
                                }
                                    else if(strcmp(tempExpense->item, "Entertainment") == 0)
                                    {
                                        sumEntertainment += amount;
                                    }
                                        else if(strcmp(tempExpense->item, "Mobile and Internet Bill") == 0)
                                        {
                                            sumMobileAndInternetBill += amount;
                                        }
                                            else if(strcmp(tempExpense->item, "Medical Expenses") == 0)
                                            {
                                                sumMedicalExpenses += amount;
                                            }
                                                else if(strcmp(tempExpense->item, "Donate to Charity") == 0)
                                                {
                                                    sumDonateToCharity += amount;
                                                }
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        amount = atoi(tempExpense->amount);
                        sumExpenses += amount;
                        if(strcmp(tempExpense->item, "Clothing") == 0)
                            {
                                sumClothing += amount;
                            }
                            else if(strcmp(tempExpense->item, "Transportation") == 0)
                            {
                                sumTransportation += amount;
                            }
                                else if(strcmp(tempExpense->item, "Tuition Fees") == 0)
                                {
                                    sumTuitionFees += amount;
                                }
                                    else if(strcmp(tempExpense->item, "Entertainment") == 0)
                                    {
                                        sumEntertainment += amount;
                                    }
                                        else if(strcmp(tempExpense->item, "Mobile and Internet Bill") == 0)
                                        {
                                            sumMobileAndInternetBill += amount;
                                        }
                                            else if(strcmp(tempExpense->item, "Medical Expenses") == 0)
                                            {
                                                sumMedicalExpenses += amount;
                                            }
                                                else if(strcmp(tempExpense->item, "Donate to Charity") == 0)
                                                {
                                                    sumDonateToCharity += amount;
                                                }
                    }
                }
                else if(endYearInt > yearInt)
                {
                    amount = atoi(tempExpense->amount);
                    sumExpenses += amount;
                    if(strcmp(tempExpense->item, "Clothing") == 0)
                    {
                        sumClothing += amount;
                    }
                    else if(strcmp(tempExpense->item, "Transportation") == 0)
                    {
                        sumTransportation += amount;
                    }
                        else if(strcmp(tempExpense->item, "Tuition Fees") == 0)
                        {
                            sumTuitionFees += amount;
                        }
                            else if(strcmp(tempExpense->item, "Entertainment") == 0)
                            {
                                sumEntertainment += amount;
                            }
                                else if(strcmp(tempExpense->item, "Mobile and Internet Bill") == 0)
                                {
                                    sumMobileAndInternetBill += amount;
                                }
                                    else if(strcmp(tempExpense->item, "Medical Expenses") == 0)
                                    {
                                        sumMedicalExpenses += amount;
                                    }
                                        else if(strcmp(tempExpense->item, "Donate to Charity") == 0)
                                        {
                                            sumDonateToCharity += amount;
                                        }
                }
            }
            tempExpense = tempExpense->link;
        }
        float ratioClothing, ratioTransportation, ratioTuitionFees, ratioEntertainment, ratioMobileAndInternetBill, ratioMedicalExpenses, ratioDonateToCharity;
        ratioClothing = ((float)sumClothing / sumExpenses) * 100;
        ratioTransportation = ((float)sumTransportation / sumExpenses) * 100;
        ratioTuitionFees = ((float)sumTuitionFees / sumExpenses) * 100;
        ratioEntertainment = ((float)sumEntertainment / sumExpenses) * 100;
        ratioMobileAndInternetBill = ((float)sumMobileAndInternetBill / sumExpenses) * 100;
        ratioMedicalExpenses = ((float)sumMedicalExpenses / sumExpenses) * 100;
        ratioDonateToCharity = ((float)sumDonateToCharity / sumExpenses) * 100;
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("The ratio of different expenses to each other between %s/%s/%s and %s/%s/%s: ", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        setTextColor(AQUA);
        printf("\n\n> ");
        setTextColor(WHITE);
        printf("Clothing = %.2f%%", ratioClothing);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Transportation = %.2f%%", ratioTransportation);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Tuition Fees = %.2f%%", ratioTuitionFees);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Entertainment = %.2f%%", ratioEntertainment);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Mobile and Internet Bill = %.2f%%", ratioMobileAndInternetBill);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Medical Expenses = %.2f%%", ratioMedicalExpenses);
        setTextColor(AQUA);
        printf("\n> ");
        setTextColor(WHITE);
        printf("Donate to Charity = %.2f%%\n\n", ratioDonateToCharity);
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
            ratioExpensesInterval();
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

//This function displays the details of expenses in a history interval and goes to the next step based on the user's choice
void detailsExpensesInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0;
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
        setTextColor(AQUA);
        printf("\n Amount      | Item                     | Date       | Description\n");
        setTextColor(WHITE);
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
                            printf(" %-12s", tempExpense->amount);
                            setTextColor(AQUA);
                            printf("|");
                            setTextColor(WHITE);
                            printf(" %-25s", tempExpense->item);
                            setTextColor(AQUA);
                            printf("|");
                            setTextColor(WHITE);
                            printf(" %s/%s/%s ", tempExpense->date.year, tempExpense->date.month, tempExpense->date.day);
                            setTextColor(AQUA);
                            printf("|");
                            setTextColor(WHITE);
                            printf(" %s\n", tempExpense->description);
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        printf(" %-12s", tempExpense->amount);
                        setTextColor(AQUA);
                        printf("|");
                        setTextColor(WHITE);
                        printf(" %-25s", tempExpense->item);
                        setTextColor(AQUA);
                        printf("|");
                        setTextColor(WHITE);
                        printf(" %s/%s/%s ", tempExpense->date.year, tempExpense->date.month, tempExpense->date.day);
                        setTextColor(AQUA);
                        printf("|");
                        setTextColor(WHITE);
                        printf(" %s\n", tempExpense->description);
                    }
                }
                else if(endYearInt > yearInt)
                {
                    printf(" %-12s", tempExpense->amount);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %-25s", tempExpense->item);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s/%s/%s ", tempExpense->date.year, tempExpense->date.month, tempExpense->date.day);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s\n", tempExpense->description);
                }
            }
            tempExpense = tempExpense->link;
        }
        printf("\n--------------------------------------------------\n\n");
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
            detailsExpensesInterval();
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

//This function displays the most expense in a history interval and goes to the next step based on the user's choice
void mostExpenseInterval(void)
{
    int beginningYearInt, beginningMonthInt, beginningDayInt, endYearInt, endMonthInt, endDayInt, yearInt, monthInt, dayInt, correct=0, ok=0, exist=0, mostExpense=0, amount;
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
                            if(amount >= mostExpense)
                            {
                                mostExpense = amount;
                            }
                        }
                    }
                    else if(endMonthInt > monthInt)
                    {
                        amount = atoi(tempExpense->amount);
                        if(amount >= mostExpense)
                        {
                            mostExpense = amount;
                        }
                    }
                }
                else if(endYearInt > yearInt)
                {
                    amount = atoi(tempExpense->amount);
                    if(amount >= mostExpense)
                    {
                        mostExpense = amount;
                    }
                }
            }
            tempExpense = tempExpense->link;
        }
        setTextColor(AQUA);
        printf("\n>> ");
        setTextColor(WHITE);
        printf("The most expense between %s/%s/%s and %s/%s/%s: ", beginningYear, beginningMonth, beginningDay, endYear, endMonth, endDay);
        printf("%d Rials\n\n", mostExpense);
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
            mostExpenseInterval();
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

//This function displays expenses that have the user desired word in their description field and goes to the next step based on the user's choice
void wordSearchExpensesDescription(void)
{
    int exist=0, i=0, j=0, k=0, a=0, b=0, choice;
    char description[100], descriptionWords[50][30], word[30], userWord[30], ch;
    system("cls");
    printf("--------------- Expenses Statistics ---------------\n\n");
    printf("Please enter a search term: ");
    scanf("%s", userWord);
    fflush(stdin);
    strcpy(word, userWord);
    strlwr(word);
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
        memset(descriptionWords, 0, sizeof(descriptionWords));
        strcpy(description, tempExpense->description);
        ch = description[i];
        i++;
        while(ch != '\r')
        {
            ch = tolower(ch);
            descriptionWords[j][k] = ch;
            k++;
            ch = description[i];
            i++;
            while(ch != ' ' && ch != '\r')
            {
                ch = tolower(ch);
                descriptionWords[j][k] = ch;
                k++;
                ch = description[i];
                i++;
            }
            descriptionWords[j][k] = '\0';
            if(ch == ' ')
            {
                k=0;
                j++;
                ch = description[i];
                i++;
            }
        }
        for(i=0; i<50; i++)
        {
            if(strcmp(word, descriptionWords[i]) == 0)
            {
                exist = 1;
                break;
            }
        }
        i=0;
        j=0;
        k=0;
        tempExpense = tempExpense->link;
    }
    if(exist == 1)
    {
        setTextColor(AQUA);
        printf("\n Amount      | Item                     | Date       | Description\n");
        setTextColor(WHITE);
        tempExpense = startExpense;
        while(tempExpense != NULL)
        {
            memset(descriptionWords, 0, sizeof(descriptionWords));
            strcpy(description, tempExpense->description);
            ch = description[i];
            i++;
            while(ch != '\r')
            {
                ch = tolower(ch);
                descriptionWords[j][k] = ch;
                k++;
                ch = description[i];
                i++;
                while(ch != ' ' && ch != '\r')
                {
                    ch = tolower(ch);
                    descriptionWords[j][k] = ch;
                    k++;
                    ch = description[i];
                    i++;
                }
                descriptionWords[j][k] = '\0';
                if(ch == ' ')
                {
                    k=0;
                    j++;
                    ch = description[i];
                    i++;
                }
            }
            for(i=0; i<50; i++)
            {
                if(strcmp(word, descriptionWords[i]) == 0)
                {
                    printf(" %-12s", tempExpense->amount);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %-25s", tempExpense->item);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s/%s/%s ", tempExpense->date.year, tempExpense->date.month, tempExpense->date.day);
                    setTextColor(AQUA);
                    printf("|");
                    setTextColor(WHITE);
                    printf(" %s\n", tempExpense->description);
                    break;
                }
            }
            i=0;
            j=0;
            k=0;
            tempExpense = tempExpense->link;
        }
        printf("\n--------------------------------------------------\n\n");
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
        printf("\nERROR: The word \"%s\" was not found!\n\n", userWord);
        setTextColor(WHITE);
        printf("1. Try again!\n2. EXIT\n\n0. Expense Statistics Menu\n\n");
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
            wordSearchExpensesDescription();
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

//This function receives change in user information and places it in file Profiles and goes to the next step based on the user's choice
void settings(void)
{
    int i=0, j=1, res, lenPassword;
    char email[50], mobile_number[12], password[30], password2[30], codedPassword[30], ch, choice;
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
    temp = start;
    while(temp != NULL)
    {
        if(strcmp(temp->national_code, NationalCode) == 0)
        {
            break;
        }
        temp = temp->link;
    }
    system("cls");
    printf("--------------- Settings ---------------\n\n");
    printf("Which part of your profile do you want to change?\n\n");
    printf("1. Password\n2. Mobile Number\n3. Email\n\n0. Main Menu\n\n");
    printf(">>Please Enter Your Choice: ");
    choice = getchar();
    fflush(stdin);
    while(choice != '1' && choice != '2' && choice != '3' && choice != '0')
    {
        system("cls");
        printf("--------------- Settings ---------------\n\n");
        printf("Which part of your profile do you want to change?\n\n");
        printf("1. Password\n2. Mobile Number\n3. Email\n\n0. Main Menu\n\n");
        setTextColor(RED);
        printf("ERROR: The number entered is invalid! Try again!\n\n");
        setTextColor(WHITE);
        printf(">>Please Enter Your Choice: ");
        choice = getchar();
        fflush(stdin);
    }
    printf("\n");
    if(choice == '1')
    {
        printf("Enter your new password: ");
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
        res = checkFormatPassword(password);
        if(res == 2)
        {
            printf("Re-enter your new password: ");
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
                strcpy(temp->password, password);
            }
            else
            {
                while(strcmp(password, password2) != 0)
                {
                    setTextColor(RED);
                    printf("\nERROR: The re-password is incorrect! Try again!\n\n");
                    setTextColor(WHITE);
                    printf("Re-enter your new password: ");
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
                strcpy(temp->password, password);
            }
        }
        else
        {
            while(res != 2)
            {
                if(res == 1)
                {
                    setTextColor(RED);
                    printf("\nERROR: The password entered must contain at least 6 characters!\n\n");
                    setTextColor(WHITE);
                }
                else
                {
                    setTextColor(RED);
                    printf("\nERROR: The password entered must contain at least one digit, one uppercase and one lowercase letter!\n\n");
                    setTextColor(WHITE);
                }
                printf("Enter your new password: ");
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
                res = checkFormatPassword(password);
            }
            printf("Re-enter your new password: ");
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
                strcpy(temp->password, password);
            }
            else
            {
                while(strcmp(password, password2) != 0)
                {
                    setTextColor(RED);
                    printf("\nERROR: The re-password is incorrect! Try again!\n\n");
                    setTextColor(WHITE);
                    printf("Re-enter your new password: ");
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
                strcpy(temp->password, password);
            }
        }
        lenPassword = strlen(password);
        for(i=0; i<lenPassword; i++)
        {
            codedPassword[i] = password[i] + j;
            j++;
        }
        codedPassword[i] = '\0';
        strcpy(temp->password, codedPassword);
    }
    else if(choice == '2')
    {
        printf("Enter your new mobile number: ");
        gets(mobile_number);
        res = checkFormatMobileNumber(mobile_number);
        if(res == 2)
        {
            strcpy(temp->mobile_number, mobile_number);
        }
        else
        {
            while(res != 2)
            {
                if(res == 1)
                {
                    setTextColor(RED);
                    printf("\nERROR: The mobile number entered must contain 11 digits!\n\n");
                    setTextColor(WHITE);
                }
                else
                {
                    setTextColor(RED);
                    printf("\nERROR: The mobile number entered must contain only digits!\n\n");
                    setTextColor(WHITE);
                }
                printf("Enter your new mobile number: ");
                gets(mobile_number);
                res = checkFormatMobileNumber(mobile_number);
            }
            strcpy(temp->mobile_number, mobile_number);
        }
    }
        else if(choice == '3')
        {
            printf("Enter your new email: ");
            gets(email);
            res = checkFormatEmail(email);
            if(res == 1)
            {
                strcpy(temp->email, email);
            }
            else
            {
                while(res == 0)
                {
                    setTextColor(RED);
                    printf("\nERROR: The email entered must end at \"@gmail.com\"!\n\n");
                    setTextColor(WHITE);
                    printf("Enter your email: ");
                    gets(email);
                    res = checkFormatEmail(email);
                }
                strcpy(temp->email, email);
            }
        }
            else
            {
                mainMenu();
            }
    if(remove("Profiles.txt") == 0)
    {
        f = fopen("Profiles.txt", "a");
        if(f != NULL)
        {
            temp = start;
            while(temp != NULL)
            {
                fwrite(temp, sizeof(struct profile), 1, f);
                temp = temp->link;
            }
            fclose(f);
            setTextColor(GREEN);
            printf("\nChange was successfully recorded!\n\n");
            setTextColor(WHITE);
            printf("----------------------------------------\n\n");
        }
        else
        {
            printf("File could not be opened!");
            exit(0);
        }
    }
    else
    {
        printf("File could not be deleted!");
    }
    printf("1. Another Change\n2. Main Menu\n3. EXIT\n\n");
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
        settings();
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
