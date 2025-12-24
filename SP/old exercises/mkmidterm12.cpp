//
// Created by cactus on 13/11/2025.
//
#include <iostream>
using namespace std;
int main () {
    int x;
    // a<5, b>=5, c<5, d>=5 или a>=5, b<5, c>=5, d<5
    while (cin>>x) {
        if (x<=10) {
            continue;
        }
        int temp = x;
        bool pattern1 = true;
        bool pattern2 = true;
        bool greater1 = true; // d>=5
        bool greater2 = false; // d<5
        while (temp>0) {
            int d = temp%10;
            if (greater1 && (d < 5) || !greater1 && (d>=5)) {
                pattern1 = false;
            }
            if (greater2 && (d < 5) || !greater2 && (d>=5)) {
                pattern2 = false;
            }
            greater1 = !greater1;
            greater2 = !greater2;
            temp/=10;
        }
        if (pattern1||pattern2) {
            cout<<x<<'\n';
        }
    }
    return 0;
}