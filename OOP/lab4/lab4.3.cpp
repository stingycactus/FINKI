//
// Created by cactus on 01/04/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

class Chocolate {
private:
    char name[100];
    int price;
public:
    Chocolate(const char *name="", int price=0) {
        strcpy(this->name,name);
        this->price=price;
    }
    friend ostream &operator<<(ostream &os, const Chocolate &choco) {
        os<<choco.name<<": "<<"$"<<choco.price;
        return os;
    }
    int getPrice() const {
        return price;
    }
};

class ChocolateFactory {
private:
    Chocolate *products;
    int *weeklyProduction;
    int numProducts;
public:
    ChocolateFactory(Chocolate *products=nullptr, int *weeklyProduction=nullptr, int numProducts=0) {
        this->numProducts=numProducts;
        this->products= new Chocolate[numProducts];
        this->weeklyProduction = new int[numProducts];
        for (int i = 0; i<numProducts; i++) {
            this->products[i]=products[i];
            this->weeklyProduction[i]=weeklyProduction[i];
        }
    }
    ~ChocolateFactory() {
        delete [] products;
        delete [] weeklyProduction;
    }
    ChocolateFactory(const ChocolateFactory &other) {
        this->numProducts=other.numProducts;
        this->products= new Chocolate[numProducts];
        this->weeklyProduction = new int[numProducts];
        for (int i = 0; i<numProducts; i++) {
            this->products[i]=other.products[i];
            this->weeklyProduction[i]=other.weeklyProduction[i];
        }
    }
    ChocolateFactory &operator=(const ChocolateFactory &other) {
        if (this==&other) {
            return *this;
        }
        delete [] products;
        delete [] weeklyProduction;
        this->numProducts=other.numProducts;
        this->products= new Chocolate[numProducts];
        this->weeklyProduction = new int[numProducts];
        for (int i = 0; i<numProducts; i++) {
            this->products[i]=other.products[i];
            this->weeklyProduction[i]=other.weeklyProduction[i];
        }
        return *this;
    }
    int weeklyIncome() const {
        int sum = 0;
        for (int i = 0; i<numProducts; i++) {
            sum+=weeklyProduction[i]*products[i].getPrice();
        }
        return sum;
    }
    bool operator<(const ChocolateFactory &other) {
        return weeklyIncome() < other.weeklyIncome();
    }
    bool operator>(const ChocolateFactory &other) {
        return weeklyIncome() > other.weeklyIncome();
    }
    ChocolateFactory &operator+(const ChocolateFactory &other) {
        int combinedProducts = numProducts+other.numProducts;
        int *temp = new int[combinedProducts];
        Chocolate *tempProducts = new Chocolate[combinedProducts];
        for (int i = 0; i<numProducts; i++) {
            temp[i]=this->weeklyProduction[i];
            tempProducts[i]=this->products[i];
        }
        delete [] weeklyProduction;
        delete [] products;
        for (int i = combinedProducts-numProducts; i<combinedProducts; i++) {
            temp[i]=other.weeklyProduction[i-numProducts];
            tempProducts[i]=other.products[i-numProducts];
        }
        numProducts=combinedProducts;
        weeklyProduction=temp;
        products=tempProducts;
        return *this;
    }
    friend ostream &operator<<(ostream &os, ChocolateFactory const &chocolateF) {
        for (int i = 0; i<chocolateF.numProducts; i++) {
            os<<chocolateF.products[i]<<" x "<<chocolateF.weeklyProduction[i]<<'\n';
        }
        os <<"$"<<chocolateF.weeklyIncome()<<"/wk"<<'\n';
        return os;
    }
};

int main() {
    int testCase;
    char name[100];
    int price;

    Chocolate products[100];
    int weeklyProduction[100];

    cin >> testCase;
    if (testCase == 0) {
        cout<<"Testing Chocolate print operator:"<<endl;
        for (int i = 0; i < 10; ++i) {
            cin>>name>>price;
            cout<<Chocolate(name,price)<<endl;
        }
    }
    else if (testCase == 1) {
        cout<<"Testing ChocolateFactory print operator:"<<endl;

        for (int i = 0; i < 10; ++i) {
            cin>>name>>price;
            products[i] = Chocolate(name, price);
            cin>>weeklyProduction[i];
        }

        ChocolateFactory cf(products,weeklyProduction,10);
        cout<<cf<<endl;
    }
    else if (testCase == 2) {
        cout<<"Testing ChocolateFactory comparison operators:"<<endl;

        for (int i = 0; i < 3; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products,weeklyProduction,3);

        for (int i = 0; i < 4; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products,weeklyProduction,4);

        cout<<cf1<<cf2;

        cout<<"< operator: "<< (cf1<cf2 ? "PASS" : "FAIL") <<endl;
        cout<<"> operator: "<< (cf2>cf1 ? "PASS" : "FAIL") <<endl;
    }
    else if (testCase == 3) {
        cout<<"Testing ChocolateFactory sum operator:"<<endl;

        for (int i = 0; i < 5; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf1 = ChocolateFactory(products,weeklyProduction,5);
        for (int i = 0; i < 5; ++i) {
            cin>>name>>price>>weeklyProduction[i];
            products[i] = Chocolate(name,price);
        }
        ChocolateFactory cf2 = ChocolateFactory(products,weeklyProduction,5);

        cout<<cf1+cf2;
    }
}