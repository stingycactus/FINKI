//
// Created by cactus on 11/01/2026.
//
#include <iostream>
using namespace std;
void printAsc (int n) {
    if (!n) {
        return;
    }
    printAsc(n-1);
    cout<<n;
}
void printDesc (int n) {
    if (!n) {
        return;
    }
    cout<<n;
    printDesc(n-1);
}
void printTimes (int n) {
    if (!n) {
        return;
    }
    printAsc(n);
    printDesc(n-1);
    cout<<'\n';
    printTimes(n-1);

}

int main() {
    int n;
    cin>>n;
    printTimes(n);
    return 0;
}