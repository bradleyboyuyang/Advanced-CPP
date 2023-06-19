/*
    Level 3.4: C++11 Tasks
    Problem 2: Shared Futures 101

    Name: Boyu Yang

    Problem objective:
    We wish to process the outcome of a concurrent computation more than once, especially when multiple
    threads are running and to this end we use std::shared_future so that we can make multiple calls to get().
    Answer the following questions:
    a) Create the following shared future by calling the appropriate constructor:
    • Default instance.
    • As a shared future that shares the same state as another shared state.
    • Transfer shared state from a ‘normal’ future to a shared future.
    • Transfer shared state from a shared future to a shared future.
    b) Check the member functions from std::future that they are also applicable to
    std::shared_future.
    c) Test what happens when you call get() twice on a shared future.
    d) Create a shared future that waits for an infinite loop to finish (which it never does). To this end, use
    wait_for and wait_until to trigger a time out.
*/

#include <iostream>
#include <future>
#include <thread>

int testFunc(int a)
{
    return a+1;
}

int main() {
    /// a) Create the following shared future by calling the appropriate constructor:
    /// • Default instance.
    std::shared_future<int> sf1;
    
    /// • As a shared future that shares the same state as another shared state.
    std::shared_future<int> sf2(std::async(testFunc, 3));
    std::shared_future<int> sf3(sf2);

    /// • Transfer shared state from a ‘normal’ future to a shared future.
    std::future<int> fut = std::async(testFunc, 1);
    // the share() of std::future transfer the shared state of *this to a std::shared_future object
    std::shared_future<int> sf4 = fut.share(); // move assignment, fut now becomes invalid, valid() == false

    /// • Transfer shared state from a shared future to a shared future.
    // since a shared future allows multiple threads to wait for the same shared state, it is copyable (while std::future is only moveable)
    // Therefore to transfer shared state of a shared future we use std::move to do move assignment
    std::shared_future<int> sf5 = std::move(sf4); 

    /// b) Check the member functions from std::future that they are also applicable to std::shared_future.
    std::cout << std::boolalpha;
    std::cout << "is shared future valid (before): " << sf5.valid() << '\n'; //true
    sf5.wait();
    std::cout << "shared future value: " << sf5.get() << '\n';
    std::cout << "is shared future valid (after): " << sf5.valid() << '\n'; //true, we can repeatedly get()

    /// c) Test what happens when you call get() twice on a shared future.
    std::cout << "shared future value (again): " << sf5.get() << '\n';
    // It is ok and we can process the outcome of a concurrent computation more than once by using shared futures

    /// d) Create a shared future that waits for an infinite loop to finish (which it never does). To this end, use
    /// wait_for and wait_until to trigger a time out.
    std::shared_future<int> future = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        return 8;
        });

    std::cout << "waiting...\n";
    std::future_status status;
    do {
        // use wait_for or wait_until to let the future_status become std::future_status::timeout
        status = future.wait_for(std::chrono::seconds(1));
        //status = future.wait_until(std::chrono::steady_clock::now()+std::chrono::seconds(1));
        switch (status) {
        case std::future_status::deferred: std::cout << "deferred\n"; break;
        case std::future_status::timeout: std::cout << "timeout\n"; break;
        case std::future_status::ready: std::cout << "ready!\n"; break;
        }
    } while (status != std::future_status::ready);

    std::cout << "result is " << future.get() << '\n';

}