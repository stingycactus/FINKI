//
// Created by cactus on 09/03/2026.
//
#include <iostream>
using namespace std;
class Email {
private:
    string to;
    string from;
    string message;
public:
    Email(string to="?", string from="?", string message="?") {
        this->to=to;
        this->from=from;
        this->message=message;
    }
    bool checkEmailValidity() {
        if (to.find('@') != string::npos && from.find('@') != string::npos) {
            return true;
        }
        return false;
    }
    void printEmailContents() {
        cout<<"To: "<<to<<'\n';
        cout<<"From: "<<from<<'\n';
        cout<<"Message: "<<message<<'\n';
    }
};
int main() {
    string to,from,message;
    cin>>to>>from;
    cin.ignore();
    getline(cin,message);
    Email email1(to,from,message);
    if (email1.checkEmailValidity()) {
        email1.printEmailContents();
    }
    else {
        cout<<"Invalid info";
    }
    return 0;
}