//
// Created by cactus on 16/12/2025.
//
#include <iostream>
using namespace std;
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

int mask(int number, int k) {
    // Base case: if number is 0, return 0
    if (number == 0) {
        return 0;
    }

    // Get the last digit
    int ld = number % 10;

    // Recursively process the rest of the number
    int rest = mask(number / 10, k);

    // Determine the masked digit (0 or 1)
    int maskedDigit = (ld > k) ? 1 : 0;

    // Build the result: shift the rest left and add the masked digit
    return rest * 10 + maskedDigit;
}

int main() {
    int number = 771256;
    int k = 3;
    cout<<mask(number, k);
    return 0;
}
