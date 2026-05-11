//
// Created by cactus on 4/20/2026.
//
#include <iostream>
using namespace std;

class Doctor {
private:
    int fax;
    string fName;
    string lName;
    float baseSalary;
public:
    Doctor (int fax=0, const string &fName="", const string &lName="", float baseSalary=0) :
    fax(fax), fName(fName), lName(lName), baseSalary(baseSalary) {}
    Doctor &operator=(const Doctor &other) = default;
    void print() {
        cout<<fax<<": "<<fName<<" "<<lName<<'\n';
    }
    float salary() {
        return baseSalary;
    }
};

class HeadDoctor : public Doctor {
    int numberOfPatients;
    float *fees;
public:
    HeadDoctor(int fax=0, const string &fName="", const string &lName="", float baseSalary=0, int numberOfPatients=0, float *fees=nullptr) :
    Doctor(fax, fName, lName, baseSalary) {
        this->numberOfPatients = numberOfPatients;
        this->fees = new float[numberOfPatients];
        for (int i = 0; i < numberOfPatients; i++) {
            this->fees[i]=fees[i];
        }
    }
    HeadDoctor(const HeadDoctor &other) : Doctor(other) {
        this->numberOfPatients = other.numberOfPatients;
        this->fees = new float[numberOfPatients];
        for (int i = 0; i < numberOfPatients; i++) {
            this->fees[i]=other.fees[i];
        }
    }
    HeadDoctor &operator=(const HeadDoctor &other) {
        if (this!= &other) {
            Doctor::operator=(other);
            delete [] this->fees;
            this->numberOfPatients = other.numberOfPatients;
            this->fees = new float[numberOfPatients];
            for (int i = 0; i < numberOfPatients; i++) {
                this->fees[i]=other.fees[i];
            }
        }
        return *this;
    }
    ~HeadDoctor() {
        delete [] this->fees;
    }
    double averageCollectedFees() {
        float avg = 0;
        for (int i = 0; i<numberOfPatients; i++) {
            avg += this->fees[i];
        }
        avg /= numberOfPatients;
        return avg;
    }
    void print() {
        Doctor::print();
        cout<<"avg: "<<averageCollectedFees()<<'\n';
    }
    double salary() {
        return (Doctor::salary()+ 0.3*averageCollectedFees());
    }
};

int main() {
    return 0;
}