#include <cstring>
#include <iostream>
using namespace std;

class PlDrustvo {
    char *name;
    int tours;
    int members;
public:
    PlDrustvo(const char*name="",int tours=0, int members=0) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->tours=tours;
        this->members=members;
    }
    ~PlDrustvo() {
        delete [] name;
    }
    PlDrustvo(const PlDrustvo &other) {
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->tours=other.tours;
        this->members=other.members;
    }
    PlDrustvo &operator=(const PlDrustvo &other) {
        if (this == &other) {
            return *this;
        }
        delete [] this->name;
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->tours=other.tours;
        this->members=other.members;
        return *this;
    }
    PlDrustvo operator+(const PlDrustvo &other) {
        int totalMembers = members+other.members;
        PlDrustvo toReturn = *this;
        if (toReturn.members < other.members) {
            toReturn=other;
        }
        toReturn.members=totalMembers;
        return toReturn;
    }
    bool operator>(const PlDrustvo &other) {
        return members>other.members;
    }
    bool operator<(const PlDrustvo &other) {
        return members<other.members;
    }
    friend ostream &operator<<(ostream &os, const PlDrustvo &other) {
        os<<"Ime: "<<other.name<<" Turi: "<<other.tours<<" Clenovi: "<<other.members<<'\n';
        return os;
    }
    int getMembers() const {
        return members;
    }
};

void najmnoguClenovi(PlDrustvo drustva[], int n) {
    PlDrustvo biggest = drustva[0];
    int biggestMemberCount = drustva[0].getMembers();
    for (int i = 1; i<n; i++) {
        if (drustva[i].getMembers()>biggestMemberCount) {
            biggest=drustva[i];
            biggestMemberCount=drustva[i].getMembers();
        }
    }
    cout<<"Najmnogu clenovi ima planinarskoto drustvo: "<<biggest;
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}