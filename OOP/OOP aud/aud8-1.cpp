//
// Created by cactus on 11/05/2026.
//
// was having weird issue naming this file 8.1, for some reason clion would complain
// about file not being found and can't compile even though cmakelists was correct, lol.
#include <iostream>
using namespace std;

class Vehicle {
public:
    Vehicle() {
        cout << "Vehicle testing in progress" << '\n';
    }
    virtual ~Vehicle() {
        cout << "~Vehicle testing in progress" << '\n';
    }
    virtual void accelerate() {
        cout << "Accelerate testing in progress" << '\n';
    }
};

class Car : virtual public Vehicle {
public:
    Car() {
        cout << "Car testing in progress" << '\n';
    }
    ~Car() {
        cout << "~Car testing in progress" << '\n';
    }
    void drive() {
        cout << "Drive testing in progress" << '\n';
    }
};

class Jet : virtual public Vehicle {
public:
    Jet() {
        cout << "Jet testing in progress" << '\n';
    }
    ~Jet() {
        cout << "~Jet testing in progress" << '\n';
    }
    void fly() {
        cout << "Fly testing in progress" << '\n';
    }
};

class JetCar: public Car, public Jet {
public:
    JetCar() {
        cout << "JetCar testing in progress" << '\n';
    }
    ~JetCar() {
        cout << "~JetCar testing in progress" << '\n';
    }
    void drive() {
        cout << "JetCar Drive testing in progress" << '\n';
    }
    void fly() {
        cout << "JetCar Fly testing in progress" << '\n';
    }
};

void analyzeCarPerformance(Car *testVehicle) {
    testVehicle->drive();
    //method drive() can also be called with a pointer to the base and
    //to the derived class. this function is defined in both classes
}
void analyzeJetPerformance(Jet *testVehicle) {
    testVehicle->fly();
    //fly() is defined in base and derived class (Jet & JetCar)
}

int main() {
    Car myCar;
    Jet myJet;
    JetCar myJetCar;
    cout << endl << endl;
    cout << "Car testing in progress" << endl;
    analyzeCarPerformance(&myCar);
    analyzeCarPerformance(&myJetCar);
    cout << "Jet testing in progress" << endl;
    analyzeJetPerformance(&myJet);
    analyzeJetPerformance(&myJetCar);
    cout << endl << endl;
    return 0;
}