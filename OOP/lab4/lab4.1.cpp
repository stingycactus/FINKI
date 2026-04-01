//
// Created by cactus on 01/04/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

class Automobile {
private:
    char *brand;
    int *registration;
    int size;
    int capacity;
    int maxSpeed;
public:
    Automobile(const char *brand = "", int *registration=nullptr, int maxSpeed=0, int capacity=5) {
        this->brand = new char[strlen(brand)+1];
        strcpy(this->brand,brand);
        this->maxSpeed=maxSpeed;
        this->capacity=capacity;
        this->registration=new int[capacity];
        this->size=capacity;
        if (registration!=nullptr) {
            for (int i = 0; i<size; i++) {
                this->registration[i]=registration[i];
            }
        }
    }
    ~Automobile() {
        delete [] brand;
        delete [] registration;
    }
    Automobile(const Automobile &other) {
        this->brand = new char[strlen(other.brand)+1];
        strcpy(this->brand,other.brand);
        this->maxSpeed=other.maxSpeed;
        this->capacity=other.capacity;
        this->registration=new int[capacity];
        this->size=other.size;
        for (int i = 0; i<size; i++) {
            this->registration[i]=other.registration[i];
        }
    }
    Automobile &operator=(const Automobile &other) {
        if (this == &other) {
            return *this;
        }
        delete [] brand;
        delete [] registration;
        this->brand = new char[strlen(other.brand)+1];
        strcpy(this->brand,other.brand);
        this->maxSpeed=other.maxSpeed;
        this->capacity=other.capacity;
        this->registration=new int[capacity];
        this->size=other.size;
        for (int i = 0; i<size; i++) {
            this->registration[i]=other.registration[i];
        }
        return *this;
    }
    bool operator==(const Automobile &other) {
        if (registration==other.registration) {
            return true;
        }
        for (int i = 0; i<size; i++) {
            if (registration[i]!=other.registration[i]) {
                return false;
            }
        }
        return true;
    }
    friend ostream &operator<<(ostream &os, const Automobile &car) {
        os<<"Marka\t"<<car.brand<<"\tRegistracija[ ";
        for (int i = 0; i<car.size; i++) {
            os<<car.registration[i]<<" ";
        }
        os<<"]"<<'\n';
        return os;
    }
    int *getRegistration() const {
        return registration;
    }
    int getMaxSpeed() const {
        return maxSpeed;
    }
    int getSize() const {
        return size;
    }
};

class RentACar {
private:
    char agencyName[100];
    Automobile *automobiles;
    int size;
    int capacity;
public:
    RentACar(const char *agencyName="", int capacity=1) {
        strcpy(this->agencyName,agencyName);
        this->capacity=capacity;
        automobiles = new Automobile[capacity];
        this->size=0;
    }
    ~RentACar() {
        delete [] automobiles;
    }
    RentACar(const RentACar &other) {
        strcpy(this->agencyName,other.agencyName);
        this->capacity=other.capacity;
        this->size=other.size;
        automobiles = new Automobile[capacity];
        for (int i = 0; i<size; i++) {
            this->automobiles[i]=other.automobiles[i];
        }
    }
    RentACar &operator=(const RentACar &other) {
        if (this == &other) {
            return *this;
        }
        delete [] automobiles;
        strcpy(this->agencyName,other.agencyName);
        this->capacity=other.capacity;
        this->size=other.size;
        automobiles = new Automobile[capacity];
        for (int i = 0; i<size; i++) {
            this->automobiles[i]=other.automobiles[i];
        }
        return *this;
    }
    RentACar &operator+=(const Automobile &car) {
        if (size==capacity) {
            capacity++;
            Automobile *temp = new Automobile[capacity];
            for (int i = 0; i<size; i++) {
                temp[i]=this->automobiles[i];
            }
            delete [] automobiles;
            automobiles=temp;
        }
        automobiles[size]=car;
        size++;
        return *this;
    }
    RentACar &operator-=(const Automobile &car) {
        int index=0;
        for (int i = 0; i<size; i++) {
            bool uniqueRegistration=false;
            for (int j = 0; j<automobiles[i].getSize(); j++) {
                if (automobiles[i].getRegistration()[j]!=car.getRegistration()[j]) {
                    uniqueRegistration=true;
                }
            }
            if (uniqueRegistration) {
                automobiles[index]=automobiles[i];
                index++;
            }
        }
        size=index;
        return *this;
    }
    void pecatiNadBrzina(int max) {
        cout<<agencyName<<'\n';
        for (int i = 0; i<size; i++) {
            if (automobiles[i].getMaxSpeed()>max) {
                cout<<automobiles[i];
            }
        }
    }
};

int main()
{
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0;i<5;i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}