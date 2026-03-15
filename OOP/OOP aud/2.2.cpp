//
// Created by cactus on 09/03/2026.
//
#include <iostream>
#include <string>
using namespace std;
enum position {
    employee, manager, owner
};
class Employee {
private:
    string name;
    int salary;
    position pos;
public:
    Employee(string name = "Unknown", int salary=-1, position pos=employee) {
        this->name = name;
        this->salary = salary;
        this->pos = pos;
    };
    void setName(string name) {
        this->name = name;
    }
    void setSalary(int salary) {
        this->salary = salary;
    }
    void setPos(position pos) {
        this->pos = pos;
    }
    string getName() {
        return name;
    }
    int getSalary() {
        return salary;
    }
    position getPos() {
        return pos;
    }
};
void sortEmployees(Employee employees[],int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j<n-1-i; j++) {
            if (employees[j].getSalary()>employees[j+1].getSalary()) {
                swap(employees[j],employees[j+1]);
            }
        }
    }
}
int main () {
    Employee employees[100];
    int n;
    cin>>n;
    for (int i = 0; i<n; i++) {
        string name;
        int salary;
        int pos;
        cin>>name>>salary>>pos;
        employees[i].setName(name);
        employees[i].setSalary(salary);
        employees[i].setPos(position(pos));
    }
    sortEmployees(employees,n);
    for (int i = 0; i<n; i++) {
        cout<<"Name: "<<employees[i].getName()<<endl;
        cout<<"Salary: "<<employees[i].getSalary()<<endl;
        cout<<"Pos: "<<employees[i].getPos()<<endl;
    }
    return 0;
}