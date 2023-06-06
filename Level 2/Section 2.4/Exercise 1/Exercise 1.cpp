/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 1: First Encounters with Smart Pointers: Unique Pointers

    Name: Boyu Yang

    Problem objective:
    a) Type, run and test the given code. Introduce a try-catch block in which memory is allocated and
    directly afterwards an exception is thrown. Since the code is not re-entrant, the memory is not
    reclaimed and hence introduces a memory leak (in more general cases it would be a resource leak).
    b) Now port the above code by replacing raw pointers by std::unique_ptr. Run the code. Are there
    memory leaks now?
    c) Experiment with the following: initialising two unique pointers to the same pointer, assigning a unique
    pointer to another unique pointers and transferring ownership from one unique pointer to another
    unique pointer.
    d) Use alias template (template typedef) to make the code more readable.
*/

#include "Point.hpp"

int main() {
    /// a) Type, run and test the given code. Introduce a try-catch block in which memory is allocated and
    /// directly afterwards an exception is thrown. Since the code is not re-entrant, the memory is not
    /// reclaimed and hence introduces a memory leak (in more general cases it would be a resource leak).
    std::cout << "Using raw pointers: \n";
    { // Block with raw pointer lifecycle
        double* d = new double(1.0);
        Point* pt = new Point(1.0, 2.0); // Two-d Point class

        // Dereference and call member functions
        *d = 2.0;
        (*pt).X(3.0); // Modify x coordinate
        (*pt).Y(3.0); // Modify y coordinate

        // Can use operators for pointer operations
        pt->X(3.0); // Modify x coordinate
        pt->Y(3.0); // Modify y coordinate

        // try-catch block, direct exception thrown after allocating memory
        // In this case, we have a memory leak because the memory allocated for the second "Point" object inside
        // the try-catch block is not freed before the exception is thrown
        try {
            Point* pt = new Point(1.0, 2.0);
            throw - 1; // throw an exception
        }
        catch (int i) {
        std::cout << "An exception is thrown after memory is allocated" << std::endl;
        }

        // Explicitly clean up memory (if you have not forgotten)
        delete d;
        delete pt; 
    }
    
    /// b) Now port the above code by replacing raw pointers by std::unique_ptr. Run the code. Are there memory leaks now?
    std::cout << "Using unique pointers: \n";
    { // Block with unique pointer lifecycle
        std::unique_ptr<double> d(new double(1.0));
        std::unique_ptr<Point> pt(new Point(1.0, 2.0)); // Two-d Point class

        // Dereference and call member functions
        *d = 2.0;
        (*pt).X(3.0); // Modify x coordinate
        (*pt).Y(3.0); // Modify y coordinate

        // Can use operators for pointer operations
        pt->X(3.0); // Modify x coordinate
        pt->Y(3.0); // Modify y coordinate

        // try-catch block
        try {
            std::unique_ptr<Point> pt = std::make_unique<Point>(1.0, 2.0);
            throw - 1; // throw an exception
        }
        catch (int i) {
            std::cout << "An exception is thrown after memory is allocated" << std::endl;
        }
    }
    // We can see from the output of the destructor, with "unique_ptr", the memory will be automatically released
    // when the smart pointers go out of scope. Hence there is no memory leak now.

    /// c) Experiment with the following: initialising two unique pointers to the same pointer, assigning a unique
    /// pointer to another unique pointers and transferring ownership from one unique pointer to another unique pointer.
    // initialize two unique pointers to the same pointer
    double* dptr = new double(2.0);
    std::unique_ptr<double> ptr_1(dptr);
    //std::unique_ptr<double> ptr_2(dptr); // Error: unique_ptr uses exclusive ownership

     // assign a unique pointer to another 
    std::unique_ptr<double> ptr(new double(3.4));
    //std::unique_ptr<double> ptr2 = ptr1; // Error: unique_ptr does not allow copy assignment because of exclusive ownership

    // transferring ownership from one unique pointer to another
    std::unique_ptr<int> ptr1(new int(5));
    std::unique_ptr<int> ptr2;
    ptr2 = std::move(ptr1); // ownership transfer through move semantics

    /// d) Use alias template (template typedef) to make the code more readable.
    // We can use the alias to replace the previous std::unique_ptr<Point> to make the code more readable
    using UniquePtr = std::unique_ptr<Point>;
    UniquePtr uptr(new Point(5.5,4.5));
}