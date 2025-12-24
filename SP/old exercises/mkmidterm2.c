//
// Created by cactus on 12/11/2025.
//
#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int evenDigits = 1;
    for (int i = m; i <= n; i++) {
        int temp = i;

        while (temp > 0) {
            evenDigits = 1;
            int digit = temp%10;
            if (digit % 2 != 0) {
                evenDigits = 0;
                break;
            }
            temp/=10;
        }
        if (evenDigits) {
            printf("%d",i);
            break;
        }
    }
    if (!evenDigits) {
        printf("NE");
    }
    return 0;
}
