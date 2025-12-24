//
// Created by cactus on 16/12/2025.
//
#include <iostream>
using namespace std;
/*
LAB 3
Да се имплементира рекурзивна функција void printAlphabet (char c, bool backwards)
која ке спроведува печатење на латиничната азбука почнувајќи од буквата c.
Доколку backwards е true во таа ситуација печатењето оди кон почетокот,
а доколку е false, печатењето оди кон крајот.

*/
void printAlphabet (char c, bool backwards) {
    if (c=='Z'+1&&!backwards||c=='A'-1&&backwards) {
        return;
    }
    else {
        if (!backwards) {
            cout<<c;
            printAlphabet(c+1,backwards);
        }
        else {
            cout<<c;
            printAlphabet(c-1,backwards);
        }
    }
}
int main() {
    printAlphabet('D',false);
    return 0;
}