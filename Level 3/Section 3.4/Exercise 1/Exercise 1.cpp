/*
    Level 3.4: C++11 Tasks
    Problem 1: Tasks 101: Running Functions asynchronously

    Name: Boyu Yang

    Problem objective:
    For this exercise, you need to understand C++11 futures, std::async and thread/task launching policies.
    This exercise involves running synchronous and asynchronous functions based on various launch policies.
    The functions should have both void and non-void return types to show how clients can use the results
    of computations. The objective is not in creating complex functions but in showing how the tasks execute
    and exchange information.
    a) Create two functions having the given signatures
    You may place any code into the body of these functions for the purpose of this exercise.
    b) Use std::async (default settings) to launch func1 and func2. Get the results of the computations
    and print them when applicable. Check the validity of the associated future before and after getting
    the result.
    c) What happens if you try to get the result of a std::future more than once?
    d) Now test the same code using the launch parameter std::launch::async. Do you notice any
    differences?
    e) We now wish to asynchronously call a function at some time later in the client code (deferred/lazy
    evaluation). Get the result of the function and check that it is the same as before.
*/

#include <iostream>
#include <future>

/// a) Create two functions having the following signatures
void func1()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "func1" << std::endl;
}
double func2(double a, double b)
{
    std::cout << "func2" << std::endl;
    return a + b;
}


int main() {
    /// b) Use std::async (default settings) to launch func1 and func2. Get the results of the computations
    /// and print them when applicable. Check the validity of the associated future before and after getting the result.
    std::future<void> result1(std::async(func1));
    std::future<double> result2(std::async(func2, 1.1, 2.2));
    // check validity, check whether the future has a shared state
    std::cout << std::boolalpha;
    std::cout << "F1 valid before: " << result1.valid() << std::endl;
    std::cout << "F2 valid before: " << result2.valid() << std::endl;
    // since return of func1 is void, we use wait (future block until result is available) rather than get (until a valid result)
    result1.wait();
    std::cout << "F2 output: " << result2.get() << std::endl;
    // check validity
    std::cout << "F1 valid after: " << result1.valid() << std::endl; // true
    std::cout << "F2 valid after: " << result2.valid() << std::endl; // false

    /// c) What happens if you try to get the result of a std::future more than once?
    // We will get an exception since any shared state is released after calling get()
    try {
        double output = result2.get();
    }
    catch (const std::exception& e) {
        std::cout << "caught exception: " << e.what() << std::endl;
    }

    /// d) Now test the same code using the launch parameter std::launch::async. Do you notice any differences?
    std::future<void> res1(std::async(std::launch::async, func1));
    std::future<double> res2(std::async(std::launch::async, func2, 1.1, 2.2));
    std::cout << "F1 valid before: " << res1.valid() << std::endl;
    std::cout << "F2 valid before: " << res2.valid() << std::endl;
    res1.wait();
    std::cout << "F2 output: " << res2.get() << std::endl;
    // check validity
    std::cout << "F1 valid after: " << res1.valid() << std::endl; // true
    std::cout << "F2 valid after: " << res2.valid() << std::endl; // false
    // The previous test gives random console output, since std::async executes the task in a thread pool or a new thread.
    // However, using std::launch::async will execute the task on a different thread, creating and 
    // launching F1 first. Therefore we get tidy console output. 

    /// e) We now wish to asynchronously call a function at some time later in the client code (deferred/lazy
    /// evaluation). Get the result of the function and check that it is the same as before.
    std::future<double> result(std::async(std::launch::deferred, func2, 1.1, 2.2));
    std::cout << "F2 valid before: " << result.valid() << std::endl;
    // Using a lazy evaluation (std::launch::defered) will execute the task the first time when the result is requested.
    // Therefore we always get the console output "func2" after the following line (the first time we retrieve the data)
    std::cout << "F2 output: " << result.get() << std::endl;
    // check validity
    std::cout << "F2 valid after: " << result.valid() << std::endl;
}