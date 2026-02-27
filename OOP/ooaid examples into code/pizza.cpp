//
// Created by cactus on 2/27/2026.
//
#include <iostream>
using namespace std;

class Pizza {
private:
    char size;
    int price;

public:
    Pizza() {
        size = '?';
        price = -1;
        cout << "Default constructor called" << '\n'; // Seeing what order things work in
    }

    Pizza(char size, int price) {
        this->size = size;
        this->price = price;
        cout << "Constructor called" << '\n';
    }

    ~Pizza() {
        cout << "Destructor called" << '\n';
    }

    void printPizza() const {
        cout << "Pizza size: " << size << ", pizza price: " << price << '\n';
        preparePizza();
        roastPizza();
        cutPizza();
        packagePizza();
    }

    void preparePizza() const {
        cout << "Preparing pizza..." << '\n';
    }

    void roastPizza() const {
        cout << "Roasting pizza..." << '\n';
    }

    void cutPizza() const {
        cout << "Cutting pizza..." << '\n';
    }

    void packagePizza() const {
        cout << "Packaging pizza..." << '\n';
    }

    char getSize() const {
        return size;
    }

    int getPrice() const {
        return price;
    }

    void setSize(char size) {
        this->size = size;
    }

    void setPrice(int price) {
        this->price = price;
    }
};

int main() {
    char s;
    int x;
    cin >> s;
    cin >> x;
    Pizza p1;
    p1.setSize(s);
    p1.setPrice(x);
    p1.printPizza();
    Pizza p2('L', 500);
    p2.printPizza();
    return 0;
}
