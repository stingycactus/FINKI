#include <iostream>
#include <cstring>
#include <string>
class UserProfile;
using namespace std;

class Bill {
private:
    char *billNumber;
    int expense;
    char dateIssued[8];
    bool paid;
public:
    Bill(const char *billNumber="", int expense=0, const char *dateIssued="", bool paid = false) {
        this->billNumber=new char[strlen(billNumber)+1];
        strcpy(this->billNumber,billNumber);
        this->expense=expense;
        strcpy(this->dateIssued,dateIssued);
        this->paid=paid;
    }
    Bill(const Bill &other) {
        this->billNumber=new char[strlen(other.billNumber)+1];
        strcpy(this->billNumber,other.billNumber);
        this->expense=other.expense;
        strcpy(this->dateIssued,other.dateIssued);
        this->paid=other.paid;
    }
    ~Bill() {
        delete [] billNumber;
    }
    Bill &operator=(Bill otherBill) {
        if (this == &otherBill) {
            return *this;
        }
        delete [] billNumber;
        this->billNumber = new char[strlen(otherBill.billNumber)+1];
        strcpy(billNumber,otherBill.billNumber);
        this->expense=otherBill.expense;
        strcpy(this->dateIssued, otherBill.dateIssued);
        this->paid=otherBill.paid;
        return *this;
    }
    bool operator==(Bill otherBill) {
        if (this==&otherBill) {
            return true;
        }
        if (strlen(billNumber)==strlen(otherBill.billNumber)) {
            for (int i = 0; i<strlen(billNumber); i++) {
                if (billNumber[i]!=otherBill.billNumber[i]) {
                    return false;
                }
            }
        }
        return true;
    }
    friend ostream &operator<<(ostream &os, Bill bill) {
        os<<bill.billNumber<<"("<<bill.dateIssued<<")"<<" - "<<bill.expense<<'\n';
        return os;
    }
    friend UserProfile;
};

class UserProfile {
private:
    char username[31];
    Bill billsArray[30];
    int numberOfBills;
public:
    UserProfile(const char *username = "", Bill *billsArray=nullptr, int numberOfBills=0) {
        strcpy(this->username,username);
        this->numberOfBills=numberOfBills;
        for (int i = 0; i<numberOfBills; i++) {
            this->billsArray[i]=billsArray[i];
        }
    }
    UserProfile &operator+=(Bill bill) {
        for (int i = 0; i<numberOfBills; i++) {
            if (billsArray[i]==bill) {
                cout<<"The bill already exists"<<'\n';
                return *this;
            }
        }
        billsArray[numberOfBills]=bill;
        numberOfBills++;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const UserProfile &user) {
        os<<"Pending bills for "<<user.username<<" are:"<<'\n';
        for (int i = 0; i<user.numberOfBills; i++) {
            if (!user.billsArray[i].paid) {
                cout<<user.billsArray[i];
            }
        }
        return os;
    }
};
int totalDue(int month, int year) {
    // maybe later because i thought MMYYYY was string not 2 ints
}

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator <<-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += & << -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
