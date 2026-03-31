//
// Created by cactus on 31/03/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

class Pair {
private:
    char *key;
    int value;

public:
    Pair(const char *key = "", int value = 0) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    }

    Pair(const Pair &other) {
        this->key = new char[strlen(other.key) + 1];
        strcpy(this->key, other.key);
        this->value = other.value;
    }

    ~Pair() {
        delete [] key;
    }

    Pair &operator=(const Pair &other) {
        delete [] key;
        this->key = new char[strlen(other.key) + 1];
        strcpy(this->key, other.key);
        this->value = other.value;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Pair &pair) {
        os << "('" << pair.key << "', " << pair.value << ")" <<'\n';
        return os;
    }

    Pair &operator++() {
        value++;
        return *this;
    }

    Pair operator++(int) {
        Pair temp = *this;
        value++;
        return temp;
    }

    friend Pair operator+(const Pair &pair1, const Pair &pair2) {
        Pair pairToReturn = pair1;
        if (strlen(pair1.key) < strlen(pair2.key)) {
            pairToReturn = pair2;
        }
        pairToReturn.value = pair1.value + pair2.value;
        return pairToReturn;
    }
    int getValue() {
        return value;
    }
    char *getKey() {
        return key;
    }
};

class Collection {
private:
    Pair *pairs;
    int size;
    int capacity;

public:
    Collection(int capacity = 10) {
        this->capacity = capacity;
        this->size = 0;
        this->pairs = new Pair[capacity];
    }

    ~Collection() {
        delete [] pairs;
    }

    Collection(const Collection &other) {
        this->capacity = other.capacity;
        this->size = other.size;
        this->pairs = new Pair[capacity];
        for (int i = 0; i < size; i++) {
            this->pairs[i] = other.pairs[i];
        }
    }

    Collection &operator=(const Collection &other) {
        this->capacity = other.capacity;
        this->size = other.size;
        this->pairs = new Pair[capacity];
        for (int i = 0; i < size; i++) {
            this->pairs[i] = other.pairs[i];
        }
        return *this;
    }

    Collection &operator+=(const Pair &pair) {
        if (size==capacity) {
            capacity*=2;
            Pair *temp = new Pair[capacity];
            for (int i = 0; i<size; i++) {
                temp[i]=pairs[i];
            }
            delete [] pairs;
            pairs=temp;
        }
        pairs[size]=pair;
        size++;
        return *this;
    }
    friend ostream &operator<<(ostream &os,const Collection &collection) {
        os << "Size: "<<collection.size<<'\n';
        for (int i = 0; i<collection.size; i++) {
            os << collection.pairs[i];
        }
        return os;
    }
    bool operator==(const Collection &other) {
        if (this==&other) {
            return true;
        }
        if (size=other.size) {
            for (int i = 0; i<size; i++) {
                if (pairs[i].getKey()!=other.pairs[i].getKey() && (pairs[i].getValue()!=other.pairs[i].getValue())) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    Pair* find(const char* key) {
        for (int i = 0; i<size; i++) {
            if (strcmp(pairs[i].getKey(), key) == 0) {
                return &pairs[i];
            }
        }
        return NULL;
    }
};

void read(char *k, float *v) {
    scanf("%s", k); // cin >> k was given but CLion throws error, cin >> k works on courses compiler
    cin >> *v;
}

int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator ++(int) -----" << endl;
    cout << p1++;
    cout << p1;
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator == -----" << endl;
    if(k == k2) {
        cout << "k == k2" << endl;
    }
    k2 += p1;
    if(k == k2) {
        // not equal
        cout << "k == k2" << endl;
    }
    cout << "----- find -----" << endl;
    Pair* f = k.find(key);
    cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if(f == NULL) {
        cout << key << " not found" << endl;
    }
    return 0;
}
