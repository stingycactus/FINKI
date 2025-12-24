//
// Created by cactus on 04/11/2025.
//
#include <iostream>
using namespace std;
int main() {
    int m,n;
    cin>>m>>n;
    bool number = false;
    int num;
    for (int i = m; i <= n; i++) {
        int temp = i;
        while (temp>0) {
            int digit = temp % 10;
            if (digit%2!=0) {
                number = false;
                break;
            }
            else {
                number = true;
            }
            temp/=10;
        }
        if (number) {
            cout<<i;
            break;
        }
    }
    if (!number) {
        cout<<"NSN";
    }
    return 0;
}