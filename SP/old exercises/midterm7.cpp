//
// Created by cactus on 03/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int max_sum=0, max_div = 0;
    for (int i = n-1; i > 0; --i) {
        int sum = 0;
        for (int j = 1; j < i; j++) {
            if (i%j == 0) {
                sum += j;
            }
        }
        if (sum>max_sum) {
            max_sum = sum;
            max_div = i;
        }
    }
    cout<<max_div;
    return 0;
}
