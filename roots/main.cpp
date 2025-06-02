#include <iostream>
#include <cmath>
using namespace std;

class Equation {
public:
    virtual void findRoots() const = 0;
    virtual ~Equation() {}
};

class LinearEquation : public Equation {
private:
    double a, b;
public:
    LinearEquation(double a_, double b_) : a(a_), b(b_) {}

    void findRoots() const override {
        if (a == 0) {
            if (b == 0) {
                cout << "Linear. Infinite number of solutions.\n";
            }
            else {
                cout << "Linear. No solution.\n";
            }
        }
        else {
            double x = -b / a;
            cout << "Linear. Root: x = " << x << endl;
        }
    }
};

class QuadraticEquation : public Equation {
private:
    double a, b, c;
public:
    QuadraticEquation(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    void findRoots() const override {
        if (a == 0) {
            LinearEquation lin(b, c);
            lin.findRoots();
            return;
        }

        double D = b * b - 4 * a * c;

        if (D > 0) {
            double x1 = (-b + sqrt(D)) / (2 * a);
            double x2 = (-b - sqrt(D)) / (2 * a);
            cout << "Quadratic Roots. x1 = " << x1 << ", x2 = " << x2 << endl;
        }
        else if (D == 0) {
            double x = -b / (2 * a);
            cout << "Quadratic Root. x = " << x << endl;
        }
        else {
            cout << "Quadratic. No roots.\n";
        }
    }
};

int main() {
    Equation* eq1 = new LinearEquation(4, -7);
    Equation* eq2 = new QuadraticEquation(2, -4, 5);
    Equation* eq3 = new QuadraticEquation(4,3, 1);
    Equation* eq4 = new LinearEquation(0, 0);

    eq1->findRoots();
    eq2->findRoots();
    eq3->findRoots();
    eq4->findRoots();

    delete eq1;
    delete eq2;
    delete eq3;
    delete eq4;
}
