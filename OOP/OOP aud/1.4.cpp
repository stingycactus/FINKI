//
// Created by cactus on 09/03/2026.
//
#include <iostream>
#include <string>
using namespace std;
struct City {
    string name;
    int population;
    void readCity() {
        cin>>name>>population;
    }

};
struct President {
    string name;
    string surname;
    string politicalParty;
    void readPresident() {
        cin>>name>>surname>>politicalParty;
    }
};
struct Country {
    string name;
    President president;
    City capital;
    int population;
    void readCountry() {
        cin>>name;
        president.readPresident();
        capital.readCity();
        cin>>population;
    }
    void printCountryPresident() {
        cout<<president.name<<" "<<president.surname<<'\n';
    }
};
Country MaxCapital(Country country[],int n) {
    Country maxCapital = country[0];
    for (int i = 1; i < n; i++) {
        if (country[i].capital.population>maxCapital.capital.population) {
            maxCapital = country[i];
        }
    }
    return maxCapital;
}
int main() {
    Country country[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        country[i].readCountry();
    }
    Country maxCapital = MaxCapital(country,n);
    maxCapital.printCountryPresident();
    return 0;
}