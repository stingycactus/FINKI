//
// Created by cactus on 15/11/2025.
//
#include <iostream>
#include <cmath>
using namespace std;
// n amount of numbers, read triple ints (a,b,c), rez = 2 * min - abs(min-a), print out rez + rez from previous triples (0 starting value), print min if rez not > min
int main () {
    int n;
    cin>>n;
    int rez1 = 0;
    for (int i = 0; i<n; i++) {
        int x,y,z, min;
        cin>>x>>y>>z;
        if (x<z && x<y) {
            min=x;
        }
        else if (y<x && y<z) {
            min=y;
        }
        else {
            min=z;
        }
        int rez2 = 2 * min - abs(min-x);
        if (rez2>min) {
            cout<<rez2+rez1<<'\n';
        }
        else {
            cout<<min<<'\n';
        }
        rez1=rez2;
    }
    return 0;
}