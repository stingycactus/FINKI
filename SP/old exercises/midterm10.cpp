//
// Created by cactus on 04/11/2025.
//
#include <iostream>
using namespace std;
int main () {
    int z;
    int a,b;
    cin>>z;
    int counter = 0, pair_counter=0;
    while (true) {
        int sum = 0;
        cin>>a>>b;
        if (a==0 && b==0) {
            break;
        }
        else {
            sum = a + b;
            if (sum==z) {
                pair_counter++;
            }
            counter++;
        }
    }
    cout<<"You entered "<<pair_counter<<" pairs of numbers that have a sum equal to "<<z<<'\n';
    cout<<"The percentage of pairs with sum "<<z<<" is "<<(pair_counter*100.0)/counter<<"%";
    return 0;
}