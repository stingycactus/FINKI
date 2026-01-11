//
// Created by cactus on 11/01/2026.
//
#include <iostream>
#include <cstring>
using namespace std;
void transform(char *text, int shift) {
    if (*text=='\0') {
        return;
    }
    if (islower(*text) && *text != ' ') {
        *text = 'a' + ((*text-'a'+shift)%26);
    }
    else if (isupper(*text) && *text != ' ') {
        *text = 'A' + ((*text-'A'+shift)%26);
    }
    transform(text+1, shift);
}
int main () {
    int n;
    int x;
    cin>>n>>x;
    cin.get();
    for (int i = 0; i < n; i++) {
        char text[100];
        cin.getline(text,100);
        transform(text,x);
        cout<<text<<'\n';
    }
}