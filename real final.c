#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
typedef struct
{
    char username[100];
    char password[100];

} loginStruct;
typedef struct
{
    int month;
    int year ;
} date_opened;
typedef struct
{
    char account_number[30];
    char name[50];
    char mobile[30];
    char address[60];
    double balance;
    date_opened DOB;
} user;
user users_arr[100];
void printUsersArray();

user* load( );
int  Check_Account_num(char acc_no[],user *users_arr);
int Find_Index(char required_num[],user users_arr[]);
int find_number_of_accounts(user users_arr[]);
void search_specific_user_data(user users_arr[]);
void Deposit(user users_arr[]);
void withdraw(user users_arr[]);
int duplicate (user users_arr[],char key[]);
void add (user users[]);
int check_email(char email[]);
void transfer (user users_arr[]);
void menu( user users_arr[]);
void printSorted(user users_arr[]);
void sortByName(user users_arr[]);
void sortByBalance(user users_arr[]);
void Advanced_Search(user users_arr[],char keyword);
void sort();
void save_balance(double balance,user users_arr[],int i);
void save_transactions_withdraw(char username[], user users_arr[],double balance,double withd);
void save_transactions_deposit(char username[], user users_arr[],double balance,double dep);
void modified_accounts(char name[40],char mobile[15],char address[60],user users_arr[],int i);
void modify(user users_arr[]);
void sort_cases(user users_arr[]);
void login()
{
    char answer[30];
    char q[30];
    char pass[100];
    char user[100];
    loginStruct log[100];
    int i=0,j,found=0,found2=0;
    while(1)
    {
        printf("do you want to login?:(yes or no)\n");
        scanf("%s",answer);
        strcmp(answer,"yes");
        if(strcmp(answer,"yes")==0)
        {
            FILE*f1;
            f1= fopen("users.txt","r");
            if(f1==NULL)
            {
                printf("file is not available\n");
                return;
            }
            else
            {
                while (fscanf(f1,"%s%s",log[i].username,log[i].password)==2)
                {
                    i++;
                }
                fclose(f1);
                printf("please enter username:\n");
                scanf("%s",user);
                printf("please enter password:\n");
                scanf("%s",pass);
                for(j=0;j<i; j++)
                {

                    if(strcmp(log[j].username,user)==0)
                    {
                        found=1;
                        strcmp(log[j].password,pass);
                        if(strcmp(log[j].password,pass)==0)
                        {
                            found2=1;
                            break;
                        }
                    }
                }
                if(found==0|| found2==0)
                    printf("incorrect username or password!");
                else{
                    printf("login successful\n");
                    break;
                    menu(users_arr);
                }

            }

        }
        else if (strcmp(answer,"no")==0)
        {
            printf("do you want to exit? yes or no\n");
            scanf("%s",q);
            strcmp(q,"no");
            if( strcmp(q,"no")==0)
            continue;
            else
                break;

        } else {
        printf("invalid\n");
        }

}
}

int delete_function()
{
    printf("delete is working");
    return 1;
}

int report()
{
    printf("report is working");
    return 1;
}

int quit()
{
    printf("quit is working");
    return 1;
}
int sortByDateOfOpening()
{
    printf("sortByDateOfOpening is working");
    return 1;
}


int main()
{
    user* users_arr = load();
    printf("%lf",users_arr[3].balance);


      if (users_arr == NULL)
    {
        printf("Failed to load users.\n");
        return 1;
    }
    int choice ;
    printf("enter your choice\n");
    printf("1-login\n");
    printf("2-quit\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        login();
    }
    else if (choice==2)
        exit(1);
    else
        printf("invalid choice please try again");

    printf("welocome");
    menu( users_arr);



    return 0;
}

int find_number_of_accounts(user users_arr[])
{
    int count=0;
    for(int i=0; users_arr[i].account_number[0] != '\0'; i++ )
        count++;
    return count;

}

