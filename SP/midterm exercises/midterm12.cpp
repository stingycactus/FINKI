//
// Created by cactus on 04/11/2025.
//
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int power = 1;
        int rest = a / 10;
        int temp = rest;
        while (temp > 0) {
            power *= 10;
            temp /= 10;
        }
        int lastdigit = a % 10;
        int lasttofirst = lastdigit * power + rest;
        if (lasttofirst>b) {
            cout<<"YES";
        }
        else {
            cout<<"NO";
        }
        cout<<endl;
    }
    return 0;
}
