#include <iostream>
using namespace std;
void printOnes(int number) {
    if (!number) {
        return;
    }
    cout<<number;
    printOnes(number-1);
}
void printFunc(int number) {
    if (!number) {
        return;
    }
    printFunc(number-1);
    printOnes(number-1);
    cout<<number;
    printOnes(number-1);
    cout<<'\n';
}


int main() {
    int n;
    cin>>n;
    printFunc(n);
    return 0;
}