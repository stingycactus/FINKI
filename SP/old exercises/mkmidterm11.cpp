#include <iostream>
using namespace std;

int main() {
    int x;
    while (cin >> x) {
        if (x <= 10) {
            continue;
        }
        int temp = x;
        bool pattern = true; // a>b, b<c, c>d, d<e или a<b, b>c, c<d, d>e
        bool greater = true; // greater meaning d>e
        while (temp > 9) {
            int e = temp % 10;
            int d = temp / 10 % 10;
            if (temp==x) { // used to check condition below only for first iteration, temp == x instead of counter
                if (d < e) {
                    greater = false; // greater is meant to be d>e, so if d<e then greater changes to false
                }
            }
            if (greater && d <= e || !greater && d >= e) {
                pattern = false;
            }
            greater = !greater; // flips signs, if greater is true(d>e) -> > to <
            temp /= 10;
        }
        if (pattern) {
            cout << x << '\n';
        }
    }
    return 0;
}