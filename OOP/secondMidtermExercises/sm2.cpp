//
// Created by cactus on 5/25/2026.
//
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

class User {
protected:
    string username;
    string password;
    string email;
public:
    User(const string &username="", const string &password="", const string &email="")
    : username(username), password(password), email(email) {}
    virtual void printDetail() const = 0;
    virtual int checkPasswordStrength() const = 0;
};

class RegularUser : public User {
private:
    bool has2FA;
public:
    RegularUser(const string &username="", const string &password="", const string &email="", bool has2FA=false)
    : User(username, password, email), has2FA(has2FA) {}
    int checkPasswordStrength() const override {
        int totalStrength=0;
        totalStrength+= 2 * (password.length()>=6);
        for (int i = 0; i<password.length(); i++) {
            if (islower(password[i])) {
                totalStrength+=1;
                break;
            }
        }
        totalStrength+= 1 * !(isdigit(password[password.length()-1]));
        totalStrength+= 1 * has2FA;
        return totalStrength;
    }
    void printDetail() const override {
        cout<<username<<" (Regular) - Email: "<<email<<" - 2FA: "<<(has2FA ? "Yes" : "No")<<" - Strength: "<<checkPasswordStrength()<<'\n';
    }
};

class AdminUser : public User {
private:
    string department;
    bool usesPasswordManager;
public:
    AdminUser(const string &username="", const string &password="", const string &email="", const string &department="", bool usesPasswordManager=false)
    : User(username,password,email), department(department), usesPasswordManager(usesPasswordManager) {}
    int checkPasswordStrength() const override {
        int totalStrength=0;
        totalStrength+= 2 * (password.length()>=10);
        for (int i = 0; i<password.length(); i++) {
            if (isupper(password[i])) {
                totalStrength+=2;
                break;
            }
        }
        totalStrength+= 1 * !(isupper(password[0]));
        totalStrength+= 2 * usesPasswordManager;
        return totalStrength;
    }
    void printDetail() const override {
        cout<<username<<" (Admin) - Email: "<<email<<" - Dept: "<<department<<" - PM: "<<(usesPasswordManager ? "Yes" : "No")<<" - Strength: "<<checkPasswordStrength()<<'\n';
    }
};
void printAdminUserStats(User** users, int n) {

    int totalStrength=0;
    int counter=0;
    cout<<"--- Admin Users ---"<<'\n';

    for (int i = 0; i<n; i++) {
        if (dynamic_cast<AdminUser*>(users[i])) {
            totalStrength+=users[i]->checkPasswordStrength();
            counter++;
            users[i]->printDetail();
        }
    }
    if (!counter) {
        cout<<"No Admin Users found in the array!"<<'\n';
    }
    else {
        cout << fixed << setprecision(2);
        cout<<"Average Admin Strength: "<<static_cast<float>(totalStrength)/counter<<'\n';
    }
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    User** users = new User*[n];

    for (int i = 0; i < n; ++i) {
        string username, password, email;
        cin >> type;
        cin.ignore();
        getline(cin, username);
        getline(cin, password);
        getline(cin, email);

        if (type == 1) {
            bool has2FA;
            cin >> has2FA;
            cin.ignore();
            users[i] = new RegularUser(username, password, email, has2FA);
        } else {
            string department;
            bool usesPM;
            getline(cin, department);
            cin >> usesPM;
            cin.ignore();
            users[i] = new AdminUser(username, password, email, department, usesPM);
        }
    }

    if (testCase == 1) {
        cout << "Abstract and child classes OK" << endl;
    } else if (testCase == 2) {
        for (int i = 0; i < n; ++i) {
            cout << users[i]->checkPasswordStrength() << endl;
        }
        cout << "checkPasswordStrength method OK" << endl;
    } else if (testCase == 3) {
        for (int i = 0; i < n; ++i) {
            users[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    } else if (testCase == 4) {
        printAdminUserStats(users, n);
        cout << "printAdminUserStats method OK" << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete users[i];
    }
    delete[] users;

    return 0;
}