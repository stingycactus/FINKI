//
// Created by cactus on 1/20/2026.
//
#include <iostream>
using namespace std;
class Person {
public:
    string name;
    char gender;
    int age;
    Person(string name, char gender, int age) {
        this->name = name;
        this->gender = gender;
        this->age = age;
    }
    Person () {
        name="";
        gender='?';
        age=-1;
    }
    void printInfo() const {
        cout<<"Name: "<<name<<'\n';
        cout<<"Gender: "<<gender<<'\n';
        cout<<"Age: "<<age<<'\n';
    }
};

int main() {
    Person p1("Filip", 'M', 19);
    p1.printInfo();
    Person p2;
    p2.name = "Katja";
    p2.age = 21;
    p2.gender = 'F';
    p2.printInfo();
    return 0;
}