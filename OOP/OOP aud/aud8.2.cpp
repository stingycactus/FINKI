//
// Created by cactus on 11/05/2026.
//
// was having weird issue naming this file 8.1, for some reason clion would complain
// about file not being found and can't compile even though cmakelists was correct, lol.
#include <iostream>
using namespace std;

class Discount {
public:
    virtual float getDiscount() const = 0;

    virtual float getPrice() const = 0;
};

class Product {
private:
    string name;
    float price;

public:
    Product(const string &name = "", float price = 0) : name(name), price(price) {}
    float getPrice() const {
        return price;
    }
};

class FoodProduct : public Product, public Discount {
    float calories;

public:
    FoodProduct(const string &name = "", float price = 0, float calories=0) : Product(name, price), calories(calories) {}
    float getDiscount() const {
        return 0.8 * getPrice();
    }

    float getPrice() const {
        return Product::getPrice();
    }
};

class DigitalProduct : public Product, public Discount {
private:
    float size;
public:
    DigitalProduct(const string &name="", float price = 0, float size = 0) : Product(name, price), size(size) {}
    float getDiscount() const {
        return 0.9 * Product::getPrice();
    }
    float getPrice() const {
        return Product::getPrice();
    }
};

float totalDiscount(Discount* discounts[], int n) {
    float totalPrice = 0;
    float totalDiscount = 0;
    for (int i = 0; i < n; ++i) {
        totalPrice += discounts[i]->getPrice();
        totalDiscount += discounts[i]->getDiscount();
    }
    return totalPrice - totalDiscount;
}

int main() {
    Discount **d = new Discount *[3];
    d[0] = new FoodProduct("Cheese", 450, 1200);
    d[1] = new FoodProduct("Wine", 780, 250);
    d[2] = new DigitalProduct("WOW", 380, 400);
    cout << "Difference: " << totalDiscount(d, 3) << endl;
    for (int i = 0; i < 3; ++i) {
        delete d[i];
    }
    delete[] d;
    return 0;
}
