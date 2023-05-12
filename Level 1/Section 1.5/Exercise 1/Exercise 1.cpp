#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using VoidFunctionType = std::function<void(double)>;

// Class hierarchy
class Shape
{
protected:
    VoidFunctionType f;
public:
    Shape() = default; // default constructor
    Shape(const VoidFunctionType& func) {
        f = func;
    }
    void rotate(double d) {
        f(d); // call the protected function wrapper
    }
};
class Circle : public Shape
{
public:
    Circle(const VoidFunctionType& func) {
        f = func;
    }
    void rotate(double d2) { f(d2); }
};



int main()
{
    // • Create a constructor in the base and derived classes to initialize f with a target method, having a
    //  compatible signature with void rotate(double d).
    // • Modify void rotate(double d) in the base class so that it calls f.
    // • The derived classes may override void rotate(double d).
    // • Create a test program with various examples of f.

    // Test function
    VoidFunctionType func1 = [](const double& d) {std::cout << d * d << std::endl; };
    double param = 4;
    Shape sp(func1);
    sp.rotate(param);
    Circle cl(func1);
    cl.rotate(param);

    VoidFunctionType func2 = [](const double& d) {std::cout << d + 1 << std::endl; };
    Shape sp2(func2);
    sp2.rotate(param);
    Circle cl2(func2);
    cl2.rotate(param);
    // As we can see, although rotate() is not a virtual function, we still achieve polymorphism even with more flexibility
    // The function rotate() in the derived class behaves differently for different protected function wrapper

}