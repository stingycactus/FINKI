//
// Created by cactus on 09/03/2026.
//
#include <iostream>
using namespace std;
struct Vector {
    float x;
    float y;
    float z;
    float scalarProduct(Vector other) {
        return x*other.x + y*other.y + z*other.z;
    }
    Vector vectorProduct(Vector other) {
        Vector result;
        result.x = y*other.z - z*other.y;
        result.y = z*other.x - x*other.z;
        result.z = x*other.y - y*other.x;
        return result;
    }
    void print() {
        cout << "[" << x << ", " << y << ", " << z << "]" << endl;
    }
};
int main() {
    Vector v1(2,4,6);
    Vector v2(3,5,9);
    cout<<v1.scalarProduct(v2)<<endl;
    v1.vectorProduct(v2).print();
    return 0;
}