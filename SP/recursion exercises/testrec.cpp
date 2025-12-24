//
// Created by cactus on 16/12/2025.
//
/*
LAB 2
Да се имплементира рекурзивна функција int mask (int number, int k)
која што во бројот number ќе ги замени сите цифри <= од k со 0, а сите цифри > к со 1.
Пример:
Влез
number = 771256, k = 3

Резултат:
110011 (цифрите 7,5,6 бидејќи се поголеми од k=3 се маскираат во 1, а цифрите 1 и 2 бидејќи се <= k се маскираат во 0)

*/
#include <iostream>
using namespace std;
int mask(int number, int k) {
    if (!number) {
        return 0;
    }
    int ld = number%10;
    int resultDigit = (ld>k);
    int rest = mask(number/10,k);
    return rest * 10 + resultDigit;
}
int main() {
    cout<<mask(771256,3);
    return 0;
}