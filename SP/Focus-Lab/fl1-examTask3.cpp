//
// Created by cactus on 6/8/2026.
//
#include <iostream>
#include <cstring>
using namespace std;

void maxSandwichOcc(char c[], char triple[], int *numOccurrences) {
    int tripleStart=-1;
    for (int i = 0; i<strlen(c)-2; i++) {
        if (c[i]==c[i+2]) {
            int counter=1;
            for (int j = i+1; j<strlen(c)-2; j++) {
                if (c[j]==c[i] && c[j+1]==c[i+1] && c[j+2]==c[i+2]) {
                    counter++;
                }
            }
            if (counter>*numOccurrences) {
                *numOccurrences=counter;
                triple[0]=c[i];
                triple[1]=c[i+1];
                triple[2]=c[i+2];
            }
        }
    }
    cout<<triple[0]<<triple[1]<<triple[2]<<" "<<*numOccurrences<<'\n';
}

int main() {
    char text[100];
    int n;
    cin>>n;
    char triple[4];
    int numOccurrences;
    for (int i = 0; i<n; i++) {
        cin>>text[i];
    }
    maxSandwichOcc(text, triple, &numOccurrences);
}