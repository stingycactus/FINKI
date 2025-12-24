//
// Created by cactus on 13/11/2025.
//
#include <iostream>
using namespace std;
int main() {
    int x;
    while (cin >> x) {
        if (x < 10) {
            continue;
        }
        int counter = -1; // -1 cuz we want to reassign it later anyways
        int temp = x;
        bool pattern = true;
        while (temp>9) {
            int e = temp%10; // a>b, b<c, c>d, d<e или a<b, b>c, c<d, d>e
            int d = temp/10%10; // e<d = 1, e>d = 0;
            if (counter==-1) {
                counter=e<d; // e<d == 1, e>d == 0
            }
            if (counter%2==0 && e<=d || counter%2==1 && e>=d){
                pattern=false;
            }
            counter++;
            temp/=10;
        }
        if (pattern) {
            cout<<x<<'\n';
        }
    }
    return 0;
}