int  Check_Account_num(char acc_no[],user *users_arr)
{
    if(strlen(acc_no)!=10)
        return 0;
    else
    {
        for(int j=0; j<10; j++)
            if(!isdigit(acc_no[j]))
                return 0;
    }
    return 1;

}

   int Find_Index(char required_num[],user users_arr[])
    {   int count=find_number_of_accounts(users_arr);
        for(int i=0;i<count; i++ ){
            if (strcmp(required_num,users_arr[i].account_number)==0)
            {
                return i;
            }
            }

        return -1;
    }



    void search_specific_user_data(user users_arr[])
{
    char acc_no[20];
    int valid,k;

    do
    {
        printf("Please enter the account number you want to display its data:");
        scanf("%s",acc_no);
        valid=Check_Account_num(acc_no, users_arr);
        if(!valid)
            printf("\nWrong account number,please try again.\n");
    }
    while(valid==0);
    do
    {
         k=Find_Index(acc_no, users_arr);
        if(k==-1)
            printf("Account number is not found.\n");}
            while(k==-1);

            printf("Account Number:%s\n",users_arr[k].account_number);
            printf("Name:%s\n",users_arr[k].name);
            printf("E-mail:%s\n",users_arr[k].address);
            printf("Balance:%0.2lf\n",users_arr[k].balance);
            printf("Mobile:%s\n",users_arr[k].mobile);
            printf("Date opened:%d_%d",users_arr[k].DOB.month,users_arr[k].DOB.year);
        menu(users_arr);

    }



    void transfer (user users_arr[])
    {
        char sender[30],reciever[30],answer[10];
        double transferMoney;
        do
        {
            printf("enter the account number of the sender");
            scanf("%s",sender);
            if(!Check_Account_num(sender,users_arr))
                printf("account number not found try again");

        }
        while(!Check_Account_num(sender,users_arr));
        do
        {
            printf("enter the account number of the reciever");
            scanf("%s",reciever);
            if(!Check_Account_num(reciever,users_arr))
                printf("account number not found try again");

        }
        while(!Check_Account_num(reciever,users_arr));
        int sender_index=Find_Index(sender,users_arr);
        int reciever_index=Find_Index(reciever,users_arr);

        printf("enter the amount of money you want to transfer:");
        scanf("%lf",&transferMoney);
        if(users_arr[sender_index].balance<transferMoney)
            printf("sorry you don't have enough balance");
        else
        {
            users_arr[sender_index].balance= users_arr[sender_index].balance-transferMoney;
            users_arr[reciever_index].balance= users_arr[reciever_index].balance+transferMoney;
      printf("the updated balance of the reciever %lf\n",users_arr[reciever_index].balance);
            printf("the updated balance of the sender %lf\n",users_arr[sender_index].balance);

        }
        while(1){
    printf("\n Do you want to save the changes:\n(yes or no)");
    scanf("%s",answer);

    if(strcmp(answer,"Yes")==0||strcmp(answer,"yes")==0)
    {
        save_balance( users_arr[sender_index].balance, users_arr,sender_index);
        save_transactions_withdraw(users_arr[sender_index].account_number, users_arr,users_arr[sender_index].balance,transferMoney);
         save_balance( users_arr[reciever_index].balance, users_arr,reciever_index);
        save_transactions_withdraw(users_arr[reciever_index].account_number, users_arr,users_arr[reciever_index].balance,transferMoney);
        printf("The changes are saved successfully");
        menu(users_arr);
    }else if (strcmp(answer,"No")==0||strcmp(answer,"no")==0)
        menu(users_arr);
      else{
        printf("Invalid answer.please try again.\n");
        continue;}
}}




void Deposit(user users_arr[])

{

    char answer[15];
    double deposit;
    char acc_no[12];
    printf("enter account number:");
    scanf("%s",acc_no);
    int valid=Check_Account_num(acc_no,users_arr);
     int index=Find_Index(acc_no,users_arr);
    if(!valid)
        printf("Wrong account number,please try again");
    else
    {
    if(index==-1)
        printf("Sorry this account number is not found.");
        else{ do
        {
            printf("Enter the amount you want to deposit:\nMAX limit for deposit per a transaction is 10000$.");
            scanf("%lf",&deposit);
            if(deposit>10000)
                printf("Sorry,this process can't be executed,try again.");
        }
        while(deposit>10000);
    if (deposit<=0)
        printf("Invalid transaction,please enter positive value.");
    else
    {
        printf("please wait while your transaction is being processesd.");
        users_arr[index].balance+=deposit;
    }
        } }
        while(1){
    printf("Do you want to save the changes:\n(yes or no)");
    scanf("%s",answer);

    if(strcmp(answer,"Yes")==0||strcmp(answer,"yes")==0)
    {
 save_balance( users_arr[index].balance, users_arr,index);
 save_transactions_deposit(users_arr[index].account_number, users_arr,users_arr[index].balance,deposit);

        printf("The changes are saved successfully");
        menu(users_arr);
    }else if (strcmp(answer,"No")==0||strcmp(answer,"no")==0)
        menu(users_arr);
      else{
        printf("Invalid answer.please try again.\n");
        continue;}
}}




