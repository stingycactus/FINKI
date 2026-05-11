//
// Created by cactus on 4/21/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

class RealEstate {
private:
    char *address;
    int sq;
    int pricePerSq;
public:
    RealEstate(const char *address="", int sq=0, int pricePerSq=0) {
        this->address = new char[strlen(address) + 1];
        strcpy(this->address, address);
        this->sq = sq;
        this->pricePerSq = pricePerSq;
    }
    RealEstate(const RealEstate &other) {
        this->address = new char[strlen(other.address) + 1];
        strcpy(this->address, other.address);
        this->sq = other.sq;
        this->pricePerSq = other.pricePerSq;
    }
    RealEstate &operator=(const RealEstate &other) {
        if (this!=&other) {
            delete [] this->address;
            this->address = new char[strlen(other.address) + 1];
            strcpy(this->address, other.address);
            this->sq = other.sq;
            this->pricePerSq = other.pricePerSq;
        }
        return *this;
    }
    ~RealEstate() {
        delete [] this->address;
    }
    int price() {
        return sq * pricePerSq;
    }
    void print() {
        cout<<address<<" "<<sq<<" "<<pricePerSq<<'\n';
        cout<<price()<<'\n';
    }
    float propertyTax() {
        return (price()*0.05);
    }
    friend istream &operator>>(istream &is, RealEstate &e) {
        char temp[100];
        is >> temp >> e.sq >> e.pricePerSq;
        delete[] e.address;
        e.address = new char[strlen(temp) + 1];
        strcpy(e.address, temp);
        return is;
    }
};

class Villa : public RealEstate {
private:
    int luxuryTax;
public:
    Villa (const char *address="", int sq=0, int pricePerSq=0, int luxuryTax=0) :
    RealEstate(address,sq,pricePerSq), luxuryTax(luxuryTax) {}
    void print() {
        RealEstate::print();
        cout<<luxuryTax<<'\n';
    }
    float propertyTax() {
        return (RealEstate::propertyTax()*luxuryTax/100.0);
    }
    friend istream &operator>>(istream &is, Villa &v) {
        RealEstate &e = v;
        is>>e>>v.luxuryTax;
        return is;
    }
};