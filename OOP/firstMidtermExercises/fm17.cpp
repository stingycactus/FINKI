//
// Created by cactus on 01/04/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
class IndexOutOfBounds {
    int index;
public:
    IndexOutOfBounds(int index) {
        this->index = index;
    }
    int getIndex() const {
        return index;
    }
};
class String {
private:
    char *string;
    int length;
public:
    String(const char *string="", int length=0) {
        this->length=strlen(string)+1;
        this->string=new char[this->length];
        strcpy(this->string,string);
    }
    ~String() {
        delete [] string;
    }
    String(const String &other) {
        this->length=other.length;
        this->string=new char[length];
        strcpy(this->string,other.string);
    }
    String &operator=(const String &other) {
        if (this==&other) {
            return *this;
        }
        delete [] string;
        this->length=other.length;
        this->string=new char[length];
        strcpy(this->string,other.string);
        return *this;
    }
    char &operator[](int index) {
        if (index < 0 || index>length-2) {
            throw IndexOutOfBounds(index);
        }
        return string[index];
    }
    friend ostream &operator<<(ostream &os, const String &s) {
        os<<s.string;
        return os;
    }
};

class StringBuilder {
private:
    String *strings; // read task wrong, this should just be char *string
    int size;
    int capacity;
public:
    StringBuilder(int capacity=0) {
        this->capacity=capacity;
        this->size=0;
        this->strings = new String[capacity];
    }
    ~StringBuilder() {
        delete [] strings;
    }
    StringBuilder(const StringBuilder &other) {
        this->capacity=other.capacity;
        this->size=other.size;
        this->strings = new String[capacity];
        for (int i = 0; i<size; i++) {
            this->strings[i]=other.strings[i];
        }
    }
    StringBuilder &operator=(const StringBuilder &other) {
        if (this==&other) {
            return *this;
        }
        delete [] strings;
        this->capacity=other.capacity;
        this->size=other.size;
        this->strings = new String[capacity];
        for (int i = 0; i<size; i++) {
            this->strings[i]=other.strings[i];
        }
        return *this;
    }
    StringBuilder &operator+=(const String &s) {
        if (size==capacity) {
            this->capacity=this->capacity*2+1;
            String *temp = new String[capacity];
            for (int i = 0; i<size; i++) {
                temp[i]=strings[i];
            }
            delete [] strings;
            strings = temp;
        }
        strings[size]=s;
        size++;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const StringBuilder &sb) {
        os<<"Capacity: "<<sb.capacity<<'\n';
        os<<"Size: "<<sb.size<<'\n';
        os<<"Contents: ";
        for (int i = 0; i<sb.size; i++) {
            os<<sb.strings[i];
        }
        return os;
    }
};

int main() {
    int n;
    cin >> n;
    StringBuilder sb(n);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char input[100];
        cin >> input;
        String s(input);
        int x;
        cin >> x;
        try {
            cout << "s[" << x << "] = " << s[x] << endl;
        }
        catch (IndexOutOfBounds &e) {
            cout << "Index '" << e.getIndex() << "' is out of bounds" << endl;
        }


        sb += s;
    }
    cout << sb;
    return 0;
}