//
// Created by cactus on 07/01/2026.
//
#include <iostream>
#include <cctype>
using namespace std;
void transformString(char *str, int shift) {
    if (*str == '\0') {
        return;
    }
    if (islower(*str) && *str != ' ') {
        *str = 'a'+((*str-'a'+shift)%26);
    }
    else if (isupper(*str) && *str != ' ') {
        *str = 'A'+((*str-'A'+shift)%26);
    }
    transformString(str+1,shift);
}
int main() {
    int n;
    cin>>n;
    int x;
    cin>>x;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        char string[100];
        cin.getline(string,100);
        transformString(string,x);
        cout<<string<<endl;
    }
    return 0;
}