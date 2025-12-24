//
// Created by cactus on 23/12/2025.
//
#include <iostream>
using namespace std;

void sortFunc(int& a,int& b, int& c){
    if (a<b) {
        swap(a,b);
    }
    if (a<c) {
        swap(a,c);
    }
    if (b<c) {
        swap(b,c);
    }
}
int main() {
    int x,y,z;
    cin>>x>>y>>z;
    sortFunc(x,y,z);
    cout<<x<<" "<<y<<" "<<z<<endl;
    return 0;
}