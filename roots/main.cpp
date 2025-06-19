#include <iostream>
#include <cmath>
using namespace std;

class EquationException {
public:
    virtual const char* what() const {
        return "Equation error occurred.";
    }
};

class DivisionByZeroException : public EquationException {
public:
    const char* what() const override {
        return "Cannot divide by zero (a = 0).";
    }
};

class NoRealRootsException : public EquationException {
public:
    const char* what() const override {
        return "No real roots (discriminant < 0).";
    }
};

class InfiniteSolutionsException : public EquationException {
public:
    const char* what() const override {
        return "Infinite number of solutions (0x = 0).";
    }
};

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
                throw InfiniteSolutionsException();
            }
            else {
                throw DivisionByZeroException();
            }
        }
        double x = -b / a;
        cout << "Linear. Root: x = " << x << endl;
    }
};

class QuadraticEquation : public Equation {
private:
    double a, b, c;
public:
    QuadraticEquation(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    void findRoots() const override {
        if (a == 0) {
            // Öå âæå ë³í³éíå ð³âíÿííÿ
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
            throw NoRealRootsException();
        }
    }
};

int main() {
    Equation* equations[4];
    equations[0] = new LinearEquation(4, -7);     
    equations[1] = new QuadraticEquation(2, -4, 5);  
    equations[2] = new QuadraticEquation(4, 3, 1);
    equations[3] = new LinearEquation(0, 0); 

    for (int i = 0; i < 4; ++i) {
        try {
            equations[i]->findRoots();
        }
        catch (EquationException& e) {
            cout << "Exception: " << e.what() << endl;
        }
        delete equations[i];
    }

    return 0;
}
