/*1. n numbers — print those with all even digits (starting from last to first), find firstpos & lastpos
(even-digit check must be recursive)*/
#include <iostream>
#include <cmath>
using namespace std;
bool recursiveEvenCheck (int number) {
    int digit = number%10;
    if (number<10) {
        return !(digit%2);
    }
    return !(digit%2) * recursiveEvenCheck(number/10);
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i<n; i++) {
        cin>>arr[i];
    }
    int lastPos = -1;
    int firstPos = -1;
    for (int i = n-1; i>=0; i--) {
        if (recursiveEvenCheck(abs(arr[i]))) {
            cout<<arr[i]<<' ';
            if (lastPos == -1) {
                lastPos=i+1;
                firstPos=i+1;
            }
            else {
                firstPos=i+1;
            }
        }
    }
    if (firstPos != -1 || lastPos != -1) {
        cout<<'\n';
        cout<<firstPos<<','<<lastPos;
    }
    return 0;
}