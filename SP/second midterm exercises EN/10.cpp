//
// Created by cactus on 08/01/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin>>arr[i];
    }
    int maxAppearances = 0;
    for (int i = 0; i < n; i++) {
        int appearances = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i]==arr[j]) {
                appearances++;
            }
        }
        if (appearances>maxAppearances) {
            maxAppearances = appearances;
        }
    }
    int A = -1;
    int B = -1;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i]==arr[j]) {
                count++;
            }
        }
        if (count==maxAppearances) {
            if (A==-1) {
                A=arr[i];
            }
            else if (arr[i]!=A){
                B=arr[i];
            }
        }
    }
    if (A>B) {
        swap(A,B);
    }
    for (int i = 0; i<A; i++) {
        for (int j = 0; j<B; j++) {
            cout<<"*"<<' ';
        }
        cout<<'\n';
    }
    return 0;
}