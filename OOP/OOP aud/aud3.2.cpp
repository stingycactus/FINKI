//
// Created by cactus on 3/16/2026.
//
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }
};

class Employee {
private:
    string name;
    int salary;
    Date DOB;

public:
    Employee(string name = "", int salary = 0, Date DOB = Date()) {
        this->name = name;
        this->salary = salary;
        this->DOB = DOB;
    }

    int getSalary() {
        return salary;
    }

    Date getDOB() {
        return DOB;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
        cout << "Date of birth: " << DOB.getDay() << "." << DOB.getMonth() << "." << DOB.
                getYear() << endl;
    }
};

class Company {
private:
    string name;
    Date dateEstablished;
    Employee employees[100];
    int numberOfEmployees;

public:
    Company(string name = "", Employee employees[100]=nullptr, int numberOfEmployees = 0, Date establishmentDate = Date()) {
        this->name = name;
        this->dateEstablished = establishmentDate;
        this->numberOfEmployees = numberOfEmployees;
        if (numberOfEmployees > 0) {
            for (int i = 0; i < numberOfEmployees; i++) {
                this->employees[i] = employees[i];
            }
        }
    }

    Employee highestSalary() {
        Employee mostPaid = employees[0];
        for (int i = 1; i < numberOfEmployees; i++) {
            if (employees[i].getSalary() > mostPaid.getSalary()) {
                mostPaid = employees[i];
            }
        }
        return mostPaid;
    }

    Employee youngestEmployee() {
        Employee youngest = employees[0];
        int youngestSum = 365 * youngest.getDOB().getYear() + 30 * youngest.getDOB().getMonth() + youngest.
                          getDOB().getDay();
        for (int i = 1; i < numberOfEmployees; i++) {
            int sumOfDates = 365 * employees[i].getDOB().getYear() + 30 * employees[i].getDOB().getMonth() + employees[
                                 i].getDOB().getDay();
            if (sumOfDates > youngestSum) {
                youngestSum = sumOfDates;
                youngest = employees[i];
            }
        }
        return youngest;
    }

    void addEmployee(Employee employee) {
        if (numberOfEmployees == 100) {
            cout << "Max employees" << '\n';
        }
        else {
            employees[numberOfEmployees] = employee;
            numberOfEmployees++;
        }
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Established on  " << dateEstablished.getDay() << "." << dateEstablished.getMonth() << "." <<
                dateEstablished.
                getYear() << endl;

        cout << "Youngest employee: " << endl;
        youngestEmployee().print();

        cout << "Employee with largest salary: " << endl;
        highestSalary().print();
    }
};

int main() {
    Date d1(1, 1, 1980);
    Date d2(1, 2, 1983);
    Date d3(11, 12, 1984);
    Date d4(30, 3, 2011);
    Date d5(30, 5, 1974);

    Employee v[3];
    Employee v1("Marjan", 40000, d1);
    Employee v2("Stefan", 30000, d2);
    Employee v3("Marko", 20000, d3);
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;

    Company c("FINKI", v, 3, d4);

    c.print();


    Employee v4("Darko", 50000, d5);
    c.addEmployee(v4);

    c.print();

    return 0;
}
