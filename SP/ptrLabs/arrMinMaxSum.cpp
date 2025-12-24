//
// Created by cactus on 23/12/2025.
//
#include <iostream>
using namespace std;
void transformArr (int arr[], int size) {
    int min = *arr;
    int max = *arr;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum+=arr[i];
        if (arr[i]>max) max = arr[i];
        if (arr[i]<min) min = arr[i];
    }
    int diff = max - min;
    cout<<max<<endl;
    cout<<min<<endl;
    cout<<sum<<endl;
    for (int i = 0; i < size; i++) {
        arr[i]+=diff;
        cout<<arr[i]<<" ";
    }
}
int main() {
    int n;
    cin>>n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin>> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout<<endl;
    transformArr(arr, n);
    return 0;
}