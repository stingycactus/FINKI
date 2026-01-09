//
// Created by cactus on 09/01/2026.
//
#include <iostream>
using namespace std;
int evenOddSumRecursion(int number) {
    if (!number) {
        return 0;
    }
    int ld = number%10;
    if (ld%2==0) {
        cout<< ld << ' ';
    }
    int sum = ld;
    sum+=evenOddSumRecursion(number/10);
    if (ld%2==1) {
        cout<< ld << ' ';
    }
    return sum;

}
int main() {
    int n;
    while (cin>>n) {
        cout<<evenOddSumRecursion(n);
    }
    return 0;
}