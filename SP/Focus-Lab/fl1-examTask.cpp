//
// Created by cactus on 6/8/2026.
//
#include <iostream>
using namespace std;

bool isValidNumber(int number) {
    int temp = number;
    bool flag = true;
    while (temp>100) {
        int ld = temp%10;
        int sld = (temp/10)%10;
        if (abs(ld-sld)!=1) {
            flag=false;
            break;
        }
        temp/=10;
    }
    return flag;
}

int main() {
    int x;
    cin>>x;
    bool found = false;
    for (int i = 10; i<=x/2; i++) {
        if ((x-i>=10) && isValidNumber(i) && isValidNumber(x-i)) {
            cout<<i<<" "<<x-i<<'\n';
            found=true;
        }
    }
    cout<<(found ? "Yes" : "No")<<'\n';
    return 0;
}