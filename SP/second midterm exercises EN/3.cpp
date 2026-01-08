//
// Created by cactus on 07/01/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
int transformArr(int *arr, int start, int end, int &transformedNums) {
    if (start>end) {
        return 0;
    }
    int maxNum = max(arr[start],arr[end]);
    if (arr[start]!=arr[end]) {
        arr[start]=arr[end]=maxNum;
        transformedNums++;
    }
    return transformArr(arr,start+1,end-1,transformedNums);
}
int main() {
    int arr[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        cin>>arr[i];
    }
    int transformedNums = 0;
    int start = 0;
    int end = n-1;
    transformArr(arr,start, end, transformedNums);
    cout<<transformedNums<<'\n';
    for (int i = 0; i<n; i++) {
        cout<<arr[i]<<' ';
    }
    return 0;
}