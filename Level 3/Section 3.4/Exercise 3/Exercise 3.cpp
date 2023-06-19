/*
    Level 3.4: C++11 Tasks
    Problem 3: C++11 Promises 101

    Name: Boyu Yang

    Problem objective:
    A promise is the counterpart of a future object. Both are able to temporarily hold a shared state. Thus, a
    promise is a general mechanism to allow values and exceptions to be passed out of threads. A promise is
    the “push” end of the promise-future communication channel.
    a) Create a default promise, a promise with an empty shared state and a promise based on the move constructor.
    b) Create a promise with double as stored value. Then create a future that is associated with the promise.
    c) Start a thread with the new future from part b). Create a thread function that uses the value of the shared data.
    d) Use the promise to set the value of the shared data.
*/

#include <iostream>
#include <future>
#include <memory>
#include <thread>

int main() {
    /// a) Create a default promise, a promise with an empty shared state and a promise based on the move constructor.
    // default promise
    std::promise<double> ps1;
    // promise with empty shared state
    std::promise<double> ps2(std::allocator_arg, std::allocator<double>());
    // promise based on a move constructor
    std::promise<double> ps3(std::move(ps1));

    /// b) Create a promise with double as stored value. Then create a future that is associated with the promise.
    std::promise<double> ps4;
    std::future<double> fut = ps4.get_future();

    /// c) Start a thread with the new future from part b). Create a thread function that uses the value of the shared data.
    std::thread t([&fut]() {
        double value = fut.get();
        std::cout << "The value of the shared data is: " << value << std::endl;
        });

    /// d) Use the promise to set the value of the shared data.
    ps4.set_value(23.4);
    t.join();
    // The final printed result is 23.4, if we join the thread before setting the value we will not get any result,
    // because we haven't set the value for the promise, using "get()" then will continue waiting for set_value()
    // After setting the value we can get() the stored value and therefore the thread finishes.
}