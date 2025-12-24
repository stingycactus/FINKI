//
// Created by cactus on 04/11/2025.
//
#include <iostream>
using namespace std;
int main () {
    int a,b,c;
    cin>>a>>b>>c;
    if ((a+b+c)==180) {
        cout<<"YES"<<endl;
        if (a>90 || b>90 || c>90) {
            cout<<"OBTUSE";
        }
        else if (a<90 && b<90 && c<90) {
            cout<<"ACUTE";
        }
        else {
            cout<<"RIGHT";
        }
    }
    else {
        cout<<"NO";
    }
    return 0;
}