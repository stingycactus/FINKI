//
// Created by cactus on 25/12/2025.
//
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;
void filter(char str[], int n) {
    int j = 0;
    for (int i = 0; i<n; i++) {
        if (isalpha(str[i])) {
            if (islower(str[i])) {
                str[j] = toupper(str[i]);
            }
            else if (isupper(str[i])) {
                str[j] = tolower(str[i]);
            }
            j++;
        }
    }
    str[j] = '\0';
}
int main() {
    char str[100];
    cin.getline(str, 100);
    filter(str,strlen(str));
    cout<<str;
    return 0;
}