//
// Created by cactus on 31/03/2026.
//
#include <cstring>
#include <iostream>
using namespace std;
class DonationSociety;

class DonationAction {
    char *name;
    char *idNumber;
    int collectedFundValue;
    int neededFundValue;

public:
    DonationAction(const char *name = "", const char *idNumber = "", int collectedFundValue = 0,
                   int neededFundValue = 0) {
        this->name = new char[strlen(name) + 1];
        this->idNumber = new char [strlen(idNumber) + 1];
        strcpy(this->name, name);
        strcpy(this->idNumber, idNumber);
        this->collectedFundValue = collectedFundValue;
        this->neededFundValue = neededFundValue;
    }

    ~DonationAction() {
        delete [] name;
        delete [] idNumber;
    }

    DonationAction(const DonationAction &other) {
        this->name = new char[strlen(other.name) + 1];
        this->idNumber = new char [strlen(other.idNumber) + 1];
        strcpy(this->name, other.name);
        strcpy(this->idNumber, other.idNumber);
        this->collectedFundValue = other.collectedFundValue;
        this->neededFundValue = other.neededFundValue;
    }

    DonationAction &operator=(const DonationAction &other) {
        delete [] name;
        delete [] idNumber;
        this->name = new char[strlen(other.name) + 1];
        this->idNumber = new char [strlen(other.idNumber) + 1];
        strcpy(this->name, other.name);
        strcpy(this->idNumber, other.idNumber);
        this->collectedFundValue = other.collectedFundValue;
        this->neededFundValue = other.neededFundValue;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const DonationAction &donation_action) {
        if (donation_action.collectedFundValue >= donation_action.neededFundValue) {
            os << donation_action.idNumber << " " << donation_action.name << " collected" << '\n';
        } else {
            os << donation_action.idNumber << " " << donation_action.name << " " << donation_action.neededFundValue -
                    donation_action.collectedFundValue << " more denars are needed" << '\n';
        }
        return os;
    }

    DonationAction &operator+=(int n) {
        collectedFundValue += n;
        return *this;
    }

    bool operator<(const DonationAction &other) {
        int notCollected1 = neededFundValue - collectedFundValue;
        int notCollected2 = other.neededFundValue - other.collectedFundValue;
        if (notCollected1==notCollected2) {
            return strlen(idNumber) > strlen(other.idNumber);
        }
        return notCollected1 < notCollected2;
    }

    friend class DonationSociety;
};

class DonationSociety {
private:
    char president[31];
    DonationAction *actions;
    int size;
    int capacity;

public:
    DonationSociety(const char *president = "", int capacity = 10) {
        strcpy(this->president, president);
        this->capacity = capacity;
        this->actions = new DonationAction[capacity];
        this->size = 0;
    }

    ~DonationSociety() {
        delete [] actions;
    }

    DonationSociety(const DonationSociety &other) {
        strcpy(this->president, other.president);
        this->capacity = other.capacity;
        this->actions = new DonationAction[capacity];
        this->size = other.size;
        for (int i = 0; i < size; i++) {
            this->actions[i] = other.actions[i];
        }
    }

    DonationSociety &operator=(const DonationSociety &other) {
        delete [] actions;
        strcpy(this->president, other.president);
        this->capacity = other.capacity;
        this->actions = new DonationAction[capacity];
        this->size = other.size;
        for (int i = 0; i < size; i++) {
            this->actions[i] = other.actions[i];
        }
        return *this;
    }

    bool takeDonation(char id[], int donatedFund) {
        for (int i = 0; i < size; i++) {
            if (strcmp(actions[i].idNumber, id) == 0) {
                actions[i].collectedFundValue += donatedFund;
                return true;
            }
        }
        return false;
    }

    DonationSociety &operator+=(const DonationAction &donationAc) {
        bool unique = true;
        for (int i = 0; i < size; i++) {
            if (strcmp(donationAc.idNumber, actions[i].idNumber) == 0) {
                unique = false;
            }
        }
        if (unique) {
            if (size == capacity) {
                capacity *= 2;
                DonationAction *temp = new DonationAction[capacity];
                for (int i = 0; i < size; i++) {
                    temp[i] = actions[i];
                }
                delete [] actions;
                actions = temp;
            }
            actions[size] = donationAc;
            size++;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, DonationSociety &ds) {
        for (int i = 0; i < ds.size - 1; i++) {
            for (int j = 0; j < ds.size - 1 - i; j++) {
                if (ds.actions[j] < ds.actions[j + 1]) {
                    swap(ds.actions[j], ds.actions[j + 1]);
                }
            }
        }
        for (int i = 0; i < ds.size; i++) {
            os << ds.actions[i];
        }
        os << "President:" << ds.president << '\n';
        return os;
    }
};


int main() {
    DonationSociety donacii("Velko Velkovski");
    int n;
    char naziv[50], id[50];
    int potrebnasuma, doniranasuma;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin.get();
        cin.getline(naziv, 50);
        cin >> id >> potrebnasuma;
        bool hasLetter=false;
        for (int i = 0; i<strlen(id); i++) {
            if (isalpha(id[i])) {
                hasLetter=true;
            }
        }
        if (strlen(id)>9) {
            cout<<"The id number has more than 9 characters"<<'\n';
        }
        else if (hasLetter) {
            cout<<"The id number has a non-digit character"<<'\n';
        }
        else if (strlen(id) <= 9) {
            DonationAction edna(naziv, id, 0 , potrebnasuma);
            donacii += edna;
        }
    }

    //donation
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> id >> doniranasuma;

        if (!donacii.takeDonation(id, doniranasuma))
            cout << "The donation is not taken. Wrong ID." << endl;
    }
    cout << "===============" << endl;
    cout << donacii;
}
