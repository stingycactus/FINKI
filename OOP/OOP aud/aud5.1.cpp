//
// Created by cactus on 24/03/2026.
//
#include <iostream>
using namespace std;

class Array {
private:
    int *x;
    int capacity;
    int size;
public:
    Array(int capacity = 5) {
        this->x = new int[capacity];
        this->size = 0;
        this->capacity=capacity;
    }
    Array(const Array &s) {
        this->size = s.size;
        this->capacity=s.capacity;
        x = new int [s.capacity];
        for (int i = 0; i<size; i++) {
            x[i] = s.x[i];
        }
    }
    ~Array() {
        delete [] x;
    }
    Array &operator=(Array &a) {
        if (this == &a) {
            return *this;
        }
        size = a.size;
        capacity = a.capacity;
        delete [] x;
        x = new int[capacity];
        size = a.size;
        for (int i = 0; i<a.size; i++) {
            x[i]=a.x[i];
        }
        return *this;
    }
    Array &operator+=(int n) {
        if (size == capacity) {
            capacity*=2;
            int *temp = new int[capacity];
            for (int i = 0; i<size; i++) {
                temp[i]=x[i];
            }
            delete [] x;
            x = temp;
        }
        this->x[size]=n;
        size++;
        return *this;
    }
    // friend Array &operator+= (Array &a, int n) {
    //     if (a.size == a.capacity) {
    //         a.capacity*=2;
    //         int *temp = new int[a.capacity];
    //         for (int i = 0; i<a.size; i++) {
    //             temp[i]=a.x[i];
    //         }
    //         delete [] a.x;
    //         a.x = temp;
    //     }
    //     a.x[a.size]=n;
    //     a.size++;
    //     return a;
    // }
    Array &operator-=(int n) {
        int index = 0;
        for (int i = 0; i<size; i++) {
            if (x[i]!=n) {
                x[index]=x[i];
                index++;
            }
        }
        size = index;
        return *this;
    }
    // friend Array &operator-=(Array &a,int n) {
    //     int index = 0;
    //     for (int i = 0; i<a.size; i++) {
    //         if (a.x[i]!=n) {
    //             a.x[index]=a.x[i];
    //             index++;
    //         }
    //     }
    //     a.size = index;
    //     return a;
    // }
    friend ostream &operator<<(ostream &os, Array &a) {
        for (int i = 0; i<a.size; i++) {
            os<<a.x[i] << " ";
        }
        os << '\n';
        return os;
    }
    int &operator[](int index) {
        return x[index];
    }
    // friend bool operator==(Array &a, Array &b) {
    //     if (a.size != b.size) {
    //         return false;
    //     }
    //     for (int i = 0; i<a.size; i++) {
    //         if (a.x[i]!=b.x[i]) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }
    bool operator==(Array &a) {
        if (size!=a.size) {
            return false;
        }
        for (int i = 0; i<size; i++) {
            if (x[i]!=a.x[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Array a;
    a += (6);
    a += (4);
    a += (3);
    a += (2);
    a += (1);


    Array b(a);
    b -= (2);
    b -= (3);

    a[0] = 9; //primena na operatorot []

    cout << "a: " << a;
    cout << "b: " << b;

    if (a == b) cout << "Isti se";
    else cout << "Ne se isti";


    return 0;
}
