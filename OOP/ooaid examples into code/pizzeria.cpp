//
// Created by cactus on 2/27/2026.
//
#include <iostream>
#include <string>
using namespace std;

class Pizza {
private:
    char size;
    int price;

public:
    Pizza() {
        size = '?';
        price = -1;
        cout << "Pizza Default constructor called" << '\n';
    }

    Pizza(char size, int price) {
        this->size = size;
        this->price = price;
        cout << "Pizza Constructor called" << '\n';
    }

    ~Pizza() {
        cout << "Pizza Destructor called" << '\n';
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

class Pizzeria {
private:
    string name;
    Pizza currentPizza;
    bool deliveredPizza = true;

public:
    Pizzeria(string name) {
        this->name = name;
        deliveredPizza = true;
        cout << "Pizzeria constructor called" << '\n';
    }

    ~Pizzeria() {
        cout << "Pizzeria destructor called" << '\n';
    }

    void deliverPizza() {
        if (!deliveredPizza) {
            cout << "Delivering pizza..." << '\n';
            deliveredPizza = true;
        }
    }

    void makePizza() {
        if (deliveredPizza) {
            deliveredPizza = false;
            char pizzaSize;
            int pizzaPrice;
            cin >> pizzaSize;
            cin >> pizzaPrice;
            currentPizza.setSize(pizzaSize);
            currentPizza.setPrice(pizzaPrice);
            currentPizza.printPizza();
            cout << "Making pizza..." << '\n';
            deliverPizza();
        }
    }

    void setName(string &name) {
        this->name = name;
    }
};

int main() {
    Pizzeria pizzeria("Poco's");
    pizzeria.makePizza();
    return 0;
}
