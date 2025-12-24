//
// Created by cactus on 12/11/2025.
//
#include <iostream>
using namespace std;
int main() {
    int N,X;
    cin>>N>>X;
    for (int i = N-1; i>=0; i--) {
        int temp = i;
        bool totallyDifferent = true;
        while (temp>0) {
            int digitX = temp%10;
            int temp2=X;
            while (temp2>0) {
                int digitY=temp2%10;
                if (digitY==digitX) {
                    totallyDifferent = false;
                    break;
                }
                temp2/=10;
            }
            temp/=10;
        }
        if (totallyDifferent) {
            cout<<i;
            break;
        }
    }
    return 0;
}