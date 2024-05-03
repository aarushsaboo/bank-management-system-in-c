/*Typedef Method:
typedef struct {
    int accountNumber;
    char name[100];
    float balance;
} Account;
This method defines the structure Account and simultaneously creates an alias Account for the structure. With this approach,
you can directly use Account as the type name whenever you declare variables of this structure type, making the code cleaner and more readable.

Differences:
Typedef Method:
    It simplifies the syntax when declaring variables of the structure type.
    It provides a clearer and more concise way to define the structure and use it throughout the code.
    It allows you to avoid using the struct keyword repeatedly when declaring variables.
Using a Pointer:
    It separates the definition of the structure from the declaration of variables.
    It allows for dynamic memory allocation and manipulation of structure instances through pointers.
    It may be more suitable when you need to allocate memory dynamically or when dealing with complex data structures involving pointers.
    In summary, both methods are acceptable, and the choice between them depends on the specific requirements and coding style preferences of the developer.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
char name[100];
int accno;
float balance;
}Account;

void createAccount(Account Accounts[], int *numAccounts,FILE *file);
void viewAccount(Account Accounts[], int *numAccounts);
void depositMoney(Account Accounts[], int *numAccounts, int acUpdated, float balUpdated);
void withdrawMoney(Account Accounts[], int *numAccounts, int acUpdated, float balUpdated);
void searchAccount(Account Accounts[], int *numAccounts, int acno);

int main(){
    int choice;
    int numAccounts=0;
    Account Accounts[100];
    int accNo;float bal;
    FILE *file;
    char filename[] = "accounts.txt";
    // Open the file in write mode (create if not exist, truncate if exist)
    file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    while(1){
        printf("\nBank Management System\n");
        printf("1. Create a new account\n");
        printf("2. View account details\n");
        printf("3. Deposit money\n");
        printf("4. Withdraw money\n");
        printf("5. Search for an account\n");
        printf("6. View Accounts from file");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                createAccount(Accounts, (&numAccounts), file);
                break;
            case 2:
                viewAccount(Accounts, (&numAccounts));
                break;
            case 3:
                printf("Enter account no and money to be deposited");
                scanf("%d %f",&accNo,&bal);
                depositMoney(Accounts,(&numAccounts),accNo, bal);
                break;
            case 4:
                printf("Enter account no and money to be withdrawed");
                scanf("%d %f",&accNo,&bal);
                withdrawMoney(Accounts,(&numAccounts),accNo, bal);
                break;
            case 5:
                printf("Enter account no to be searched");
                scanf("%d",&accNo);
                searchAccount(Accounts, (&numAccounts), accNo);
                break;
            case 6:
                viewAccounts(file);
                break;
            case 7:
                printf("Exiting...");
                exit(0);

            default:
                printf("Invalid input.Please try again.");
        }
    }
    return(0);
}
void createAccount(Account Accounts[], int *numAccounts, FILE *file){
    printf("Enter name");
    scanf("%s",&(Accounts[*numAccounts].name));
    printf("Enter A/C no");
    scanf("%d",&(Accounts[*numAccounts].accno));
    printf("Enter balance in thousands");
    scanf("%f",&(Accounts[*numAccounts].balance));

    // Write account details to the file
    fprintf(file, "Account Number: %d\n", Accounts[*numAccounts].accno);
    fprintf(file, "Name: %s\n", Accounts[*numAccounts].name);
    fprintf(file, "Balance: %.2f\n\n", Accounts[*numAccounts].balance);

    printf("Account details written to file successfully!\n");
    (*numAccounts)++;

}

void viewAccount(Account Accounts[], int *numAccounts){
    printf("A/C no\t Balance\t Name\n");
    for(int i=0; i<(*numAccounts);i++){
        printf("%d \t%f\t %s",Accounts[i].accno,Accounts[i].balance, Accounts[i].name);
        printf("\n");
    }
}
void depositMoney(Account Accounts[], int *numAccounts, int acUpdated, float balUpdated){
    for(int i=0;i<(*numAccounts);i++){
        if(Accounts[i].accno==acUpdated){
            Accounts[i].balance+=balUpdated;
        }
    }
}
void withdrawMoney(Account Accounts[], int *numAccounts, int acUpdated, float balUpdated){
    for(int i=0;i<(*numAccounts);i++){
        if(Accounts[i].accno==acUpdated){
            Accounts[i].balance-=balUpdated;
        }
    }
}
void searchAccount(Account Accounts[], int *numAccounts, int acno){
    for(int i=0; i<*numAccounts;i++){
        if(Accounts[i].accno==acno){
            printf("%d\t %f\t %s\n",Accounts[i].accno,Accounts[i].balance,Accounts[i].name);
            break;
        }
    }
}


// Function to view account details from file
void viewAccounts(FILE *file) {
    Account account;
    printf("\nAccount details:\n");
    rewind(file); // Move file pointer to the beginning
    while (fscanf(file, "Account Number: %d\nName: %s\nBalance: %f\n\n", &account.accno, account.name, &account.balance) != EOF) {
        printf("Account Number: %d\n", account.accno);
        printf("Name: %s\n", account.name);
        printf("Balance: %.2f\n\n", account.balance);
    }

}
//within the function prototype, make sure to use the same arguments


/* While creating an account, we're printing it into the file
    While viewing it, we're rewinding, scanning the file, for instances of a given format,
    This while loop reads data from the file using fscanf() and assigns it to the members of the account struct (accno, name, and balance). The loop continues until fscanf() returns EOF, which indicates the end of the file.

typescript
Copy code
- `%d` reads an integer (`accno`) from the file.
- `%s` reads a string (`name`) from the file.
- `%f` reads a floating-point number (`balance`) from the file.
*/


/* We haven't used an & with account.name in the while loop:
In C, when working with strings using the %s format specifier with scanf() or fscanf(),
you don't need to use the address-of operator (&) with a character array (string) variable. This is because a character array already represents the memory address of its first element.So, when you
write account.name in the fscanf() call, you're essentially passing the address of the first element of the name array to fscanf(). This is equivalent to passing &account.name[0], which is the
address of the first character in the name array.
Therefore, in the context of reading a string into a character array using fscanf(), you don't need to use & with account.name. The compiler automatically interprets account.name as the address of
the first character in the name array.

*/




