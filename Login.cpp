#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;


bool validateInput(const string& username, const string& password) {
    if (username.length() < 4 || password.length() < 6) return false;
    bool hasUpper = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasDigit;
}


bool isDuplicateUsername(const string& username) {
    ifstream file("users/" + username + ".txt");
    return file.good();
}


void registerUser(const string& username, const string& password) {
    if (!validateInput(username, password)) {
        cout << "Error: Username must be at least 4 characters, and password must be at least 6 characters with an uppercase letter and a digit." << endl;
        return;
    }
    if (isDuplicateUsername(username)) {
        cout << "Error: Username already exists. Please choose a different one." << endl;
        return;
    }
    ofstream file("users/" + username + ".txt");
    if (file.is_open()) {
        file << password;
        file.close();
        cout << "Registration successful! You can now log in." << endl;
    } else {
        cout << "Error: Unable to create user file." << endl;
    }
}


void loginUser(const string& username, const string& password) {
    ifstream file("users/" + username + ".txt");
    if (!file.good()) {
        cout << "Error: Username not found." << endl;
        return;
    }
    string storedPassword;
    getline(file, storedPassword);
    if (storedPassword == password) {
        cout << "Login successful! Welcome, " << username << "!" << endl;
    } else {
        cout << "Error: Incorrect password." << endl;
    }
    file.close();
}

int main() {
    int choice;
    string username, password;


    system("mkdir users 2> nul"); 

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            registerUser(username, password);
        } else if (choice == 2) {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            loginUser(username, password);
        } else if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
/*3.	OUTPUT  OF  LOGIN AND  REGISTRATION  SYSTEM

1. Register
2. Login
3. Exit
Enter choice: 1*/
