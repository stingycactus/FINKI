/* Read n lines of text
Text — remove top keyboard row letters, replace whitespace with '.'
Remove: q w e r t y u i o p (both upper & lower case)
Replace any whitespace with .
use function to do the transformation*/
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

void transform(char *str) {
    int n = strlen(str);
    char topRow[11] = "qwertyuiop";
    int k = 0;
    for (int i = 0; i < n; i++) {
        bool flag = true;
        if (str[i] == ' ') {
            str[k] = '.';
            k++;
        }
        else {
            for (int j = 0; j < 11; j++) {
                if (tolower(str[i]) == tolower(topRow[j])) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                str[k] = str[i];
                k++;
            }
        }
    }
    str[k]='\0';
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        char text[100];
        cin.getline(text, 100);
        transform(text);
        cout << text << '\n';
    }
    return 0;
}
