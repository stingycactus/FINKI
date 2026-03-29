//
// Created by cactus on 28/03/2026.
//
#include <cstring>
#include <iostream>
using namespace std;

class Student {
private:
    char *name;
    float avgGrade;
    int schoolYear;

public:
    Student(const char *name = "", float avgGrade = 0, int schoolyear = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->avgGrade = avgGrade;
        this->schoolYear = schoolyear;
    }

    Student(const Student &s) {
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->avgGrade = s.avgGrade;
        this->schoolYear = s.schoolYear;
    }

    ~Student() {
        delete [] name;
    }

    Student &operator++() {
        schoolYear++;
        return *this;
    }

    Student operator++(int) {
        Student temp = *this;
        schoolYear++;
        return temp;
    }
    Student operator=(const Student &other) {
        if (this == &other) {
            return *this;
        }
        delete [] name;
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name, other.name);
        this->avgGrade=other.avgGrade;
        this->schoolYear=other.schoolYear;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Student &s) {
        os << s.name << " " << s.avgGrade << " " << s.schoolYear << '\n';
        return os;
    }
    bool operator>(const Student &other) {
        return avgGrade>other.avgGrade;
    }
    float getAvgGrade() {
        return avgGrade;
    }
};

class Group {
private:
    Student *students;
    int size;
public:
    Group (Student *students = nullptr, int size = 0) {
        this->size = size;
        this->students = new Student[size];
        for (int i = 0; i<size; i++) {
            this->students[i] = students[i];
        }
    }
    Group (const Group &g) {
        this->size = g.size;
        this->students = new Student[size];
        for (int i = 0; i<g.size; i++) {
            this->students[i]=g.students[i];
        }
    }
    ~Group() {
        delete [] students;
    }
    Group &operator+=(const Student &s) {
        Student *temp = new Student[size+1];
        for (int i = 0; i<size; i++) {
            temp[i]=students[i];
        }
        temp[size] = s;
        size++;
        delete [] students;
        students = temp;
        return *this;
    }
    Group &operator++() {
        for (int i = 0; i<size; i++) {
            students[i]++;
        }
        return *this;
    }
    Group operator++(int) {
        Group temp = *this;
        for (int i = 0; i<size; i++) {
            students[i]++;
        }
        return temp;
    }
    friend ostream &operator<<(ostream &os, const Group &g) {
        for (int i = 0; i<g.size; i++) {
            os << g.students[i];
        }
        return os;
    }
    void nagradi() {
        for (int i = 0; i<size; i++) {
            if (students[i].getAvgGrade()==10.0) {
                cout<<students[i];
            }
        }
    }
    Student najvisokProsek() {
        Student bestStudent = students[0];
        for (int i = 1; i<size; i++) {
            if (students[i].getAvgGrade()>bestStudent.getAvgGrade()) {
                bestStudent=students[i];
            }
        }
        return bestStudent;
    }
};

int main() {
    Student u1("Martina Martinovska", 9.5, 3);
    Student u2("Darko Darkoski", 7.3, 2);
    Student u3("Angela Angelovska", 10, 3);

    Group p;
    p += u1;
    p += u2;
    p += u3;

    cout << p;
    cout << "Nagradeni:" << endl;
    p.nagradi();
    cout << endl;
    p.najvisokProsek();
    cout << endl;

    u2++;
    cout << p;
    cout << endl;
    p++;
    cout << p;

    return 0;
}
