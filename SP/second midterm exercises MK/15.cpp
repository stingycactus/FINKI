//
// Created by cactus on 11/01/2026.
//
#include <algorithm>
#include <iostream>
using namespace std;
int poramnet(int number) {
    if (!number) {
        return 0;
    }
    int digit;
    if (number%10==9) {
        digit=7;
    }
    else {
        digit=number%10;
    }
    return poramnet(number/10) * 10 + digit;
}
int main() {
    int n;
    int poramneti[100];
    int index = 0;
    while (cin>>n) {
        poramneti[index] = poramnet(n);
        index++;
    }
    sort(poramneti, poramneti + index);
    int end = 5;
    if (index<end) {
        end=index;
    }
    for (int i = 0; i<end; i++) {
        cout<<poramneti[i]<<' ';
    }
    return 0;
}