//
// Created by cactus on 19/05/2026.
//
#include <iostream>
using namespace std;

class NegativeValueException {
private:
    string text;
public:
    NegativeValueException(string text) : text(text) {}
    void print () {
        cout<<text<<'\n';
    }
};

class Discount {
protected:
    static float euros;
    static float dollars;
public:
    virtual float discount_price() const = 0;

    virtual float price() const = 0;

    virtual void print_rule() const = 0;
};
float Discount::euros=0;
float Discount::dollars=0;

class Product{
protected:
    string name;
    float price;
public:
    Product(const string &name="", float price=0) : name(name), price(price) {}
    float getPrice() const {
        return price;
    }
    void print() const {
        cout << "Product{ name=" << name << ", price=" << price << "}" << '\n';
    }
    void changePrice(float newPrice) {
        if (newPrice < 0) {
            throw NegativeValueException("You entered a negative value!");
        }
        this->price=newPrice;
    }
};

class FoodProduct : public Product, public Discount {
private:
    float calories;
public:
    FoodProduct(const string &name="", float price=0, float calories=0) : Product(name, price), calories(calories) {}
    float discount_price() const {
        return Product::price;
    }
    float price() const {
        return Product::price;
    }
    void print_rule() const {
        cout << "Product{ name=" << name << ", price=" << price() << ", calories="<<calories<<"}" << '\n';
    }
};
class Drinks : public Product, public Discount {
private:
    string brand;
    bool alcoholic;
public:
    Drinks(const string &name="", float price=0, const string &brand="", bool alcoholic=false) : Product(name, price), brand(brand), alcoholic(alcoholic){}
    float discount_price() const {
        if (alcoholic && price()>20*euros) {
            return price() * 0.95;
        }
        if (!alcoholic && brand=="Coca-Cola") {
            return price() * 0.9;
        }
        return price();
    }
    float price() const {
        return Product::price;
    }
    void print_rule() const {
        cout << "Product{ name=" << name << ", price=" << price() << ", brand="<<brand<<"}" << '\n';
    }
};

class Cosmetics : public Product, public Discount {
private:
    int weight;
public:
    Cosmetics(const string &name="", float price=0, int weight=0) : Product(name, price), weight(weight){}
    float discount_price() const {
        if (price()>5*euros) {
            return price() * 0.88;
        }
        if (price()>20*dollars) {
            return price() * 0.86;
        }
        return price();
    }
    float price() const {
        return Product::price;
    }
    void print_rule() const {
        cout << "Product{ name=" << name << ", price=" << price() << ", weight="<<weight<<"}" << '\n';
    }
};

float total_discount(Discount* d[], int n) {
    float totalDiscount=0;
    float totalPrice=0;
    for (int i = 0; i<n; i++) {
        totalDiscount+=d[i]->discount_price();
        totalPrice+=d[i]->price();
    }
    return totalPrice-totalDiscount;
}

int main() {
    int n = 0;
    float newPrice;
    Discount **d = new Discount*[10];
    d[n++] = new FoodProduct("leb", 30);
    d[n++] = new Drinks("viski", 1350, "Jack Daniel's", true);
    d[n++] = new FoodProduct("sirenje", 390, 105);
    d[n++] = new Drinks("votka", 850, "Finlandia", true);
    d[n++] = new Cosmetics("krema", 720, 100);
    d[n++] = new Drinks("sok", 50, "Coca-Cola", false);
    d[n++] = new Cosmetics("parfem", 3500, 50);

    cout << "Total price of all products is: " << total_discount(d, n) << endl;

    cout << "Changing the price of the cosmetic products" << endl;
    for (int i = 0; i < n; ++i) {
        Cosmetics* c = dynamic_cast<Cosmetics *>(d[i]);
        if (c != 0) {
            c->print();
            cin >> newPrice;
            try {
                c->changePrice(newPrice);
            }
            catch (NegativeValueException i) {
                i.print();
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete d[i];
    }
    delete[] d;

    return 0;
}