void withdraw(user users_arr[])
{
    char acc_no[15];
    char answer[5];
    double withd;
    printf("enter account number:");
    scanf("%s",acc_no);
    int index=Find_Index( acc_no, users_arr);
    int valid=Check_Account_num( acc_no, users_arr);

    if(!valid)
        printf("Wrong account number,please try again\n");
    else
    {
        if(index==-1)
            printf("Sorry this account number is not found.");
        else
        { do
        {
            printf("Enter the amount to be withdrawn:\nMAX limit for withdrawal per a transaction is 10000$.");
            scanf("%lf",&withd);
            if(withd>10000)
                printf("Sorry,this process can't be executed,try again.");
        }
        while(withd>10000);
            if(users_arr[index].balance>=withd){
                printf("please wait while your transaction is being processesd.");
                users_arr[index].balance-=withd;
            }

            else
                printf("Your current balance doesn't allow you to withdraw this amount of money.\n");
        }
    }

    printf("Do you want to save the changes?");
    scanf("%s",answer);
    if(strcmp(answer,"Yes")==0||strcmp(answer,"yes")==0)
    {
        save_balance( users_arr[index].balance, users_arr,index);
        save_transactions_withdraw(users_arr[index].account_number, users_arr,users_arr[index].balance,withd);
        printf("The changes are saved successfully");
        menu(users_arr);
    }
    else
    {
        menu(users_arr);
        printf("Nothing is saved.");

    }
}


user* load() {
    FILE* f;
    f = fopen("account.txt", "r");
    if (f == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    user* users_arr = malloc(100 * sizeof(user));
    if (users_arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(f);
        return NULL;
    }

    int i = 0;
    char delim[] = ",";
    char buffer[100];
    while (i < 100 && fgets(buffer, sizeof(buffer), f) != NULL) {
        char* token = strtok(buffer, ",");
        if (token == NULL) {
            printf("Invalid input format.\n");
            break;
        }
        strcpy(users_arr[i].account_number, token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid input format.\n");
            break;
        }
        strcpy(users_arr[i].name, token);


        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid input format.\n");
            break;
        }
        strcpy(users_arr[i].mobile, token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid input format.\n");
            break;
        }
        strcpy(users_arr[i].address, token);

          token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid input format.\n");
            break;
        }
        users_arr[i].balance = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid input format.\n");
            break;
        }
        sscanf(token, "%d-%d", &users_arr[i].DOB.month, &users_arr[i].DOB.year);

        i++;
    }

    fclose(f);
    return users_arr;
}

int duplicate (user users_arr[],char key[])
{
    int count =0;
    key[10]='\0';
    for(int i=0; users_arr[i].account_number[0] != '\0'; i++ )
    {
        if(!strcmp( users_arr[i].account_number,key))
        {
            count ++;
            break;

        }

    }
    return count;
}

int check_email(char email[])
{
    int i,atcount=0,dotcount=0;
    int valid=1;
    if (email[0]=='\0')
    {
        valid=0;
    }
    else
    {
        for (i=0; email[i]!='\0'; i++)
        {
            if (!((email[i]>='A' && email[i]<= 'Z')||(email[i]>='a'&& email[i]<='z')||(email[i]>='0'&& email[i]<='9')||email[i]=='.'||email[i]=='@'||email[i]=='_'))
            {
                valid=0;
                break;
            }
            if (email[i]=='@')
            {
                atcount++;
                if (atcount!=1)
                {
                    valid=0;
                    break;
                }
            }
            if (email[i]=='.')
            {
                dotcount++;
                if (dotcount<1)
                {
                    valid=0;
                    break;
                }
            }
        }
    }
    return valid;
}


