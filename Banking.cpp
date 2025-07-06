#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(const string& t, double a) {
        type = t;
        amount = a;

        // Get current time
        time_t now = time(0);
        date = ctime(&now);
        date.pop_back(); // Remove newline character
    }

    void show() const {
        cout << type << " of ₹" << amount << " on " << date << endl;
    }
};

// Account class
class Account {
private:
    static int nextAccountNumber;

public:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

    Account() {
        accountNumber = ++nextAccountNumber;
        balance = 0.0;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "₹" << amount << " deposited successfully.\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        cout << "₹" << amount << " withdrawn successfully.\n";
        return true;
    }

    bool transfer(Account &receiver, double amount) {
        if (withdraw(amount)) {
            receiver.deposit(amount);
            transactions.emplace_back("Transfer to Acc#" + to_string(receiver.accountNumber), amount);
            return true;
        }
        return false;
    }

    void showRecentTransactions(int count = 5) const {
        cout << "\n--- Recent Transactions (Up to " << count << ") ---\n";
        int start = max(0, (int)transactions.size() - count);
        for (int i = start; i < transactions.size(); ++i) {
            transactions[i].show();
        }
        cout << "--------------------------------------\n";
    }

    void showAccountInfo() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Balance: ₹" << balance << "\n";
        showRecentTransactions();
    }
};

int Account::nextAccountNumber = 1000;

// Customer class
class Customer {
public:
    string name;
    int customerID;
    Account account;

    Customer(string n, int id) : name(n), customerID(id) {}

    void showDetails() const {
        cout << "\nCustomer ID: " << customerID << "\n";
        cout << "Name: " << name << "\n";
        account.showAccountInfo();
    }
};

// Main banking system
int main() {
    vector<Customer> customers;
    int choice, custID, receiverID;
    string name;
    double amount;

    while (true) {
        cout << "\n==== Banking System Menu ====\n";
        cout << "1. Create New Customer\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Info & Recent Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cin.ignore();
            cout << "Enter Customer Name: ";
            getline(cin, name);
            custID = customers.size() + 1;
            customers.emplace_back(name, custID);
            cout << "Customer created with ID: " << custID
                 << ", Account#: " << customers.back().account.accountNumber << endl;
            break;

        case 2:
            cout << "Enter Customer ID: ";
            cin >> custID;
            if (custID > 0 && custID <= customers.size()) {
                cout << "Enter amount to deposit: ₹";
                cin >> amount;
                customers[custID - 1].account.deposit(amount);
            } else {
                cout << "Invalid Customer ID!\n";
            }
            break;

        case 3:
            cout << "Enter Customer ID: ";
            cin >> custID;
            if (custID > 0 && custID <= customers.size()) {
                cout << "Enter amount to withdraw: ₹";
                cin >> amount;
                customers[custID - 1].account.withdraw(amount);
            } else {
                cout << "Invalid Customer ID!\n";
            }
            break;

        case 4:
            cout << "Enter Sender Customer ID: ";
            cin >> custID;
            cout << "Enter Receiver Customer ID: ";
            cin >> receiverID;
            if (custID > 0 && custID <= customers.size() && receiverID > 0 && receiverID <= customers.size()) {
                cout << "Enter amount to transfer: ₹";
                cin >> amount;
                if (customers[custID - 1].account.transfer(customers[receiverID - 1].account, amount)) {
                    cout << "Transfer successful.\n";
                }
            } else {
                cout << "Invalid Customer IDs!\n";
            }
            break;

        case 5:
            cout << "Enter Customer ID to view info: ";
            cin >> custID;
            if (custID > 0 && custID <= customers.size()) {
                customers[custID - 1].showDetails();
            } else {
                cout << "Invalid Customer ID!\n";
            }
            break;

        case 6:
            cout << "Exiting the system. Thank you!\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

/*1.	OUTPUT OF BANKING SYSTEM
 
==== Banking System Menu ====
1. Create New Customer
2. Deposit Money
3. Withdraw Money
4. Transfer Funds
5. View Account Info & Recent Transactions
6. Exit
Enter your choice: 1
Enter Customer Name: Roshan
Customer created with ID: 1, Account#: 1001

Enter your choice: 2
Enter Customer ID: 1
Enter amount to deposit: ₹5000
₹5000 deposited successfully.

Enter your choice: 5
Enter Customer ID to view info: 1
Customer ID: 1
Name: Roshan
Account Number: 1001
Balance: ₹5000
--- Recent Transactions (Up to 5) ---
Deposit of ₹5000 on Fri Jul  5 18:07:53 2025
OUTPUT  OF  CGPA  CA*/
