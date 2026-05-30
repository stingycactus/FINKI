//
// Created by cactus on 5/29/2026.
//


#include <iostream>
#include <cstring>
using namespace std;

class Tickets {
protected:
    int ID[12];
    string event;
    float price;
    static int discount;
public:
    Tickets(int *ID=nullptr, const string &event="", float price=0) {
        for (int i = 0; i < 12; i++) {
            this->ID[i] = ID[i];
        }
        this->event = event;
        this->price = price;
    }
    friend ostream &operator<<(ostream &os, const Tickets &t) {
        for (int i = 0; i<12; i++) {
            os<<t.ID[i];
        }
        os<<"-"<<t.event<<"-";
        os<<t.presmetajCena();
        return os;
    }
    bool falsifikat(int from, int to) {
        int last4=ID[8]*1000+ID[9]*100+ID[10]*10+ID[11];
        return (last4>=from && last4<=to);
    }
    virtual float presmetajCena() const {
        return price;
    }

    static void changeDiscount(int d) {
        discount = d;
    }
};

int Tickets::discount = 0;

class Online : public Tickets {
private:
    bool premium;
public:
    Online(int *ID=nullptr, const string &event="", float price=0, bool premium=false)
        : Tickets(ID, event, price), premium(premium) {}
    float presmetajCena() const override {
        float base = Tickets::presmetajCena();
        return base - base * 0.15f * premium - base * discount / 100.f;
    }
};

class Offline : public Tickets {
private:
    bool reservation;
public:
    Offline(int *ID=nullptr, const string &event="", float price=0, bool reservation=false)
        : Tickets(ID, event, price), reservation(reservation) {}
    float presmetajCena() const override {
        float base = Tickets::presmetajCena();
        return base + base * 0.10f * reservation - base * discount / 100.f;
    }
};

void vkupenPrihod(Tickets ** t, int n, int from, int to) {
    float totalIncome = 0;
    for (int i = 0; i < n; i++) {
        totalIncome += t[i]->presmetajCena() * t[i]->falsifikat(from, to);
    }
    cout<<totalIncome;
}

// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION
int main() {
    int testCase;
    cin >> testCase;
    int ID[12];
    char nastan[100];
    float price;
    bool premium;
    bool rezervacija;
    int od, doo;

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> premium;
        Online o1(ID, nastan, price, premium);
        cout << o1 << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> rezervacija;
        Offline o2(ID, nastan, price, rezervacija);
        cout << o2 << endl;

    }
    else if (testCase == 2) {
        cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
        int n;
        cin >> n;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; j++)
                cin >> ID[j];
            cin >> nastan;
            cin >> price;

            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        cin >> od;
        cin >> doo;
        vkupenPrihod(t, n, od, doo);
        for (int i = 0; i < n; ++i) {
            delete t[i];
        }
        delete[] t;
    }
    else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        //cout<<n<<endl;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; ++j)
                cin >> ID[j];
            cin >> nastan;
            //cout<<nastan<<endl;
            cin >> price;
            //cout<<price<<endl;
            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                //cout<<rezervacija<<endl;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        int d;
        cin >> d;
        Tickets::changeDiscount(d);
        for (int i = 0; i < n; ++i)
            cout << *t[i] << endl;

    }
}
