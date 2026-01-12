// 3. Matrix — difference max-min per column, print largest index with biggest difference, use function for difference
#include <iostream>
using namespace std;
int difference (int arr[100][100], int col, int row) {
    int maxNum = arr[0][col];
    int minNum = arr[0][col];
    for (int i = 0; i<row; i++) {
        if (arr[i][col]>maxNum) {
            maxNum = arr[i][col];
        }
        if (arr[i][col]<minNum) {
            minNum = arr[i][col];
        }
    }
    return maxNum-minNum;
}
int main() {
    int n,m;
    cin>>n>>m;
    int arr[100][100];
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<m; j++) {
            cin>>arr[i][j];
        }
    }
    int largestDiff = -1;
    int largestIndex = -1;
    for (int j = 0; j<m; j++) {
        int diff = difference(arr, j, n);
        cout<<diff<<'\n';
        if (diff>largestDiff) {
            largestDiff = diff;
            largestIndex = j;
        }
    }
    cout<<largestIndex;
    return 0;
}