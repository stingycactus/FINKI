//
// Created by cactus on 08/01/2026.
//
#include <iostream>
using namespace std;
int main() {
    int a,b,c;
    while (cin>>a>>b>>c) {
        int temp1 = a/10;
        int temp2 = b/10;
        int aCount = 0;
        int bCount = 0;
        while (temp1 > 0|| temp2>0) {
            int ld1 = temp1%10;
            int ld2 = temp2%10;
            if (ld1==c) {
                aCount++;
            }
            if (ld2==c) {
                bCount++;
            }
            temp1/=100;
            temp2/=100;
        }
        if (bCount > aCount) {
            cout<<b;
        }
        else {
            cout<<a;
        }
        cout<<'\n';
    }

    return 0;
}