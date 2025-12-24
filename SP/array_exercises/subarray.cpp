//
// Created by cactus on 03/12/2025.
//
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    //     int maxSum = arr[0];
    //     int maxElement=1;
    //     for (int i = 0; i < n; i++) {
    //         int current_sum = 0;
    //         int elements = 0;
    //         for (int j = i; j<n; j++) {
    //             current_sum += arr[j];
    //             elements++;
    //             if (current_sum > maxSum) {
    //                 maxSum = current_sum;
    //                 maxElement = elements;
    //             }
    //         }
    //     }
    //     cout<<maxSum<<" "<<maxElement<<endl;
    //     return 0;
    // }
    int maxSum = arr[0];
    int currentSum = arr[0];
    int maxLength = 1;
    int currentLength = 1;

    for (int i = 1; i < n; i++) {
        if (currentSum >= 0) {
            currentSum += arr[i];
            currentLength++;
        } else {
            currentSum = arr[i];
            currentLength = 1;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            maxLength = currentLength;
        }
    }

    cout << maxSum << " " << maxLength;
    return 0;
}
