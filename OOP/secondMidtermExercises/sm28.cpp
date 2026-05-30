#include <iostream>
#include <cstring>
using namespace std;

class AlcoholicDrink {
protected:
    string name;
    string country;
    float abv;
    float price;
    static int discount;
public:
    AlcoholicDrink(float abv=0, const string &name="", const string &country="", float price=0)
        : name(name), country(country), abv(abv), price(price) {}
    virtual float computePrice() const = 0;
    virtual ~AlcoholicDrink() {}
    friend ostream &operator<<(ostream &os, const AlcoholicDrink &a) {
        os << a.name << " " << a.country << " " << a.computePrice();
        return os;
    }
    static void changeDiscount(int d) {
        discount = d;
    }
    static int getDiscount() {
        return discount;
    }
    static void total(AlcoholicDrink** ad, int n) {
        float totalWithoutDiscount = 0;
        float totalWithDiscount = 0;
        for (int i = 0; i < n; i++) {
            float p = ad[i]->computePrice();
            totalWithoutDiscount += p;
            totalWithDiscount += p - p * discount / 100.0f;
        }
        cout << "Total price: "<<totalWithoutDiscount << '\n';
        cout<< "Total price with discount: "<< totalWithDiscount << '\n';
    }
};

int AlcoholicDrink::discount = 5;

class Beer : public AlcoholicDrink {
private:
    string mainIngredient;
public:
    Beer(float abv=0, const string &name="", const string &country="", float price=0, bool isBarley=false)
        : AlcoholicDrink(abv, name, country, price) {
        this->mainIngredient = isBarley ? "barley" : "wheat";
    }
    float computePrice() const override {
        return price + (0.05f * (country == "Germany") + 0.10f * (mainIngredient == "wheat")) * price;
    }
};

class Wine : public AlcoholicDrink {
private:
    int year;
    string grapes;
public:
    Wine(float abv=0, const string &name="", const string &country="", float price=0, int year=0, const string &grapes="")
        : AlcoholicDrink(abv, name, country, price), year(year), grapes(grapes) {}
    float computePrice() const override {
        return price + (0.05f * (country == "Italy") + 0.15f * (year < 2005)) * price;
    }
};

void lowestPrice(AlcoholicDrink** a, int n) {
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (a[i]->computePrice() < a[index]->computePrice()) {
            index = i;
        }
    }
    cout << *a[index] << '\n';
}

int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape[20];

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p >> name >> country >> price >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p >> name >> country >> price >> year >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if (testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for (int i = 0; i < n; ++i) {
            cin >> p >> name >> country >> price;
            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        lowestPrice(ad, n);
        for (int i = 0; i < n; ++i) delete ad[i];
        delete[] ad;

    } else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for (int i = 0; i < n; ++i) {
            cin >> p >> name >> country >> price;
            if (i % 2 == 1) {
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            } else {
                cin >> year >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for (int i = 0; i < n; ++i) delete ad[i];
        delete[] ad;
    }
}