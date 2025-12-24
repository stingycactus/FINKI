//
// Created by cactus on 03/11/2025.
//
#include <iostream>
#include <climits>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int min = 2, max = 2;
    int mindiv, maxdiv;
    for (int i = a; i < b; i++) {
        int divisors = 0;
        for (int j = 1; j <= i; j++) {
            if (i%j == 0) {
                divisors++;
            }
        }
        if (divisors >= max) {
            max=divisors;
            maxdiv = i;
        }
        else if (divisors <= min) {
            min=divisors;
            mindiv = i;
        }
    }
    cout<<"MAX: "<<maxdiv<<endl;
    cout<<"MIN: "<<mindiv<<endl;

    return 0;
}
