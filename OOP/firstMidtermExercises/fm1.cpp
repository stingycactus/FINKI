//
// Created by cactus on 30/03/2026.
//
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

class Driver {
private:
    char name[100];
    int time;

public:
    Driver(const char name[] = "", int time = 0) {
        strcpy(this->name, name);
        this->time = time;
    }

    int getTime() {
        return time;
    }

    char *getName() {
        return name;
    }
};

class Race {
private:
    char location[100];
    int numberOfDrivers;
    Driver drivers[100];

public:
    Race(const char *location = "", int numberOfDrivers = 0, Driver drivers[] = nullptr) {
        strcpy(this->location, location);
        this->numberOfDrivers = numberOfDrivers;
        for (int i = 0; i < numberOfDrivers; i++) {
            this->drivers[i] = drivers[i];
        }
    }

    void sortDrivers() {
        for (int i = 0; i < numberOfDrivers - 1; i++) {
            for (int j = 0; j < numberOfDrivers - 1 - i; j++) {
                if (drivers[j].getTime() > drivers[j + 1].getTime()) {
                    swap(drivers[j], drivers[j + 1]);
                }
            }
        }
    }

    void printDrivers() {
        cout << location << " (" << numberOfDrivers << " Drivers)" << '\n';

        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << drivers[i].getName() << " " << drivers[i].getTime() / 60 << ":" << setfill('0') <<
                    setw(2) << drivers[i].getTime() % 60 << '\n';
        }
    }
};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char location[100];
        int numberOfDrivers;
        cin >> location;
        cin >> numberOfDrivers;
        Driver drivers[100];
        for (int j = 0; j < numberOfDrivers; j++) {
            char driverName[100];
            int driverTime;
            cin >> driverName;
            cin >> driverTime;
            drivers[j] = Driver(driverName, driverTime);
        }
        Race race(location, numberOfDrivers, drivers);
        race.sortDrivers();
        race.printDrivers();
    }
    return 0;
}
