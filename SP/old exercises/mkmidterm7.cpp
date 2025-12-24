//
// Created by cactus on 12/11/2025.
//
#include <iostream>
using namespace std;

int main() {
    int z;
    cin >> z;
    int a, b;
    int pairCounter = 0;
    int counter = 0;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) {
            break;
        } else {
            if ((a + b) == z) {
                pairCounter++;
            }
            counter++;
        }
    }
    cout<<"Vnesovte "<<pairCounter<<" parovi od broevi chij zbir e "<<z<<'\n';
    cout<<"Procentot na parovi so zbir "<<z<<" e "<<(float(pairCounter)/counter)*100<<"%";
    return 0;
}
