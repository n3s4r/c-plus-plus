#include <iostream>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    double balance;

public:
    BankAccount(string n, int accNo, double bal) {
        name = n;
        accountNumber = accNo;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        }
    }

    void display() {
        cout << "\n--- Account Details ---" << endl;
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    BankAccount acc("Nesar", 12345, 1000.0);

    acc.display();

    acc.deposit(500);
    acc.withdraw(300);
    acc.withdraw(1500);

    acc.display();

    return 0;
}
