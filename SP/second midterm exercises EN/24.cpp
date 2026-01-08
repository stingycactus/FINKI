//
// Created by cactus on 1/8/2026.
//
#include <algorithm>
#include <iostream>
using namespace std;
int parcom(int number) {
    if (!number) {
        return 0;
    }
    int ld = number%10;
    if (ld%2==0) {
        // ld+1, then rest
        return parcom(number/10) * 10 + ld + 1;
    }
    if (ld%2!=0) {
        // ld-1, then rest
        return parcom(number/10) * 10 + ld - 1;
    }
}
int main() {
    int n;
    int complements[100];
    int index = 0;
    while (cin>>n) {
        complements[index++] = parcom(n);
    }
    sort(complements, complements + index);
    int elems = 5;
    if (index<elems) {
        elems=index;
    }
    for (int i = 0; i<elems; i++) {
        cout<<complements[i]<<' ';
    }
    return 0;
}