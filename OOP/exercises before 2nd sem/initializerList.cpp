//
// Created by cactus on 1/20/2026.
//
#include <iostream>
using namespace std;
class Subjects {
public:
    string subject;
    string difficulty;
    Subjects(string subject, string difficulty) : subject(subject), difficulty(difficulty) {
        string str = "hard";
        bool difficult = true;
        for (int i = 0; i<str.length(); i++) {
            if (str[i]!=tolower(difficulty[i])) {
                difficult = false;
            }
        }
        if (difficult) {
            this->difficulty+=" GL :D";
        }
    }
};

int main() {
    string subject;
    string difficulty;
    cin>>subject>>difficulty;
    Subjects s1(subject,difficulty);
    cout<<"Subject: "<<s1.subject<<" ||| Difficulty: "<<s1.difficulty<<'\n';
    Subjects s2("VVKN", "easy");
    cout<<"Subject: "<<s2.subject<<" ||| Difficulty: "<<s2.difficulty<<'\n';
}