//
// Created by cactus on 27/04/2026.
//
#include <iostream>
#include <string>
using namespace std;

class HotelReservation {
protected:
    int days;
    int people;
    string fName;
    string lName;

public:
    HotelReservation(const string &fName, const string &lName, int days, int people) : fName(fName), lName(lName),
        days(days), people(people) {
    }

    virtual int price() const {
        return 25 * people * days;
    }

    virtual int price(int amount) const {
        if (amount >= price()) {
            return amount - price();
        }
        cout << "You need to pay " << price() << '\n';
        return -1;
    }
};

class HalfBoardHotelReservation : public HotelReservation {
public:
    HalfBoardHotelReservation(const string &fName, const string &lName, int days, int people) : HotelReservation(
        fName, lName, days, people) {
    }

    int price(int amount) const {
        int totalPrice = HotelReservation::price() + people * 5;
        if (amount >= totalPrice)
            return amount - totalPrice;
        cout << "You need to pay " << totalPrice << endl;
        return -1;
    }
};

class Hotel {
private:
    string name;
    int balance;

public:
    Hotel(const string &name="", int balance=0) : name(name), balance(balance) {}

    int pay(const HotelReservation &hr, int amount) {
        int change = hr.price(amount);
        if (change!=-1) {
            balance+=amount-change;
        }
        return change;
    }
};

int main() {
    Hotel h("Bristol");
    HotelReservation *hr1 = new HotelReservation("Petko", "Petkovski", 5, 5);
    int cena = h.pay(*hr1, 1000);
    if (cena != -1)
        cout << "Change : " << cena << endl;

    HalfBoardHotelReservation *hr2 =
            new HalfBoardHotelReservation("Risto", "Ristovski", 5, 5);
    cena = h.pay(*hr2, 1000);
    if (cena != -1)
        cout << "Change : " << cena << endl;

    HotelReservation *hr3 = new HalfBoardHotelReservation("Ana", "Anovska", 4, 2);
    cena = h.pay(*hr3, 100);
    if (cena != -1)
        cout << "Change : " << cena << endl;

    HalfBoardHotelReservation hr4("Tome", "Tomovski", 5, 3);
    cena = h.pay(hr4, 1000);
    if (cena != -1)
        cout << "Change : " << cena << endl;
}
