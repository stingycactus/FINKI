#include <iostream>
#include <cstring>
using namespace std;

class Word {
private:
    char* characters;
public:
    Word(const char* characters="UNDEFINED") {
        this->characters = new char[strlen(characters)+1];
        strcpy(this->characters,characters);
    }
    ~Word() {
        delete [] characters;
    }
    Word(const Word &other) {
        this->characters = new char[strlen(other.characters)+1];
        strcpy(this->characters,other.characters);
    }
    Word &operator=(const Word &other) {
        if (this==&other) {
            return *this;
        }
        delete [] characters;
        this->characters = new char[strlen(other.characters)+1];
        strcpy(this->characters,other.characters);
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Word &word) {
        os << word.characters;
        return os;
    }
};

class Sentence {
private:
    Word *words;
    int numberOfWords;
    int capacity;
public:
    Sentence(int capacity=10) {
        this->numberOfWords=0;
        this->capacity=10;
        this->words = new Word[capacity];
    }
    ~Sentence() {
        delete [] words;
    }
    Sentence (const Sentence &other) {
        this->numberOfWords=other.numberOfWords;
        this->capacity=other.capacity;
        this->words = new Word[capacity];
        for (int i = 0; i<numberOfWords; i++) {
            this->words[i]=other.words[i];
        }
    }
    Sentence &operator=(const Sentence &other) {
        delete [] words;
        this->numberOfWords=other.numberOfWords;
        this->capacity=other.capacity;
        this->words = new Word[capacity];
        for (int i = 0; i<numberOfWords; i++) {
            this->words[i]=other.words[i];
        }
        return *this;
    }
    void add (Word w) {
        if (numberOfWords==capacity) {
            this->capacity+=10;
            Word *temp = new Word[capacity];
            for (int i = 0; i<numberOfWords; i++) {
                temp[i]=words[i];
            }
            delete [] words;
            words = temp;
        }
        words[numberOfWords]=w;
        numberOfWords++;
    }
    void print() {
        for (int i = 0; i<numberOfWords;i++) {
            cout<<words[i]<<" ";
        }
        cout<<'\n';
    }
    void swap(int i, int j) {
        Word temp = words[i];
        words[i]=words[j];
        words[j]=temp;
    }
};

int main() {
    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SWAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();
    return 0;
}
