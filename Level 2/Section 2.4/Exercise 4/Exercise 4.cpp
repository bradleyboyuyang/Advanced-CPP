/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 4: Smart Pointers and STL Algorithms

    Name: Boyu Yang

    Problem objective:
    In this case we create a simple example of STL containers whose elements are smart pointers.
    a) Create a list of smart pointers to Base. In particular, test the above code with both shared and unique
    pointers. Which option compiles and why does unique pointer not compile?
    b) Create a factory function to create instances of Derived and then add them to the list.
    c) Test the functionality and check that there are no memory leaks.
*/

#include <iostream>
#include <memory>
#include <vector>
#include <list>

class Base
{ // Base class 
private:
public:
    Base() { }
    virtual void print() const = 0;
protected:
    virtual ~Base() { std::cout << "Base destructor\n\n"; }
};
class Derived : public Base
{ // Derived class
private:
public:
    Derived() : Base() { }
    ~Derived() { std::cout << "Derived destructor\n"; }
    void print() const { std::cout << "derived object\n"; }
};


/// b) Create a factory function to create instances of Derived and then add them to the list.
std::shared_ptr<Base> createDerived() {
    return std::make_shared<Derived>();
}


int main() {
    /// a) Create a list of smart pointers to Base. In particular, test the above code with both shared and unique
    /// pointers. Which option compiles and why does unique pointer not compile?
    std::list<std::shared_ptr<Base>> sharedList({ std::make_shared<Derived>() }); // work
    //std::list<std::unique_ptr<Base>> uniqueList; // not work
    // The compiler reports that the unique pointer cannot access the protected destructor for Base
    // Shared pointer works because it allows multiple pointers to manage the same object
    // Unique pointers fail because it forbids copy constructor and copy assignment, but std::list requires elements can be copied
    
    /// b) Create a factory function to create instances of Derived and then add them to the list.
    sharedList.push_back(createDerived());
    for (const auto& ptr : sharedList) {
        ptr->print();
    }

    /// c) Test the functionality and check that there are no memory leaks.
    // Each time an object of Base or Derived is destroyed, the corresponding destructor will be called.
    // By checking the destructor messages, we can see that the memory management is handled automatically, no memory leaks.
}