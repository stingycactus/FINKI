//
// Created by cactus on 1/20/2026.
//
#include <iostream>
using namespace std;
class Subjects {
public:
    string subject;
    string difficulty;
    Subjects() : subject("Unknown "), difficulty ("Unknown ") {}
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
    Subjects subjects[100];
    int subjectCount;
    cin >> subjectCount;
    cin.ignore();
    for (int i = 0; i < subjectCount; i++) {
        getline(cin, subjects[i].subject);
        getline(cin, subjects[i].difficulty);
    }
    for (int i = 0; i < subjectCount; i++) {
        cout<<subjects[i].subject<<" "<<subjects[i].difficulty<<'\n';
    }
    return 0;
}