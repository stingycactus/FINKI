//
// Created by cactus on 4/25/2026.
//
#include <iostream>
#include <string>
using namespace std;
class PostOffice;
class Parcel {
protected:
    int id;
    static inline int price=150;

public:
    Parcel(int id = 0) : id(id){}

    static void setProcessingPrice(int newPrice) {
        price = newPrice;
    }
    int getId() const {
        return id;
    }
};

class Envelope : public Parcel {
private:
    int width;
    int height;
    string receiver;

public:
    Envelope(int id = 0, const string &receiver="", int width=0, int height=0)
    : Parcel(id), width(width), height(height), receiver(receiver) {}
    int price() {
        return Parcel::price + width * height * 0.3;
    }
    string getReceiver() const {
        return receiver;
    }
    friend class PostOffice;
};

class PostOffice {
private:
    Envelope envelopes[100];
    int n;
public:
    PostOffice(Envelope *envelopes=nullptr, int n = 0) :  n(n) {
        for (int i = 0; i<n; i++) {
            this->envelopes[i]=envelopes[i];
        }
    }
    int sendEnvelope(int id, const string &receiver, int width, int height) {
        envelopes[n]=Envelope(id, receiver, width, height);
        n++;
        return envelopes[n-1].price();
    }
    void printEnvelopsTo(const string &receiver) {
        cout<<"For "<<receiver<<" are envelops with ids: ";
        for (int i = 0; i<n; i++) {
            if (envelopes[i].receiver == receiver) {
                cout<<(i+1)<<" ";
            }
        }
        cout<<'\n';
    }
};

int main() {
    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) {
            // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(
                id, receiver, width, height) << endl;
        } else if (type == 2) {
            // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) {
            // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) {
            // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {
            // Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.
                    price() << endl;
        }
    }
    return 0;
}
