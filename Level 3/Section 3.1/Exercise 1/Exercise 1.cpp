/*
    Level 3.1: Threads
    Problem 1: Thread Class in C++11 101

    Name: Boyu Yang

    Problem objective:
    • Creating and launching instances of std::thread.
    • Using various kinds of callable objects as a thread’s start function.
    • Waiting on threads to complete; has a thread finished executing code, but has not yet been joined?
    (use joinable()).
    • Creating threads that run in the background (detached/daemon threads).
    • Passing arguments to a thread function.
    The threads that you create all call a function that prints a string a number of times on the console. A
    typical interface is Iprint(const std::string& s, int count).
    a) Create as many callable objects as you can (free functions, lambda function and stored lambda
    function, function object, binded member function, static member function) that all call the interface
    Iprint above.
    b) Create a thread for each of the callable objects in part a). One of the threads should be a detached
    thread. Each thread’s function has its own unique ID.
    c) Introduce code to check if threads have completed and then join each one if this is the case.
    d) We need to introduce exception handling in the case that a thread may not be joined. In these cases
    we need to introduce join() inside the catch blocks.
    e) Print the thread ID of each thread in each implementation of Iprint.
    f) Compute the running time of the program based on the example code in the summary based on
    std::chrono. Examine the output; what do you see? What is happening?
*/

#include <thread>
#include <iostream>
#include <functional>

/// f) prints the thread ID of each thread in Iprint
// A typical function that prints a string a number of times on the console
void Iprint(const std::string& s, int count) {
    for (int i = 0; i < count; i++)
        std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
}

// free function
void freeFunc() {
    Iprint("free function", 2);
}

// lambda function
auto storedLambdaFunc = []() {Iprint("stored lambda function", 2); };

// function object
struct funcObj {
    // overload the () operator to make the object callable
    void operator() () {
        Iprint("function object", 2);
    }

    static void staticFunc() {
        Iprint("static member function", 2);
    }
};

/// c) Introduce code to check if threads have completed and then join each one if this is the case.
/// d) We need to introduce exception handling in the case that a thread may not be joined. In these cases
/// we need to introduce join() inside the catch blocks.
// function to check whether a thread has completed and join it if yes
// introduce the try-catch block as required
void join(std::thread& t) {
    if (t.joinable()) {
        t.join();
    }
    else {
        try {
            t.join();
        }
        catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
}

int main() {
    /// a) Create as many callable objects as you can (free functions, lambda function and stored lambda function, function object, 
    /// binded member function, static member function) that all call the interface Iprint above.
    /// b) Create a thread for each of the callable objects in part a). One of the threads should be a detached
    /// thread. Each thread’s function has its own unique ID.
    // mark the start time
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    // create threads for each of the callable objects
    std::thread t1{ freeFunc }; // free function
    std::thread t2{ []() {Iprint("lambda function", 2); } }; // lambda function
    std::thread t3{ storedLambdaFunc }; // stored lambda function
    std::thread t4{ funcObj() }; // function object
    std::thread t5{ funcObj::staticFunc }; // static function
    std::thread t6{std::bind(Iprint, "binded function", 2)}; // binded function
    // detach one thread as required
    t6.detach();

    /// c) Introduce code to check if threads have completed and then join each one if this is the case.
    /// d) We need to introduce exception handling in the case that a thread may not be joined. In these cases
    /// we need to introduce join() inside the catch blocks.
    join(t1);
    join(t2);
    join(t3);
    join(t4);
    join(t5);
    join(t6); // will throw an exception since we cannot join the detached thread

    /// f) Compute the running time of the program based on the example code in the summary based on
    /// std::chrono. Examine the output; what do you see? What is happening?
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end-start;
    std::cout << "Elapsed time: " << duration.count() << "s" << std::endl;

}