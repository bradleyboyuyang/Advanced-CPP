/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 2: Shared Pointers

    Name: Boyu Yang

    Problem objective:
    Create two classes C1 and C2 that share a common heap-based object as data member: std::shared_ptr<double> d;
    a) Create the code for the classes C1 and C2 each of which contains the shared object from the value d above
    b) Create instances of these classes in scopes so that you can see that resources are automatically
    released when no longer needed. To this end, employ the member function use_count() to keep
    track of the number of shared owners. This number should be equal to 0 when the program exits.
    c) Carry out the same exercise as in steps a) and b) but with a user-defined type as shared data: std::shared_ptr<Point> p;
    d) Now extend the code in parts a) to c) to include the following operations on shared pointers: assigning,
    copy and compare two shared pointers sp1 and sp2. Furthermore, test the following features (some
    research needed here):
    • Transfer ownership from sp1 to sp2.
    • Determine if a shared pointer is the only owner of a resource.
    • Swap sp1 and sp2.
    • Give up ownership and reinitialise the shared pointer as being empty.
*/

#include "Point.hpp"
#include "C.hpp"
#include "C2.hpp"

int main() {
    /// b) Create instances of these classes in scopes so that you can see that resources are automatically
    /// released when no longer needed. To this end, employ the member function use_count() to keep
    /// track of the number of shared owners. This number should be equal to 0 when the program exits.
    std::cout << "=========Code for Part (B)========= \n";
    {
        std::cout << "Built-in types\n";
        std::shared_ptr<double> commonValue(new double(3.1415)); // create a shared pointer
        { // block with object2 lifecycle
            std::cout << "Reference count: " << commonValue.use_count() << std::endl; // the reference count is 1
            {// block with object1 lifecycle
                C1 object1(commonValue);
                std::cout << "Reference count: " << commonValue.use_count() << std::endl; // reference count becomes 2
                object1.print();
            } // object1 has gone out of scope, the resources will automatically released, reference count becomes 1
            C2 object2(commonValue);
            std::cout << "Reference count: " << commonValue.use_count() << std::endl; // the reference count again becomes 2
            object2.print();
        } // object2 ends its lifecycle, reference count 
        std::cout << "Reference count: " << commonValue.use_count() << std::endl; // the reference count becomes 1
    }
    // Out of scope for C1, C2 instances, use_count becomes 0

    /// c) Carry out the same exercise as in steps a) and b) but with a user-defined type as shared data: std::shared_ptr<Point> p;
    std::cout << "=========Code for Part (C)========= \n";
    {
        std::cout << "Built-in types\n";
        std::shared_ptr<Point> commonValue2(new Point(1.0, 2.0)); // create a shared pointer
        { // block with object2 lifecycle
            std::cout << "Reference count: " << commonValue2.use_count() << std::endl; // the reference count is 1
            {// block with object1 lifecycle
                NewC1 obj1(commonValue2);
                std::cout << "Reference count: " << commonValue2.use_count() << std::endl; // reference count becomes 2
                obj1.print();
            } // object1 has gone out of scope, the resources will automatically released, reference count becomes 1
            NewC2 obj2(commonValue2);
            std::cout << "Reference count: " << commonValue2.use_count() << std::endl; // the reference count again becomes 2
            obj2.print();
        } // object2 ends its lifecycle, reference count 
        std::cout << "Reference count: " << commonValue2.use_count() << std::endl; // the reference count becomes 1
    }
    // Out of scope for C1, C2 instances, use_count becomes 0


    /// d) Now extend the code in parts a) to c) to include the following operations on shared pointers: assigning,
    /// copy and compare two shared pointers sp1 and sp2. Furthermore, test the following features (some
    /// research needed here):
    //• Transfer ownership from sp1 to sp2.
    //• Determine if a shared pointer is the only owner of a resource.
    //• Swap sp1 and sp2.
    //• Give up ownership and reinitialise the shared pointer as being empty.
        // Transfer ownership from sp1 to sp2
    std::cout << "=========Code for Part (D)========= \n";
    std::shared_ptr<Point> sp1 = std::make_shared<Point>(1.0, 2.0);
    std::shared_ptr<Point> sp2 = sp1; // assigning pointers
    std::shared_ptr<Point> sp3 = std::make_shared<Point>(*sp1); // copy, does not increase reference count
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl; // Outputs: 2
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl; // Outputs: 2

    // Determine if a shared pointer is the only owner of a resource
    std::cout << "Is sp1 the unique owner? " << (sp1.unique() ? "Yes" : "No") << std::endl; // Outputs: No

    // Swap sp1 and sp2
    sp1.swap(sp2);
    std::cout << "After swapping:\n";
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl; // Outputs: 2
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl; // Outputs: 2

    // Give up ownership and reinitialize the shared pointer as empty
    sp1.reset();
    std::cout << "After giving up ownership:\n";
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl; // Outputs: 0
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl; // Outputs: 1




}