//
// Created by cactus on 5/27/2026.
//
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class InvalidCodeFormatException {
private:
    string code;
public:
    InvalidCodeFormatException(const string &code=""):code(code){}
    void print() {
        cout<<"The code "<<code<<" is invalid doctor code format. THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA."<<'\n';
    }
};

class Doctor {
protected:
    string firstName;
    string lastName;
    float salary;
    string code;
public:
    Doctor(const string &firstName="", const string &lastName="", const string &code="", float salary=0)
    : firstName(firstName), lastName(lastName), salary(salary) {
        if (code.length()!=8) {
            throw InvalidCodeFormatException(code);
        }
        for (int i = 0; i<code.length(); i++) {
            if (code[i]==',') {
                throw InvalidCodeFormatException(code);
            }
        }
        this->code=code;
    }
    virtual float calculateSalary() const = 0;
    virtual void print() const = 0;
};

class GeneralDoctor: public Doctor {
private:
    int patients;
    static int baseSalary;
public:
    GeneralDoctor(const string &firstName="", const string &lastName="", const string &code="", int patients=0)
    : Doctor(firstName, lastName, code), patients(patients) {}
    float calculateSalary() const override {
        return (baseSalary + 3000 * (patients/10)) * 0.93;
    }
    void print() const override {
        cout<<"General Doctor: "<<firstName<<" "<<lastName<<" CODE:"<<code<<" Salary: "<<calculateSalary()<<'\n';
    }
};

int GeneralDoctor::baseSalary=45000;

class Specialist : public Doctor {
private:
    string specialty;
    int interventions;
    int experience;
    static int baseSalary;
public:
    Specialist(const string &firstName="", const string &lastName="", const string &code="", const string &specialty="", int interventions=0, int experience=0)
    : Doctor(firstName, lastName, code), specialty(specialty), interventions(interventions), experience(experience) {}
    float calculateSalary() const override {
        return (baseSalary + 85 * interventions + 0.05 * baseSalary * experience) * 0.93;
    }
    void print() const override {
        cout<<"Specialist: "<<firstName<<" "<<lastName<<" CODE:"<<code<<" "<<specialty<<" Salary: "<<calculateSalary()<<'\n';
    }
};

int Specialist::baseSalary = 55000;

void findDoctorsPercentage(Doctor **doctors, int n) {
    float totalDoctors=0;
    float totalSpecialists=0;
    int totalCount=0;
    for (int i = 0; i < n; i++) {
        if (dynamic_cast<GeneralDoctor*>(doctors[i])) {
            totalDoctors++;
            totalCount++;
        }
        if (dynamic_cast<Specialist*>(doctors[i])) {
            totalSpecialists++;
            totalCount++;
        }
    }
    cout<<totalSpecialists/totalCount*100<<"% of the doctors are specialists and "<<totalDoctors/totalCount*100<<"% are general doctors."<<'\n';
}

int main()
{
    int testCase, n;
    string name, surname, specialty, code;
    int numberOfPatients, yearsOfExperience, numberOfInterventions;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "TESTING GENERAL DOCTOR CLASS" << endl;
            Doctor *d = new GeneralDoctor("John", "Smith", "236XY@2B", 120);
            Doctor *d1 = new GeneralDoctor("Marco", "Brown", "345X!Y2B", 120);
            Doctor *d2 = new GeneralDoctor("Emily", "Johnson", "ABCD123@", 230);
            d->print();
            d1->print();
            d2->print();

        cout << "GENERAL DOCTOR CLASS OK!" << endl;
    }
    else if (testCase == 2)
    {
        cout << "TESTING SPECIALIST DOCTOR CLASS" << endl;
            Doctor *d = new Specialist("Beth", "Davis", "96Tr$$33", "Cardiologist", 45, 5);
            Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
            Doctor *d2 = new Specialist("Micheal", "Rosen", "7896YZ$s", "Radiologist", 41, 10);
            d->print();
            d1->print();
            d2->print();
        cout << "SPECIALIST DOCTOR CLASS OK!" << endl;
    }
    else if (testCase == 3)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new GeneralDoctor("John", "Smith", "23Y@2B", 120);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }


        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 4)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 5)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        try {
            Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
            d->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }

        try {
            Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
            d1->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        try {
            Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
            d2->print();
        } catch (InvalidCodeFormatException &e) {
            e.print();
        }
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else
    {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION!" << endl;
        cin >> n;
        Doctor **doctors = new Doctor *[n];
        for (int i = 0; i < n; i++)
        {
            int t;
            cin >> t;
            cin >> name >> surname;
            cin >> code;
            if (t == 1) // General doctor
            {
                cin >> numberOfPatients;
                    try {
                       doctors[i] = new GeneralDoctor(name, surname, code, numberOfPatients);
                    } catch (InvalidCodeFormatException &e) {
                        e.print();
                    }

            }
            else // Specialist
            {
                cin >> specialty;
                cin >> numberOfInterventions >> yearsOfExperience;
                try {
                    doctors[i] = new Specialist(name, surname, code, specialty, numberOfInterventions, yearsOfExperience);
                } catch (InvalidCodeFormatException &e) {
                    e.print();
                }
            }
        }
        cout << "LIST OF ALL DOCTORS: " << endl;
        for (int i = 0; i < n; i++)
        {
            if (doctors[i]) {
                doctors[i]->print();
            }
        }
        findDoctorsPercentage(doctors, n);
        for (int i = 0; i < n; i++)
        {
            delete doctors[i];
        }
        delete[] doctors;
    }
    return 0;
}
