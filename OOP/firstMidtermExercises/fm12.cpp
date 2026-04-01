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
};

int main() {
    int n;
    cin>>n;
    Transaction transactions[500];
    for (int i = 0; i<n; i++) {
        char currency[10];
        int amount;
        int day, month, year;
        cin>>currency;
        cin>>amount;
        char date[20];
        cin>>date;
        sscanf(date, "%d/%d/%d", &day, &month, &year);
        transactions[i]=Transaction(day,month,year,amount,currency);
    }
    int counter=1;
    int sum=0;
    for (int i = 0; i<n; i++) {
        if (transactions[i].getMonth()<=3 && transactions[i].getAmount()<5000 && strcmp(transactions[i].getCurrency(),"USD")==0) {
            cout<<counter<<". "<<transactions[i];
            sum+=transactions[i].getAmount();
            counter++;
        }
    }
    cout<<"Total: "<<sum<<" USD";
    return 0;
}