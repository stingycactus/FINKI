//
// Created by cactus on 5/4/2026.
//
#include <iostream>
using namespace std;

class Shape {
protected:
    double h;
public:
    virtual ~Shape() = default;

    Shape(double h=0.0) : h(h) {}
    virtual void print() const = 0;
    virtual double volume() const = 0;
    double getHeight() {
        return h;
    }
};

class Cylinder : public Shape {
private:
    double r;

public:
    Cylinder(double h, double r)
        : Shape(h),
          r(r) {
    }
    void print() const {
        cout<<h<<" "<<r<<'\n';
    }
    double volume() const {
        return r*r*3.14*h;
    }
    double getR() const {
        return r;
    }
};
class Cone : public Shape {
private:
    double r;
public:
    Cone(double h, double r)
        : Shape(h),
          r(r) {
    }
    void print() const {
        cout<<h<<" "<<r<<'\n';
    }
    double volume() const {
        return r*r*3.14*h/3.0;
    }
    double getR() const {
        return r;
    }
};

class Cuboid : public Shape {
    private:
    double a,b;
    public:
    Cuboid(double a, double b, double h) : Shape(h), a(a), b(b) {}
    void print() const {
        cout<<a<<" "<<b<<" "<<h<<'\n';
    }
    double volume() const {
        return a*b*h;
    }
};

void maxVolume(Shape *array[], int n) {
    int index=0;
    for (int i = 0; i<n; i++) {
        if (array[i]->volume()>array[index]->volume()) {
            index = i;
        }
    }
    return array[index]->print();
}

double getRadius(Shape *s) {
    Cylinder *cylinder = dynamic_cast<Cylinder *>(s);
    Cone *cone = dynamic_cast<Cone *>(s);
    if (cylinder) {
        return cylinder->getR();
    }
    if (cone) {
        return cone->getR();
    }
    return -1;
}

int main() {
    Shape** shapes; // dynamically allocated array of pointers of Shape
    int n;
    cin >> n; // number of elements in the array
    shapes = new Shape*[n]; // allocate the pointer array
    for (int i = 0 ; i < n ; i++) {
        int r, a, b, h, type;
        cout << "Shape: 1-cylinder 2-cone 3-cuboid" << endl;
        cin >> type;
        if (type == 1) { // for Cylinder
            cin >> r >> h; shapes[i] = new Cylinder(r, h);
        } else if (type == 2) { // for Cone
            cin >> r >> h; shapes[i] = new Cone(r, h);
        } else if (type == 3) { // for Cuboid
            cin >> a >> b >> h; shapes[i] = new Cuboid(a, b, h);
        }
    }
    // 1.
    maxVolume(shapes, n);
    // 2.
    int counter = 0;
    for (int i = 0 ; i < n ; i++)
        if (getRadius(shapes[i]) == -1)
            counter++;
    cout << "Number of shapes with base circle is " << counter;
}
