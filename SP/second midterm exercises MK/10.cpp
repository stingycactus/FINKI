//
// Created by cactus on 11/01/2026.
//
#include <algorithm>
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;
void bubbleSort(char* arr, int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j<size-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

int main() {
    char line[100];
    char digits[100];
    while (cin.getline(line, 100)) {
        if (*line == '#') {
            break;
        }
        int digit = 0;
        int j = 0;
        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                digit++;
                digits[j] = line[i];
                j++;
            }
        }
        digits[j]='\0';
        cout << digit << ":";
        bubbleSort(digits, strlen(digits));
        for (int i = 0; i < strlen(digits); i++) {
            cout<< digits[i];
        }
        cout<<'\n';
    }
    return 0;
}