void modify(user users_arr[])
{
    char answer[10];
    char email[50];
    char mobile[50];
    char acc_no [13];
    printf("Please enter your account number");
    scanf("%s",acc_no);
    int valid= Check_Account_num( acc_no, users_arr);
    int index= Find_Index( acc_no,users_arr);

    if(!valid)
        printf("Wrong account number,please try again\n");
    else
    {

        if(index==-1)
            printf("Account number is not found.\n");
        else
        {

            while(1)
            {
                char name[50];
                int choice;
                label_1:
                printf("please choose the field you want to modify\n1.Name\n2.Email\n3.Mobile number\n");
                scanf("%d",&choice);
                if(choice>3||choice<1)
                {
                    printf ("This number is not written in the list \n please choose the number of the field from the above list \n");
                    goto label_1;
                }
                switch(choice)
                {
                case 1:
                    printf("Enter updated name:\n");
                    fflush(stdin);
                    gets(name);
                    strcpy(users_arr[index].name,name);
                    printf("Do you want to save?\n");
                    scanf("%s",answer);
                    if(!strcmp(answer,"yes"))
                    {
                       // save(users_arr[index].name);
                        printf("name has been modified successfully\n");
                    }
                    else
                        break;
                    break;
                case 2:
                    printf("Enter updated email:\n");
                    fflush(stdin);
                    gets(email);
                    int vemail=check_email(email);
                    if(!vemail)
                        printf("Invalid email address.\n");
                    else
                    {
                        strcpy(users_arr[index].address,email);
                        printf("Do you want to save?\n");
                        scanf("%s",answer);
                        if(!strcmp(answer,"yes"))
                        {

                           // save(users_arr[index].name);
                            printf("email has been modified successfully");
                        }
                        else
                            break;
                    }
                    break ;

                case 3:
                    printf("Enter updated phone number:\n");
                    fflush(stdin);
                    gets(mobile);
                    strcpy(users_arr[index].mobile,mobile);
                    printf("\n %s",users_arr[index].mobile,mobile);
                    printf("Do you want to save?\n");
                    scanf("%s",answer);
                    if(!strcmp(answer,"yes"))
                    {


                       // save(users_arr[index].name);
                        printf("phone number has been modified successfully");
                    }
                    else
                        break;
                default:
                    printf("Something went wrong.pleae try again.");

                }
                printf("Do you want to modify another data?\n");
                scanf("%s",answer);
                if(!strcmp(answer,"yes"))
                    continue;
                else
                    break;
                break;
            }
        }
    }


while(1)
{
    printf("Do you want to save the changes:\n(yes or no)");
    scanf("%s",answer);

    if(strcmp(answer,"Yes")==0||strcmp(answer,"yes")==0)
    {
        // save();
        printf("The changes are saved successfully");
        menu(users_arr);
    }
    else if (strcmp(answer,"No")==0||strcmp(answer,"no")==0)
        menu(users_arr);
    else
    {
        printf("Invalid answer.please try again.\n");
        continue;
    }
}
}






