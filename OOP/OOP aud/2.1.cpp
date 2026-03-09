//
// Created by cactus on 09/03/2026.
//
#include <iostream>
#include <cmath>
using namespace std;
class Triangle {
private:
    int a,b,c;
    public:
    Triangle(int a=0,int b=0,int c=0) {
        this->a=a;
        this->b=b;
        this->c=c;
    };
    float perimeter() {
        return a+b+c;
    }
    float area() {
        float s = perimeter()/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }
    void readTriangle() {
        cin>>a>>b>>c;
    }
    void printTriangleInfo() {
        cout<<perimeter()<<endl;
        cout<<area()<<endl;
    }
};
int main() {
    Triangle t;
    t.readTriangle();
    t.printTriangleInfo();
    return 0;
}