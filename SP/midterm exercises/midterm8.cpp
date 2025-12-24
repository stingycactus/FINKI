//
// Created by cactus on 04/11/2025.
//
//for example: 291 -> (9 == (1 + 2) * 3) 84575 -> (754 == (5 + 8) * 58)
#include <iostream>
using namespace std;
int main() {
    int a,b;
    cin>>a>>b;
    int counter = 0;
    for (int i=a; i<=b; i++) {
        int num = i;
        int lastdigit=num%10;
        int rest = num/10;
        int temp = rest;
        int power = 1;
        while (temp>0) {
            power*=10;
            temp/=10;
        }
        int firstdigit = num/power;
        int sum = firstdigit + lastdigit;
        int firstandlast = firstdigit * 10 + lastdigit;
        int temp2 = rest;
        int reversedmiddledigits = 0;
        while (temp2 >= 10) {
            int digit = temp2%10;
            reversedmiddledigits = reversedmiddledigits * 10 + digit;
            temp2/=10;
        }
        int quotient = reversedmiddledigits/sum;
        if (reversedmiddledigits%sum==0 && quotient !=0) {
            cout<<num<<" -> "<<"("<<reversedmiddledigits<<" == "<<"("<<lastdigit<<" + "<<firstdigit<<")"<< " * "<<quotient<<")"<<endl;
            counter++;
        }
    }
    cout<<counter;
    return 0;
}