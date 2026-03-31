//
// Created by cactus on 31/03/2026.
//
#include <cstring>
#include <iostream>
class SkiCenter;
using namespace std;

class SkiLift {
private:
    char name[16];
    int maxUsers;
    bool isWorking;

public:
    SkiLift(const char *name = "", int maxUsers = 0, bool isWorking = false) {
        strcpy(this->name, name);
        this->maxUsers = maxUsers;
        this->isWorking = isWorking;
    }

    int getMaxUsers() {
        return maxUsers;
    }

    friend void biggestCapacity(SkiCenter *sc, int n);
};

class SkiCenter {
private:
    char name[21];
    char country[21];
    SkiLift skiLifts[20];
    int numberOfSkiLifts;

public:
    SkiCenter(const char *name = "", const char *country = "", SkiLift *skiLifts = nullptr, int numberOfSkiLifts = 0) {
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->numberOfSkiLifts = numberOfSkiLifts;
        for (int i = 0; i < numberOfSkiLifts; i++) {
            this->skiLifts[i] = skiLifts[i];
        }
    }

    friend void biggestCapacity(SkiCenter *sc, int n);
};

void biggestCapacity(SkiCenter *sc, int n) {
    SkiCenter biggestSkiCenter = sc[0];
    int biggestCapacity = 0;
    for (int j = 0; j < sc[0].numberOfSkiLifts; j++) {
        biggestCapacity += sc[0].skiLifts[j].maxUsers*sc[0].skiLifts[j].isWorking;
    }
    for (int i = 1; i < n; i++) {
        int capacity = 0;
        for (int j = 0; j < sc[i].numberOfSkiLifts; j++) {
            capacity += sc[i].skiLifts[j].maxUsers*sc[i].skiLifts[j].isWorking;
        }
        if (capacity > biggestCapacity) {
            biggestCapacity=capacity;
            biggestSkiCenter = sc[i];
        }
        else if (capacity == biggestCapacity) {
            if (sc[i].numberOfSkiLifts > biggestSkiCenter.numberOfSkiLifts) {
                biggestCapacity=capacity;
                biggestSkiCenter = sc[i];
            }
        }
    }
    cout << biggestSkiCenter.name << '\n';
    cout << biggestSkiCenter.country << '\n';
    cout << biggestCapacity << '\n';
}

int main() {
    int n;
    cin >> n;
    SkiCenter skicenters[n];
    for (int i = 0; i < n; i++) {
        char centerName[16];
        char country[21];
        int numberOfSkis;
        cin >> centerName >> country >> numberOfSkis;
        SkiLift s[numberOfSkis];
        for (int j = 0; j < numberOfSkis; j++) {
            char skiName[21];
            int maxUsers;
            bool status;
            cin >> skiName >> maxUsers >> status;
            s[j]=SkiLift(skiName, maxUsers, status);
        }
        skicenters[i]=SkiCenter(centerName, country, s, numberOfSkis);
    }
    biggestCapacity(skicenters,n);
    return 0;
}