void add (user users_arr[])
{
    printf("inside the add");
    int check;
    int dup;
    int index=find_number_of_accounts(users_arr);
    users_arr[index+1];
    printf("new bank account\n");
    printf("name:");
    char c= getc(stdin);
    //printf("%c",c);
    //fgets(users_arr[index + 1].name, sizeof(users_arr[index + 1].name), stdin);
    //  s[index + 1].name[strcspn(s[index + 1].name, "\n")] = '\0';
    scanf(" %[^\n]", users_arr[index+1].name);
    printf("mobile phone:");
    scanf("%s",users_arr[index+1].mobile);

    do
    {
        printf("account number:");
        scanf("%s", users_arr[index + 1].account_number);
        //char f= getc(stdin);
        dup = duplicate(users_arr, users_arr[index + 1].account_number);
        if (dup>0)
            printf("\n the account number already exists try again\n");
        }
        while (dup > 0);

        do
        {
            printf("email address:");
            scanf("%s",users_arr[index+1].address);
            check=check_email(users_arr[index+1].address);
            if (!check)
                printf("the email is not right please try again");
        }
        while(!check);

        printf("balance:");
        scanf("%lf",&users_arr[index+1].balance);

        char accno[20];
        strcpy(accno,users_arr[index+1].account_number);
        strcat(accno,".txt");

        FILE *file = fopen(accno,"a");
        if (file == NULL)
        {
            printf("Error opening the file.\n");
            return;
        }
        time_t t=time(NULL);
        struct tm*current_time=localtime(&t);
        users_arr[index+1].DOB.year=current_time->tm_year+1900;
         users_arr[index+1].DOB.month=current_time->tm_mon+1;

        fclose(file);
        FILE *account= fopen("account.txt","a");
        fprintf(account, "%s,%s,%s,%s,%.2lf,%d-%d",users_arr[index+1].account_number,users_arr[index+1].name, users_arr[index+1].address,users_arr[index+1].balance, users_arr[index+1].mobile,users_arr[index+1].DOB.month,users_arr[index+1].DOB.year);
        fclose(account);
        load();
}


    void menu(user users_arr[])
    {
        int choice;
        char username[10];
        // user* users_arr=load( );
        printf("\n select one of the following :\n");
        printf("3-add\n");
        printf("4-delete\n");
        printf("5-modify\n");
        printf("6-search\n");
        printf("7-advanced search\n");
        printf("8-withdraw\n");
        printf("9-deposit\n");
        printf("10-transfer\n");
        printf("11-report\n");
        printf("12-print\n");
        printf("13-quit\n");
        printf("enter your choice :");
        scanf("%d",&choice);

        switch(choice)
        {
        case 3:
            add(users_arr);
            break;
        case 4:
            delete_function(users_arr);
            break;
        case 5:
            modify(users_arr);
            break;
        case 6:
          search_specific_user_data( users_arr);
            break;
        case 7:
            printf("enter the account number");
            scanf("%s",username);
            Advanced_Search(users_arr,username);
            break;
        case 8:
           withdraw(users_arr) ;
            break;
        case 9:

            Deposit( users_arr);
            break;
        case 10:
           transfer(users_arr);
            break;
        case 11:
            report();
            break;
        case 12:
            sort_cases(users_arr);
            break;
        case 13:
            quit ();
            break;
        default:
            printf("invalid please try again:");
            menu(users_arr);
            break;
        }
    }





void sort_cases(user users_arr[])
{
    int choice;

    printf("please choose the type of sorting you want:\n 1-by name\n 2-by balance\n 3-by date\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        sortByName(users_arr);
        break;
    case 2:
        sortByBalance(users_arr);
        break;
//case 3:
    //sortbydate(users_arr);
    //break;
    default:
        printf("invalid please try again:");
        sort_cases(users_arr);
        break;

    }

}



void printSorted(user users_arr[])
{
    for(int i=1; users_arr[i].name[0]!= '\0'; i++)
    {
        printf("Account Number:%s\n",users_arr[i].account_number);
        printf("Name:%s\n",users_arr[i].name);
        printf("Email:%s\n",users_arr[i].address);
        printf("Balance:%f\n",users_arr[i].balance);
        printf("Mobile:%s\n",users_arr[i].mobile);
        printf("Date opened:%d-%d\n",users_arr[i].DOB.month,users_arr[i].DOB.year);
    }
    menu(users_arr);
}
void sortByName(user users_arr[])
{
    user key;
    for(int i=1; users_arr[i].name[0] != '\0'; i++)
    {
        key=users_arr[i];
        int j=i-1;
        while (j>=0 &&(strcasecmp(users_arr[j].name,key.name)>0))
        {
            users_arr[j+1]=users_arr[j]  ;
            j=j-1;
        }
        users_arr[j+1]=key;
    }
    printSorted(users_arr);
}

void sortByBalance(user users_arr[])
{ user key;
    for(int i=1; users_arr[i].name[0] != '\0'; i++)
    {
        key=users_arr[i];
        int j=i-1;
        while (j>=0 &&(users_arr[j].balance)>key.balance)
        {
            users_arr[j+1]=users_arr[j];
            j=j-1;
        }
        users_arr[j+1]=key;
    }
    printSorted(users_arr);
}

    void Advanced_Search(user users_arr[],char keyword)
    {
        int flag=1;
        for(int i=0; users_arr[i].name != '\0'; i++)
        {
            char delim =" ";
            char *token;
            token= strtok(users_arr[i].name,delim);
            while (token != NULL)
            {
                if (strcmp(token,keyword)==0)
                {
                    printf("Account Number:%s\n",users_arr[i].account_number);
                    printf("Name:%s\n",users_arr[i].name);
                    printf("Email:%s\n",users_arr[i].address);
                    printf("Balance:%f\n",users_arr[i].balance);
                    printf("Mobile:%s\n",users_arr[i].mobile);
                    printf("Date opened:%d-%d\n",users_arr[i].DOB.month,users_arr[i].DOB.year);

                }
                token = strtok(NULL,delim);
            }



        }
    }



