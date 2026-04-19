//
// Created by cactus on 02/04/2026.
//
/*Napravi klasa User:
vo klasata se cuva
char username[10];
char password[30];
int loginAttempts;

potrebni se konstruktori

Passewordot e validen ako se sostoi od najmalku 12 karakteri

treba da se napravi metod bool za proverka dali e strong passwordot
eden password e strong ako povekje od polovina od passwordot e sostaven od specijalni znaci.

mainot e daden i treba samo da se dopolni;
vnesuvanje na niza objekti od klasata  User.

ova e vlezna od prva grupa.*/
#include <cstring>
#include <iostream>
using namespace std;

class User {
private:
    char username[10];
    char password[30];
    int loginAttempts;
public:
    User(const char* username="", const char *password="") {
        strcpy(this->username, username);
        strcpy(this->password, password);
        this->loginAttempts = 0;
    }
    bool validPassword(const char* password) {
        if (strlen(password)>=12) {
            return true;
        }
        return false;
    }
    bool strongPassword(const char *password) {
        int halfOfPass = strlen(password)/2;
        int specialCount = 0;
        for (int i = 0; i<strlen(password); i++) {
            if (!(isdigit(password[i]) || isalpha(password[i]))) {
                specialCount++;
            }
        }
        if (specialCount>halfOfPass) {
            return true;
        }
        return false;
    }
};
int main() {
    int n;
    cin>>n;
    User users[100];
    for (int i = 0; i<n; i++) {
        char username[10];
        char password[30];
        cin>>username>>password;
        users[i]=User(username,password);
    }
    return 0;
}