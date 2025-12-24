//
// Created by cactus on 18/12/2025.
//
#include <iostream>
using namespace std;
void doShit(int &a, int &b) {
    a+=b;
    b*=a;
}
int main() {
    int a,b;
    cin>>a>>b;
    doShit(a,b);
    cout<<a<<" "<<b;
    return 0;
}