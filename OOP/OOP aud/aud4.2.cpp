//
// Created by cactus on 23/03/2026.
//
#include <iostream>
#include <string>
using namespace std;
class Library;
class libraryMember;
class Book {
private:
    string title;
    string author;
    bool availability;

public:
    Book(string title = "", string author = "", bool availability = false) {
        this->title = title;
        this->author = author;
        this->availability = availability;
    }

    Book(const Book &other) = default;

    ~Book() = default;

    friend class Library;
    friend void checkOutBook(libraryMember &member, Library &library, int index);
};

class Library {
private:
    string name;
    Book books[100];
    int numberOfBooks;

public:
    Library(string name = "City Library", Book books[] = nullptr, int numberOfBooks = 0) {
        this->name = name;
        this->numberOfBooks = numberOfBooks;
        for (int i = 0; i < numberOfBooks; i++) {
            this->books[i] = books[i];
        }
    }

    void addBook(Book const &book) {
        books[numberOfBooks] = book;
        numberOfBooks++;
    }

    void printLibraryInfo() {
        cout << name << '\n';
        cout << numberOfBooks << '\n';
        for (int i = 0; i < numberOfBooks; i++) {
            cout << (i+1) <<": "<< books[i].title << " "<<books[i].author << " "<<books[i].availability << '\n';
        }
    }
    friend void checkOutBook(libraryMember &member, Library &library, int index);
};
class libraryMember {
    private:
    string name;
    int index;
public:
    libraryMember(string name = "", int index = -1) {
        this->name = name;
        this->index = index;
    }
    friend void checkOutBook(libraryMember &member, Library &library, int index);
};
void checkOutBook(libraryMember &member, Library &library, int index) {
    if (library.books[index].availability) {
        cout<<"Book is available"<<'\n';
        library.books[index].availability = false;
    }
    else {
        cout<<"Book is not available"<<'\n';
    }
}

int main() {

    Library l1;
    int n;
    cout << "Enter the number of books" << endl;
    cin >> n;
    char name[30], author[30];
    bool availability;
    for (int i = 0; i < n; i++) {
        cin >> name >> author >> availability;
        Book b = Book(name, author, availability);
        l1.addBook(b);
    }
    l1.printLibraryInfo();
    libraryMember m1("Marko", 9541);
    int index;
    cin >> index;
    checkOutBook(m1, l1, index);


    return 0;
}