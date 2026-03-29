//
// Created by cactus on 23/03/2026.
//
#include <iostream>
#include <string>
using namespace std;
class Student {
private:
    string name;
    string idNumber;
    float GPA;
    static int totalStudents;
    static float totalGPA;
public:
    Student() {
        name=" ";
        idNumber=" ";
        GPA=0;
    }
    Student(const string &name,const string &idNumber, const float GPA) {
        this->name = name;
        this->idNumber = idNumber;
        this->GPA = GPA;
        totalStudents++;
        totalGPA += GPA;
    }
    void print() {
        cout << name << " " << idNumber << " " << GPA << endl;
    }
    static int getTotalStudents() {
        return totalStudents;
    }
    static float getAverageGPA() {
        return totalGPA/totalStudents;
    }
};
int Student::totalStudents = 0;
float Student::totalGPA = 0;
int main() {
    int n;
    cout << "Enter number of students" << endl;
    cin >> n;
    Student students[n];
    char name[30], id[10];
    float gpa;
    for (int i = 0; i < n; i++) {
        cin >> name >> id >> gpa;
        students[i] = Student(name, id, gpa);
    }

    for (int i = 0; i < n; i++) {
        students[i].print();
    }
    cout << "Total students: " << Student::getTotalStudents() << endl;
    cout << "Total average: " << Student::getAverageGPA() << endl;
    return 0;
}