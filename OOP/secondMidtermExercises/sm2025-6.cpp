//
// Created by cactus on 5/28/2026.
//
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

class StudentFailedException {
private:
    string id;
public:
    StudentFailedException(const string &id) : id(id) {}
    void print() {
        cout<<"Student with id "<<id<<" failed the course"<<'\n';
    }
};

class Student {
private:
    string index;
    string firstName;
    string lastName;
    int points;
public:
    Student(const string &index="", const string &firstName="", const string &lastName="", int points=0)
    : index(index), firstName(firstName), lastName(lastName), points(points) {}
    int grade() const {
        if (points<50) {
            return 5;
        }
        if (points>=100) {
            return 10;
        }
        return points/10 + 1;
    }
    friend ostream &operator<<(ostream &os, const Student &s) {
        os<<s.index<<" "<<s.firstName<<" "<<s.lastName<<" "<<s.points<<" Grade: "<<s.grade()<<'\n';
        return os;
    }
    string getIndex() const {
        return index;
    }
    friend istream &operator>>(istream &is, Student &s) {
        is>>s.index>>s.firstName>>s.lastName>>s.points;
        return is;
    }
};

class Results {
private:
    Student *students;
    int n;
public:
    Results(Student *students=nullptr, int n=0) {
        this->n=n;
        this->students=new Student[n];
        for (int i = 0; i<n; i++) {
            this->students[i]=students[i];
        }
    }
    ~Results() {
        delete [] this->students;
    }
    Results(const Results &other) {
        this->n=other.n;
        this->students=new Student[n];
        for (int i = 0; i<n; i++) {
            this->students[i]=other.students[i];
        }
    }
    Results &operator=(const Results &other) {
        if (this!=&other) {
            delete [] this->students;
            this->n=other.n;
            this->students=new Student[n];
            for (int i = 0; i<n; i++) {
                this->students[i]=other.students[i];
            }
        }
        return *this;
    }
    Results &operator+=(const Student &s) {
        if (s.grade()<6) {
            throw StudentFailedException(s.getIndex());
        }
        Student *temp = new Student[n+1];
        for (int i = 0; i<n; i++) {
            temp[i]=students[i];
        }
        delete [] students;
        students=temp;
        students[n]=s;
        n++;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Results &r) {
        for (int i = 0; i<r.n; i++) {
            os<<r.students[i];
        }
        return os;
    }
    Results withGrade(int grade) {
        Results result;
        for (int i = 0; i<n; i++) {
            if (students[i].grade()==grade) {
                result+=students[i];
            }
        }
        return result;
    }
    int getN() const {
        return n;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();

    Results results;
    //TODO your code here
    //TODO Read the students from the file and add them in `results`
    ifstream fin("input.txt");
    Student s;
    while (fin>>s) {
        try {
            results+=s;
        }catch (StudentFailedException &e) {
            e.print();
        }
    }


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    ofstream fout1("output1.txt");
    ofstream fout2("output2.txt");
    fout1<<results;
    Results filtered = results.withGrade(grade);
    if (filtered.getN()) {
        fout2<<filtered;
    }
    else {
        fout2<<"None"<<'\n';
    }
    fout1.close();
    fout2.close();
    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}