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
        cout << "Pizza default constructor called" << '\n'; // Seeing what order things work in
    }

    Pizza(char size, int price) {
        this->size = size;
        this->price = price;
        cout << "Pizza constructor called" << '\n';
    }
    ~Pizza() {
        cout << "Pizza destructor called" << '\n';
    }
    void printPizza() {
        cout << "Pizza size: " << size << ", pizza price: " << price << '\n';
    }

    char getSize() {
        return size;
    }

    int getPrice() {
        return price;
    }
};

class cheesePizza : public Pizza {
private:
    string ingredients;

public:
    cheesePizza(char size, int price, string ingredients) : Pizza(size, price) {
        cout<<"CheesePizza constructor called" << '\n';
        this->ingredients = ingredients;
    }
    ~cheesePizza() {
        cout << "CheesePizza destructor called" << '\n';
    }
    void printPizza() {
        cout << "Cheese pizza size: " << getSize() << ", cheese pizza price: " << getPrice() << '\n';
        cout << "Pizza ingredients: " << ingredients << '\n';
    }
};

int main() {
    Pizza normalPizza('L', 500);
    normalPizza.printPizza();
    cheesePizza cheesePizza('L', 500, "mozzarella, cheddar ");
    cheesePizza.printPizza();
    return 0;
}
