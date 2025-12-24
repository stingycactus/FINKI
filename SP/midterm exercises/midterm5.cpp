//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int today, n;
    cin >> today;
    cin >> n;
    int current_year = today % 10000;
    int current_month = (today / 10000) % 100;
    int current_day = today / 1000000;
    for (int i = 0; i < n; i++) {
        int date;
        cin >> date;
        int year = date % 10000;
        int month = (date / 10000) % 100;
        int day = date / 1000000;
        bool is_adult = false;
        int age = current_year - year;
        if (age > 18) {
            is_adult = true;
        } else if (age == 18) {
            if (current_month > month) {
                is_adult = true;
            } else if (current_month == month && current_day >= day) {
                is_adult = true;
            }
        }
        cout << (is_adult ? "YES" : "NO") << endl;
    }

    return 0;
}
