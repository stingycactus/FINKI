//
// Created by cactus on 01/04/2026.
//
#include <iostream>
#include <string>
using namespace std;
class Book {
private:
    string title;
    int pagesRead;
public:
    Book(const string title="TEST BOOK", int pagesRead=0) {
        this->title=title;
        this->pagesRead=pagesRead;
    }
    void readPages(int pages) {
        if ((pagesRead+pages)>200) {
            pagesRead=200;
        }
        else {
            pagesRead+=pages;
        }
    }
    string status() {
        if (pagesRead<100) {
            return "IN PROGRESS";
        }
        if (pagesRead<200) {
            return "ALMOST DONE";
        }
        else {
            return "FINISHED";
        }
    }
    void print() {
        // TITLE - READ_PAGES/200 - STATUS
        cout<<title<<" - "<<pagesRead<<"/200"<<" - "<<status()<<'\n';
    }
};
int main() {
    int n;
    cin>>n;
    Book books[100];
    for (int i = 0; i<n; i++) {
        string title;
        int pagesRead;
        cin>>title;
        cin>>pagesRead;
        books[i]=Book(title,pagesRead);
    }
    for (int i = 0; i<n; i++) {
        books[i].print();
    }
    return 0;
}