//
// Created by cactus on 4/20/2026.
//
#include <iostream>
using namespace std;

class debitAccount {
protected:
    string name;
    long accNumber;
    double balance;

public:
    debitAccount(const string &_name, long _accNumber, double _balance) : name(_name),
                                                                          accNumber(_accNumber),
                                                                          balance(_balance) {
    }

    void showInfo() {
        cout << "Name: " << name << '\n';
        cout << "Acc Number: " << accNumber << '\n';
        cout << "Balance: " << balance << '\n';
    }

    void deposit(int amount) {
        balance += amount;
    }

    void withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "You cannot withdraw since you do not have enough money" << '\n';
        }
    }
};

class creditAccount : public debitAccount {
private:
    int limit;
    int interestRate;

public:
    creditAccount(const string &_name, long _accNumber, double _balance,int _limit, int _interestRate=0) :
    debitAccount(_name, _accNumber, _balance), limit(_limit), interestRate(_interestRate) {}
    void showInfo() {
        debitAccount::showInfo();
        cout << "Limit: " << limit << '\n';
        cout << "Interest Rate: " << interestRate << '\n';
    }
    void deposit(int amount) {
        debitAccount::deposit(amount);
    }
    void withdraw(int amount) {
        if (balance>=amount) {
            debitAccount::deposit(amount);
        }
        else {
            if ((balance+limit) >= amount ) {
                balance -= amount;
            }
            else {
                cout<<"You cannot withdraw this much."<<'\n';
            }
        }
    }
};

int main() {
    debitAccount d("Pero Perovski", 6, 100000);
    creditAccount ca("Mitko Mitkovski", 10, 5000, 1000);
    d.showInfo();
    d.deposit(50000);
    d.showInfo();
    d.withdraw(600000);
    d.showInfo();
    ca.showInfo();
    ca.deposit(500);
    ca.showInfo();
    ca.withdraw(6200);
    ca.showInfo();
    return 0;
}
