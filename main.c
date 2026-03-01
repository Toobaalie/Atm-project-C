#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 100

typedef struct {
    char type[10];
    float amount;
    float balanceAfter;
} Transaction;

void showTable(char name[], long long accNumber, float balance) {
    printf("\n+----------------------+--------------------------+\n");
    printf("| %-20s | %-24s |\n", "Account Holder", name);
    printf("+----------------------+--------------------------+\n");
    printf("| %-20s | %-24lld |\n", "Account Number", accNumber);
    printf("+----------------------+--------------------------+\n");
    printf("| %-20s | %-24.2f |\n", "Current Balance", balance);
    printf("+----------------------+--------------------------+\n");
}

void showHistory(Transaction history[], int count) {
    if (count == 0) {
        printf("\nNo transactions yet.\n");
        return;
    }

    printf("\nTransaction History:\n");
    printf("+------------+------------+----------------+\n");
    printf("| Type       | Amount     | Balance After  |\n");
    printf("+------------+------------+----------------+\n");

    for (int i = 0; i < count; i++) {
        printf("| %-10s | %-10.2f | %-14.2f |\n",
               history[i].type, history[i].amount, history[i].balanceAfter);
    }

    printf("+------------+------------+----------------+\n");
}

int main() {
    char name[50];
    long long accNumber;
    float balance;
    int choice;
    float amount;
    int pin, enteredPin;
    int attempts = 0;

    Transaction history[MAX_TRANSACTIONS];
    int transactionCount = 0;

    printf("Create Your ATM Account\n");
    printf("-----------------------\n");

    printf("Enter account holder name: ");
    scanf(" %[^\n]", name);   // FIXED: Reads full name with spaces

    printf("Enter account number: ");
    scanf("%lld", &accNumber);

    printf("Set your 4-digit ATM PIN: ");
    scanf("%d", &pin);

    printf("Enter starting balance: ");
    scanf("%f", &balance);

    printf("\nATM Login\n");
    printf("---------\n");

    while (attempts < 3) {
        printf("Enter PIN: ");
        scanf("%d", &enteredPin);

        if (enteredPin == pin) {
            printf("\nLogin successful!\n");
            break;
        } else {
            attempts++;
            printf("Incorrect PIN. Attempts left: %d\n", 3 - attempts);
        }

        if (attempts == 3) {
            printf("\nYour card has been blocked for security reasons.\n");
            return 0;
        }
    }

    while (1) {
        printf("\nATM Menu\n");
        printf("--------\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. View Transaction History\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showTable(name, accNumber, balance);
                break;

            case 2:
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);

                if (amount > 0) {
                    balance += amount;
                    printf("Amount deposited successfully.\n");

                    if (transactionCount < MAX_TRANSACTIONS) {
                        strcpy(history[transactionCount].type, "Deposit");
                        history[transactionCount].amount = amount;
                        history[transactionCount].balanceAfter = balance;
                        transactionCount++;
                    } else {
                        printf("Transaction log is full!\n");
                    }

                    showTable(name, accNumber, balance);
                } else {
                    printf("Invalid amount.\n");
                }
                break;

            case 3:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);

                if (amount <= 0) {
                    printf("Invalid amount.\n");
                } else if (amount > balance) {
                    printf("Insufficient funds.\n");
                } else {
                    balance -= amount;
                    printf("Withdrawal successful.\n");

                    if (transactionCount < MAX_TRANSACTIONS) {
                        strcpy(history[transactionCount].type, "Withdraw");
                        history[transactionCount].amount = amount;
                        history[transactionCount].balanceAfter = balance;
                        transactionCount++;
                    } else {
                        printf("Transaction log is full!\n");
                    }

                    showTable(name, accNumber, balance);
                }
                break;

            case 4:
                showHistory(history, transactionCount);
                break;

            case 5:
                printf("\nThank you for using the ATM.\n");
                return 0;

            default:
                printf("Invalid choice. Please select between 1-5.\n");
        }
    }

    return 0;
}