/*void save_accounts(char name[],char mobile[],char address[],float balance,user users_arr[],int i)
{
    FILE*f;
    f=fopen("account.txt","a");
    if(f==NULL)
    {
        printf("Error occurred in opening the file");
        exit(1);
    }
    if(balance!=users_arr[i].balance)
        users_arr[i].balance=balance;

    if (strcmp(name, users_arr[i].name)!= 0)
        strcpy(users_arr[i].name,name);

    if (strcmp(mobile, users_arr[i].mobile)!= 0)
        strcpy(users_arr[i].mobile,mobile);

    if (strcmp(address, users_arr[i].address)!= 0)
        strcpy(users_arr[i].address,address);

    fprintf(f,"%s,%s,%s,%s,%.2lf,%d,%d\n", users_arr[i].account_number, users_arr[i].name, users_arr[i].mobile, users_arr[i].address, users_arr[i].balance, users_arr[i].DOB.month, users_arr[i].DOB.year);
    fclose(f);
}*/



void save_balance(double balance,user users_arr[],int i)
{
    FILE*f;
    f=fopen("account.txt","w");
    if(f==NULL)
    {
       printf("Error occurred in opening the file\n");
       exit(1);
    }
    if(balance!=users_arr[i].balance);
    users_arr[i].balance=balance;
    int j;
    int m=find_number_of_accounts(users_arr);
   // printf("%daaaa",m);
    for(j=0;j<m;j++)
    {
        fprintf(f, "%s,",users_arr[j].account_number);
        fprintf(f, "%s,",users_arr[j].name);
        fprintf(f, "%s,",users_arr[j].mobile);
        fprintf(f, "%s,",users_arr[j].address);
        fprintf(f, "%lf,",users_arr[j].balance);
        fprintf(f, "%d _%d\n",users_arr[j].DOB.month,users_arr[j].DOB.year);
        load();

    }
    fclose(f);
    printf("successfully saved\n");
}

void save_transactions_withdraw(char username[], user users_arr[],double balance,double withd) {
    FILE *f;
    char flag[30];
    strcpy(flag,username);
    strcat(flag, ".txt");
    f = fopen(flag, "a");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(f, "\nyou withdrew %.3lf pounds and your current balance is %.3lf",withd,balance);

    fclose(f);
}
void save_transactions_deposit(char username[], user users_arr[],double balance,double dep) {
    FILE *f;
      char flag[30];
    strcpy(flag,username);
    strcat(flag, ".txt");
    f = fopen(flag, "a");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(f, "\nyou deposited %.3lf pounds and your current balance is %f",dep,balance);

    fclose(f);
}
void modified_accounts(char name[40],char mobile[15],char address[60],user users_arr[],int i)
{
    FILE*f;
    f=fopen("account.txt","w");
    if(f==NULL)
    {
       printf("Error occurred in opening the file\n");
       exit(1);
    }
   if (strcmp(name, users_arr[i].name)!= 0)
        strcpy(users_arr[i].name,name);

    if (strcmp(mobile, users_arr[i].mobile)!= 0)
        strcpy(users_arr[i].mobile,mobile);

    if (strcmp(address, users_arr[i].address)!= 0)
        strcpy(users_arr[i].address,address);
    int j;
    int m=find_number_of_accounts(users_arr);
    for(j=0;i<m;j++)
    {
        fprintf(f, "%s,",users_arr[j].account_number);
        fprintf(f, "%s,",users_arr[j].name);
        fprintf(f, "%s,",users_arr[j].mobile);
        fprintf(f, "%s,",users_arr[j].address);
        fprintf(f, "%lf,",users_arr[j].balance);
        fprintf(f, "%d_%d\n",users_arr[j].DOB.month,users_arr[j].DOB.year);

    }
    fclose(f);
    printf("successfully saved\n");
}


