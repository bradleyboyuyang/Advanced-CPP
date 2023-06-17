/*
    Level 3.2: C++ Concurrency
    Problem 1: Atomic Operations on Shared Pointers

    Name: Boyu Yang

    Problem objective:
    In general, shared pointers are not thread-safe. However, reading the count while another thread modifies
    a shared pointer does not introduce a race condition but the value may not be up-to-date.
    The syntax in this context is a bit tricky. In particular, you have to take memory ordering into account.
    a) Create an instance x of class PointerType and give it a value.
    b) Create a second instance x2 and atomically store it value in x.
    c) Create an instance x3 and exchange it with both x and x2.
    d) Keep tabs on the use count of these instances.
    e) Why is atomic<std::shared_ptr> not possible?
    f) Are shared pointers lock-free?
*/

#include <iostream>
#include <atomic>


// Given class
struct X
{
    double val;
    X() : val(0.0) {}
    void operator ()()
    {
        std::cout << "An X " << val << std::endl;
    }
};
// C++11
template <typename T>
using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;


int main() {
    /// a) Create an instance x of class PointerType and give it a value.
    PointerType x(new X);
    x->val = 123;

    /// b) Create a second instance x2 and atomically store it value in x.
    PointerType x2(new X);
    x2->val = 1234;
    (*x)(); // old value 123
    std::atomic_store(&x, x2);
    (*x)(); // new value 1234

    /// c) Create an instance x3 and exchange it with both x and x2.
    PointerType x3(new X);
    x3->val = 12345;
    PointerType old_x3 = std::atomic_exchange(&x3, x);
    std::cout << "new value of x3: " << x3->val << ", old value of x3: " << old_x3->val << std::endl;
    old_x3 = std::atomic_exchange(&x3, x2);
    std::cout << "new value of x3: " << x3->val << ", old value of x3: " << old_x3->val << std::endl;

    /// d) Keep tabs on the use count of these instances.
    std::cout << "use count for x: " << x.use_count() << std::endl;
    std::cout << "use count for x2: " << x2.use_count() << std::endl;
    std::cout << "use count for x3: " << x3.use_count() << std::endl;
    
    /// e) Why is atomic<std::shared_ptr> not possible ?
    // Because shared pointers are not thread-safe and std::atomic is used for atomic operations and it requires
    // the operated type to be a "copyable" type. The internal state of std::shared_ptr involves no-atomic increment and 
    // decrement operations to ensure the correct increment and decrement of reference count. Therefore it is not possible
    // to let the shared pointers to be atomic.
    
    /// f) Are shared pointers lock - free ?
    std::cout << "Is shared pointer lock-free: " << std::boolalpha << std::atomic_is_lock_free(&x) << std::endl;
    // False as expected. Shared pointers are not lock free and they cannot be processed by multiple threads at the same time.

}