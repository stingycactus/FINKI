//
// Created by cactus on 09/03/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
struct Date {
    int day;
    int month;
    int year;
    int dateDifference (Date other) {
        int days = abs(day - other.day);
        days+= abs((month - other.month)*30);
        days+= abs((year - other.year) * 365);
        return days;
    }
    void readDate() {
        cin >> day >> month >> year;
    }
    void printDate() {
        cout << day << "/" << month << "/" << year << endl;
    }
};
int main() {
    Date d1;
    Date d2;
    d1.readDate();
    d2.readDate();
    d1.printDate();
    d2.printDate();
    cout<<d1.dateDifference(d2)<<endl;
    return 0;
}