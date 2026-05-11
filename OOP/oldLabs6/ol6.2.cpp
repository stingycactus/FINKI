//
// Created by cactus on 4/20/2026.
//
#include <iostream>
using namespace std;

class Square {
protected:
    double a;

public:
    Square(double a=0) : a(a) {}
    Square (const Square &other) : a(other.a) {}
    double perimeter() {
        return a * 4;
    }
    double area() {
        return a * a;
    }
    void print() {
        cout << a << '\n';
        cout<<perimeter()<<'\n';
        cout<<area()<<'\n';
    }
};

class Rectangle : public Square {
private:
    double x;
    double y;
public:
    Rectangle(double x=0, double y=0) : x(x), y(y){}
    Rectangle(const Square &s, double x, double y) : Square(s), x(x), y(y) {}
    Rectangle(const Rectangle &other) : Square(other), x(other.x), y(other.y) {}
    double perimeter() {
        return Square::perimeter() + 2*x + 2*y;
    }
    double area() {
        return (a+x) * (a+y);
    }
    void print() {
        if (x == y) {
            Square::print();
        } else {
            cout << (a+x) << '\n';
            cout << (a+y) << '\n';
            cout << perimeter() << '\n';
            cout << area() << '\n';
        }
    }
};

int main() {
    return 0;
}
