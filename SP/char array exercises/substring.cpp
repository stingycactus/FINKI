//
// Created by cactus on 25/12/2025.
//
#include <iostream>
#include <cstring>
using namespace std;

int findSubStrPos(char str[], char str2[]) {
    int subStrPos = -1;
    bool subStrPosFound = true;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == str2[0]) {
            for (int j = 1; j < strlen(str2); j++) {
                if (str[i+j] != str2[j]) {
                    subStrPosFound = false;
                    break;
                }
            }
            if (subStrPosFound) {
                subStrPos = i;
            }
        }
    }
    return subStrPos;
}
bool subStr(char str[], char str2[]) {
    for (int i = 0; i < strlen(str); i++) {
        if (!strncmp(str + i, str2, strlen(str2))) {
            return true;
        }
    }
    return false;
}
bool recursiveSubStr(char str[], char str2[]) {
    if (strlen(str) < strlen(str2)) {
        return false;
    }
    if (*str != *str2) {
        return recursiveSubStr(str+1, str2);
    }
    else {
        for (int i = 1; i<strlen(str2); i++) {
            if (str[i]!=str2[i]) {
                return false;
            }
        }
        return true;
    }
}
// bool recursiveSubStr(char str[], char str2[]) { // simpler, copied from claude
//     // Base case: empty substring is always found
//     if (*str2 == '\0') {
//         return true;
//     }
//
//     // Base case: reached end of str but str2 still has characters
//     if (*str == '\0') {
//         return false;
//     }
//
//     // If current characters match, try matching the rest
//     if (*str == *str2) {
//         // Try to match rest of str2 with rest of str
//         if (recursiveSubStr(str+1, str2+1)) {
//             return true;
//         }
//     }
//
//     // Either characters didn't match or the full match failed
//     // Try starting fresh from next position in str
//     return recursiveSubStr(str+1, str2);
// }

int main() {
    char str[100];
    cin.getline(str, 100);
    char str2[100];
    cin.getline(str2, 100);
    cout<<findSubStrPos(str, str2)<<'\n';
    cout<<subStr(str, str2)<<'\n';
    cout<<(strstr(str,str2)!=nullptr)<<'\n';
    cout<<recursiveSubStr(str, str2);
    return 0;
}
