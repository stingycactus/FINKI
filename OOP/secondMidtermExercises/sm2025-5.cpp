//
// Created by cactus on 5/28/2026.
//
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class NoProductFoundException {
private:
    string category;
public:
    NoProductFoundException(const string &category) : category(category) {}
    void print() {
        cout<<"No products from category "<<category<<" were found in the store"<<'\n';
    }
};

class Product {
private:
    string name;
    string category;
    int price;
    int quantity;
public:
    Product(const string &name="", const string &category="", int price=0, int quantity=0)
    : name(name), category(category), price(price), quantity(quantity){}
    int totalPrice() const {
        return price * quantity;
    }
    friend ostream &operator<<(ostream &os, const Product &p) {
        os<<p.name<<" ("<<p.category<<") "<<p.quantity<<" x "<<p.price<<" = "<<p.totalPrice()<<'\n';
        return os;
    }
    string getCategory() const {
        return category;
    }
};

class Store {
private:
    Product *products;
    int n;
public:
    Store(Product *products=nullptr, int n=0) {
        this->n=n;
        this->products=new Product[n];
        for (int i = 0; i<n; i++) {
            this->products[i]=products[i];
        }
    }
    ~Store() {
        delete [] this->products;
    }
    Store(const Store &other) {
        this->n=other.n;
        this->products=new Product[n];
        for (int i = 0; i<n; i++) {
            this->products[i]=other.products[i];
        }
    }
    Store &operator=(const Store &other) {
        if (this!=&other) {
            delete [] this->products;
            this->n=other.n;
            this->products=new Product[n];
            for (int i = 0; i<n; i++) {
                this->products[i]=other.products[i];
            }
        }
        return *this;
    }
    Store &operator+=(const Product &p) {
        Product *temp = new Product[n+1];
        for (int i = 0; i<n; i++) {
            temp[i]=products[i];
        }
        delete [] this->products;
        this->products=temp;
        this->products[n]=p;
        n++;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Store &s) {
        for (int i = 0; i < s.n; i++) {
            os<<s.products[i];
        }
        return os;
    }
    Store fromCategory(string &category) {
        Store result;
        for (int i = 0; i<n; i++) {
            if (products[i].getCategory()==category) {
                result+=products[i];
            }
        }
        if (!result.n) {
            throw NoProductFoundException(category);
        }
        return result;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`
    ifstream fin("input.txt");
    if (!fin) {
        return -1;
    }
    string name;
    string category2;
    int price;
    int quantity;
    while (getline(fin, name)) {
        getline(fin, category2);
        fin>>price;
        fin>>quantity;
        fin.ignore();
        Product p(name,category2,price,quantity);
        s+=p;
    }
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    ofstream fout("output1.txt");
    ofstream fout2("output2.txt");
    fout << s;
    try {
        Store filtered = s.fromCategory(category);
        fout2<<filtered;
    }catch (NoProductFoundException &e) {
        e.print();
    }
    fout.close();
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}