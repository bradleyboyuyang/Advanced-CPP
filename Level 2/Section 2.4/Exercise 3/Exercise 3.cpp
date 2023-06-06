/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 3: The deprecated Smart Pointer std::auto_ptr

    Name: Boyu Yang

    Problem objective:
    a) Type the given code and run it. Why does it give a run-time error?
    b) Port to code that uses std::unique_ptr. Run and test the new code.
*/

#include <iostream>
#include <memory>

int main() {
    /// a) Type the given code and run it. Why does it give a run-time error?
    //using std::auto_ptr;
    //// Define auto_ptr pointers instead of raw pointers
    //std::auto_ptr <double> d(new double(1.0));
    //// Dereference
    //*d = 2.0;
    //// Change ownership of auto_ptr 
    //// (after assignment, d is undefined)
    //auto_ptr <double> d2 = d;
    //*d2 = 3.0;
    //std::cout << "Auto values: " << *d.get() << ", " << *d2.get();
    
    // The given code produces a run-time error because for auto_ptr, when we assign d to d2, d becomes a dangling pointer,
    // meaning that it points to invalid memory.
    // However auto_ptr allows to dereference a invalid pointer, therefore calling "d.get()" will result in unpredictable behavior.

    /// b) Port to code that uses std::unique_ptr. Run and test the new code.
    std::unique_ptr<double> d(new double(1.0));
    *d = 2.0; // dereference
    std::unique_ptr<double> d2 = std::move(d); // change ownership
    //std::unique_ptr<double> d2 = d; // will cause an error 
    *d2 = 3.0;
    std::cout << "Auto values: " << *d2.get(); 
    // In contrary to auto_ptr, unique_ptr does not allow to have "d.get()", which will cause an error since d is now empty
    // In conclusion, unique_ptr uses exclusive ownership and disables the copy assignment operator or copy constructor
}