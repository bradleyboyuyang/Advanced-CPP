/*
    Level 3.2 3.3: C++ Concurrency
    Problem 3: Active Objects 101

    Name: Boyu Yang

    Problem objective:
    An active object is one that executes in its own thread of control. One advantage of creating/using active
    objects is that it results in a one-to-one correspondence between an object and a thread. C++ does not
    directly support active objects. It only supports passive objects that are acted on by other objects.
    we create an adapter class called ActiveObject that is composed of a thread. The requirements are:
    • ActiveObject has a reference to an instance of an std::thread instance.
    • It has an explicit constructor accepting a thread with associated thread function. The active object
    starts computing as soon as it is instantiated (in principle).
    • In the destructor of ActiveObject we check if the thread is joinable and if it is we then join it.
    • Check that the thread has an associated thread function; use try and catch blocks in client code.
    a) Create a thread and a function that will be its thread function.
    b) Create an active object based on a thread with no associated thread function.
    c) Implement thread functions using function objects and lambda functions.
    d) Test the code.
*/

#include "ActiveObject.hpp"

/// a) Create a thread and a function that will be its thread function.
void threadFunction()
{
    std::cout << "call thread function" << std::endl;
}

/// c) Implement thread functions using function objects and lambda functions.
// lambda function
auto storedLambdaFunc = []() {std::cout << "call stored lambda function" <<std::endl; };

// function object
struct funcObj {
    // overload the () operator to make the object callable
    void operator() () {
        std::cout << "call function object" << std::endl;
    }

    static void staticFunc() {
        std::cout << "call static function" << std::endl;
    }
};

int main()
{
    /// a) Create a thread and a function that will be its thread function.
    // thread function
    std::thread t1{ threadFunction };
    ActiveObject ao1(t1);
    /// b) Create an active object based on a thread with no associated thread function.
    std::thread t2;
    ActiveObject ao2(t2);
    /// c) Implement thread functions using function objects and lambda functions.
    /// d) Test the code
    // function object
    std::thread t3{funcObj()}; 
    ActiveObject ao3(t3);
    // lambda function
    std::thread t4(storedLambdaFunc); 
    ActiveObject ao4(t4);

    // do not need join since already in the destructor of ActiveObject
}
