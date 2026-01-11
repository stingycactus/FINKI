//
// Created by cactus on 11/01/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
int main() {
    float n;
    cin>>n;
    cin.get();
    char str[10];
    char maxStr[10];
    int type = 0;
    float maxCoefficient=0.0;
    while (cin>>str) {
        if (*str=='#') {
            break;
        }
        int x;
        float y;
        cin>>x>>y;
        n*=y;
        if (y>maxCoefficient) {
            maxCoefficient = y;
            type=x;
            strcpy(maxStr, str);
        }
    }
    cout<<maxStr<<' '<<type<<' '<<maxCoefficient<<'\n';
    cout<<n<<'\n';
    return 0;
}