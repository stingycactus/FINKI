//
// Created by cactus on 15/11/2025.
//
#include <algorithm>
#include <iostream>
using namespace std;
// n - how many numbers, k - check if s after transformation is divisible by k, s - number, r - digit
// if digitCount even -> 1234 -> 123412, -> first 2 digits get appended to number
// if digitCount odd -> 1234, 1+4 = 5, -> 235, first and last digit sum appended to middle digits (23)
// if digitCount 0 -> s stays same
// print DA if transformedNum is divisible by k, otherwise NE
int evenTransform(int number) {
    int temp = number;
    while (temp>99) {
        temp/=10;
    }
    return number*100+temp;
}
int oddTransform (int number) {
    int temp = number;
    int ld = temp%10;
    temp/=10;
    int multiplier = 1;
    int middleNumbers = 0;
    while (temp>9) {
        int digit = temp%10;
        middleNumbers += digit*multiplier;
        multiplier*=10;
        temp/=10;
    }
    int sumFirstLast = ld + temp;
    if (sumFirstLast < 10) {
        return middleNumbers*10+sumFirstLast;
    }
    else {
        return middleNumbers*100+sumFirstLast;
    }
}
int main() {
    int n,k;
    cin>>n>>k;
    for (int i = 0; i<n; i++) {
        int s,r;
        cin>>s>>r;
        int temp = s;
        int digitCount = 0;
        while (temp>0) {
            int digit = temp%10;
            if (digit==r) {
                digitCount++;
            }
            temp/=10;
        }
        int transformedNumber;
        if (digitCount%2==0 && digitCount!=0) {
            transformedNumber = evenTransform(s);
        }
        else if (digitCount%2==1) {
            transformedNumber = oddTransform(s);
        }
        else {
            transformedNumber = s;
        }
        if (transformedNumber%k==0) {
            cout<<"DA"<<'\n';
        }
        else {
            cout<<"NE"<<'\n';
        }
    }
    return 0;
}