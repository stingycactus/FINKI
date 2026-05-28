//
// Created by cactus on 5/28/2026.
//
#include <iostream>
#include <cstring>

using namespace std;

class Museum {
protected:
    string name;
    string city;
    float ticket;
    int hours;
public:
    Museum(const string& name="", const string &city="", float ticket=0, int hours=0)
    : name(name), city(city), ticket(ticket), hours(hours) {}
    virtual void printDetail() const = 0;
    virtual double calculateTicketCost() const = 0;
    int getHours() const {
        return hours;
    }
};

class ScientificMuseum: public Museum {
private:
    bool interactive;
    int multimediaPresentations;
public:
    ScientificMuseum(const string& name="", const string &city="", float ticket=0, int hours=0, bool interactive=false, int multimediaPresentations=0)
    : Museum(name,city,ticket,hours), interactive(interactive), multimediaPresentations(multimediaPresentations) {}
    double calculateTicketCost() const override {
        return ticket + ticket * 0.12 * interactive + 6 * multimediaPresentations;
    }
    void printDetail() const override {
        cout<<name<<" - (Scientific) "<<city<<" "<<multimediaPresentations<<" "<<calculateTicketCost()<<'\n';
    }
};

class ArtMuseum : public Museum {
private:
    bool amateurExhibitions;
    int originals;
public:
    ArtMuseum(const string& name="", const string &city="", float ticket=0, int hours=0, bool amateurExhibitions=false, int originals=0)
    : Museum(name,city,ticket,hours), amateurExhibitions(amateurExhibitions), originals(originals) {}
    double calculateTicketCost() const override {
        return ticket - ticket * 0.18 * amateurExhibitions + originals * 3;
    }
    void printDetail() const override {
        cout<<name<<" - (Art) "<<city<<" "<<amateurExhibitions<<" "<<calculateTicketCost()<<'\n';
    }
};

int findCheapestScientificMuseum(Museum **m, int n) {
    int index=-1;
    for (int i = 0; i<n; i++) {
        if (dynamic_cast<ScientificMuseum*>(m[i])) {
            if (index==-1) {
                index=i;
            }
            if (m[i]->calculateTicketCost()<m[index]->calculateTicketCost()) {
                index=i;
            }
            if (m[i]->calculateTicketCost()==m[index]->calculateTicketCost()) {
                if (m[i]->getHours()>m[index]->getHours()) {
                    index=i;
                }
            }
        }
    }
    return index;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetail();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}