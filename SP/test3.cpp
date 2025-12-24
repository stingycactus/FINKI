//
// Created by cactus on 14/11/2025.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    bool zigzag = true;
    bool find = true;
    int n;
    while (cin >> n) {
        if (n > 10) {
            int temp = n;
            if (temp % 10 < 5) zigzag = false;
            while (temp > 0) {
                int ld = temp % 10;
                if (zigzag && ld < 5 || !zigzag && ld >= 5) {
                    find = false;
                }
                zigzag = !zigzag;
                temp /= 10;
            }
            if (find) {
                cout << n << endl;
            }
            zigzag = true;
            find = true;
        }
    }
    return 0;
}