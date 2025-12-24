//
// Created by cactus on 03/11/2025.
//
// 55650
#include <iostream>
using namespace std;

int main() {
    int a, b, counter=0;
    cin >> a >> b;
    for (int i = a; i <= b; i++) {
        int num = i;
        int lastdigit = num % 10;
        int rest = num / 10;
        int temp = rest;
        int power = 1;
        while (temp > 0) {
            power *= 10;
            temp /= 10;
        }
        int firstdigit = num / power;
        int middledigits = rest % (power / 10); // doesnt work cuz 025 -> 25, removes trailing zero
        int first_and_last = firstdigit * 10 + lastdigit;
        int temp2 = rest;
        int product_of_middles = 1;
        while (temp2 >= 10) {
            int digit = temp2 % 10;
            product_of_middles *= digit;
            temp2 /= 10;
        }
        if (product_of_middles!=0&&product_of_middles % first_and_last == 0) {
            cout<<num<<" -> "<<"("<<product_of_middles<<" == "<<first_and_last<< " * "<<product_of_middles/first_and_last<<")"<<endl;
            counter++;
        }
    }
    cout<<counter;
    return 0;
}
