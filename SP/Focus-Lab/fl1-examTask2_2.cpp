//
// Created by cactus on 6/8/2026.
//
#include <iostream>
using namespace std;

bool isValidNumber(int number) {
    int temp = number;
    int sum1=0;
    int sum2=0;
    while (temp>0) {
        sum1+=temp%10;
        sum2+=temp/10%10;
        temp/=100;
    }
    return sum1==sum2;
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