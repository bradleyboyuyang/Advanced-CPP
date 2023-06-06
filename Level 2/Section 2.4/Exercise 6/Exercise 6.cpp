/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 6: Weak Pointers

    Name: Boyu Yang

    Problem objective:
    A weak pointer is an observer of a shared pointer. It is useful as a way to avoid dangling pointers and when
    we wish to use shared resources without assuming ownership.
    Answer the following questions:
    a) Create a shared pointer, print the use count and then create a weak pointer that observes it. Print the
    use count again. What are the values?
    b) Assign a weak pointer to a shared pointer and check that the weak pointer is not empty.
    c) Assign a weak pointer to another weak pointer; assign a weak pointer to shared pointer. What is the
    use count in both cases?

*/

#include <iostream>
#include <memory>
#include <vector>


int main() {
    /// a) Create a shared pointer, print the use count and then create a weak pointer that observes it. Print the
    /// use count again. What are the values?
    std::shared_ptr<double> ptr(new double(1.2));
    std::cout << "Reference count before: " << ptr.use_count() << std::endl; // value 1
    std::weak_ptr<double> weakPtr(ptr); // create observer of a shared pointer
    std::cout << "Reference count after (ptr): " << ptr.use_count() << std::endl; // value 1
    std::cout << "Reference count after (weakptr): " << weakPtr.use_count() << std::endl; // value 1
    // We see the reference counts are always 1. The weak pointer does not interfere with the ownership of the shared pointer.
    // The weak pointer seves as an observer of the shared pointer, and therefore does not increase the reference count.
    
    /// b) Assign a weak pointer to a shared pointer and check that the weak pointer is not empty.
    // assign a weak pointer to shared pointer
    std::shared_ptr<double> ptr2 = weakPtr.lock(); // "lock()" returns a shared pointer that points to the same object
    std::cout << "Reference count: " << weakPtr.use_count() << std::endl; // value 2 since another shared pointer is created
    std::cout << "Whether the weak pointer is expired: " << std::boolalpha << weakPtr.expired() << std::endl;
    
    /// c) Assign a weak pointer to another weak pointer; assign a weak pointer to shared pointer. What is the
    /// use count in both cases?
    // assign a weak pointer to another weak pointer
    std::weak_ptr<double> w;
    std::weak_ptr<double> w1 = w;
    std::cout << "Reference count: " << w1.use_count() << std::endl; // value 0 since the weak pointer is not observing any shared pointers
    std::cout << "Whether the weak pointer is expired: " << std::boolalpha << w1.expired() << std::endl; // true, expired

    // assign a weak pointer to a shared pointer
    std::shared_ptr<double> s = w1.lock();
    std::cout << "Reference count: " << w1.use_count() << std::endl; // value 0 since the weak pointer is expired

    // Conclusion: Creating weak pointers will not increase the use count. Creating shared pointers will increase the use count,
    // but ONLY in the case when the assigned weak pointer is not expired yet (compare the results in (b) and (c) we can see).




}