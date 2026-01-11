#include <cstdio>
#include <cstring>
#include <iostream>
#define MAX 100
using namespace std;

//ne menuvaj!
void wtf() {
    FILE *f = fopen("numbers.txt", "w");
    char c;
    while((c = getchar()) != EOF) {
        fputc(c, f);
    }
    fclose(f);
}

int main()
{
    wtf();
    FILE *f = fopen("numbers.txt", "r");
    char line[MAX];
    while (cin.getline(line, MAX)) {
        for (int i = 0; i<strlen(line); i++) {

        }
    }
    fclose(f);
    return 0;
}