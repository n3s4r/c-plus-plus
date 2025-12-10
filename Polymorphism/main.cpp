#include <iostream>
using namespace std;

// Abstract class
class Shape {
public:
    // Pure virtual function (makes Shape an abstract class)
    virtual double area() const = 0;

    // Virtual destructor (good practice)
    virtual ~Shape() {}
};

// Derived class: Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.1416 * radius * radius;
    }
};

// Derived class: Rectangle
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }
};

int main() {
    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 6.0);

    cout << "Area of Circle: " << s1->area() << endl;
    cout << "Area of Rectangle: " << s2->area() << endl;

    delete s1;
    delete s2;

    return 0;
}
