//
// Created by cactus on 5/28/2026.
//

#include <iostream>

using namespace std;

class Library {
protected:
    string name;
    string city;
    float fee;
    bool worksOnWeekends;
public:
    Library(const string &name="", const string &city="", float fee=0, bool worksOnWeekends=false)
    : name(name), city(city), fee(fee), worksOnWeekends(worksOnWeekends){}
    virtual void printDetail() const = 0;
    virtual double calculateMembershipCardCost() const = 0;
    bool getWorksOnWeekends () const {
        return worksOnWeekends;
    }
};

class AcademicLibrary : public Library {
private:
    bool openResearchOpportunities;
    int specializedCollectionsNumber;
public:
    AcademicLibrary(const string &name="", const string &city="", float fee=0, bool worksOnWeekends=false, bool openResearchOpportunities=false, int specializedCollectionsNumber=0)
    : Library(name,city,fee,worksOnWeekends), openResearchOpportunities(openResearchOpportunities), specializedCollectionsNumber(specializedCollectionsNumber) {}
    double calculateMembershipCardCost() const override {
        return fee + fee * 0.24 * openResearchOpportunities + 6 * specializedCollectionsNumber;
    }
    void printDetail() const override {
        cout<<name<<" - (Academic) "<<city<<" "<<specializedCollectionsNumber<<" "<<calculateMembershipCardCost()<<'\n';
    }
};

class NationalLibrary : public Library {
    private:
    bool culturalEducation;
    int preservedManuscripts;
public:
    NationalLibrary(const string &name="", const string &city="", float fee=0, bool worksOnWeekends=false, bool culturalEducation=false, int preservedManuscripts=0)
    : Library(name,city,fee,worksOnWeekends), culturalEducation(culturalEducation), preservedManuscripts(preservedManuscripts) {}
    double calculateMembershipCardCost() const override {
        return fee - fee * 0.07 * culturalEducation + 15 * preservedManuscripts;
    }
    void printDetail() const override {
        cout<<name<<" - (National) "<<city<<" "<<preservedManuscripts<<" "<<calculateMembershipCardCost()<<'\n';
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<NationalLibrary*>(l[i])) {
            if (index==-1) {
                index = i;
            }
            if (l[i]->calculateMembershipCardCost()>l[index]->calculateMembershipCardCost()) {
                index = i;
            }
            if (l[i]->calculateMembershipCardCost()==l[index]->calculateMembershipCardCost()) {
                if (l[i]->getWorksOnWeekends()) {
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

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
