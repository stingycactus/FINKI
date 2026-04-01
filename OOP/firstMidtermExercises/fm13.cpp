#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

class Transaction {
private:
    int day;
    int month;
    int year;
    int amount;
    char currency[10];
public:
    Transaction(int day=0, int month=0, int year=0, int amount=0, const char *currency="") {
        this->day=day;
        this->month=month;
        this->year=year;
        this->amount=amount;
        strcpy(this->currency,currency);
    }
    int getAmount() { return amount; }
    char *getCurrency() { return currency; }
    int getMonth() { return month; }
    friend ostream &operator<<(ostream &os, const Transaction &t) {
        os<<setw(2)<<setfill('0')<<t.day<<"/"<<setw(2)<<setfill('0')<<t.month<<"/"<<t.year<<" "<<t.amount<<" "<<t.currency<<'\n';
        return os;
    }

    int day1() const {
        return day;
    }

    int year1() const {
        return year;
    }
};

int main() {
    int n;
    cin>>n;
    Transaction transactions[500];
    for (int i = 0; i<n; i++) {
        char currency[10];
        int amount;
        int day, month, year;
        char date[20];
        cin>>date;
        cin>>amount;
        cin>>currency;
        sscanf(date, "%d/%d/%d", &day, &month, &year);
        transactions[i]=Transaction(day,month,year,amount,currency);
    }
    int counter=1;
    int sum=0;
    for (int i = 0; i<n; i++) {
        if (transactions[i].day1()>=1 && transactions[i].day1()<=31
            && transactions[i].getMonth()>=1 && transactions[i].getMonth() <=12
            && transactions[i].year1()>=2013 && transactions[i].year1()<=2015
            && transactions[i].getAmount()>1000
            && strcmp(transactions[i].getCurrency(),"MKD")==0) {
            cout<<counter<<". "<<transactions[i];
            sum+=transactions[i].getAmount();
            counter++;
        }
    }
    cout<<"Total: "<<sum<<" MKD";
    return 0;
}