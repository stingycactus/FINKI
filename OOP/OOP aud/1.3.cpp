//
// Created by cactus on 09/03/2026.
//
#include <iostream>
#include <string>
using namespace std;
struct Students {
    string firstName;
    string lastName;
    int indexNumber;
    int points;
    void read() {
        cin>>firstName>>lastName>>indexNumber>>points;
    }
    void capitalizeFirst() {
        firstName[0]=toupper(firstName[0]);
        lastName[0]=toupper(lastName[0]);
    }
    void printStudent() {
        capitalizeFirst();
        cout<<firstName<<" "<<lastName<<" "<<indexNumber<<" "<<points<<'\n';
    }
};
void sortStudents(Students s[], int n) {
    for (int i = 0; i<n-1; i++) {
        for (int j = 0; j<n-1-i; j++) {
            if (s[j].points < s[j+1].points) {
                swap(s[j],s[j+1]);
            }
        }
    }
}

int main() {
    Students s[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        s[i].read();
    }
    sortStudents(s,n);
    for (int i = 0; i<n; i++) {
        s[i].printStudent();
    }
}