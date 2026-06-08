//
// Created by cactus on 6/8/2026.
//
#include <iostream>
using namespace std;
// clion didn't compiling when the file name was 1.3
int main() {
    int x;
    cin>>x;
    for (int i = 1; i<x/2; i++) {
        cout<<i<<" "<<x-i<<'\n';
    }
    return 0;
}