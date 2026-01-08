//
// Created by cactus on 08/01/2026.
//
#include <iostream>
using namespace std;
bool criteria (int number, int og) {
    if (number<10) {
        return (og%10)%2==0 && number%2;
    }
    return criteria(number/10, og);
}

int main() {
    int n;
    cin>>n;
    int printedElems = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin>>x;
        if (criteria(x, x)) {
            cout<<x<<'\n';
            printedElems++;
        }
    }
    if (!printedElems) {
        cout<<"No such elements!";
    }
    return 0;
}