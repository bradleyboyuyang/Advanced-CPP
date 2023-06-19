/*
    Level 3.4: C++11 Tasks
    Problem 4: Packaged Tasks

    Name: Boyu Yang

    Problem objective:
    The added value of using a packaged task is that we can create a background task without starting it
    immediately. In particular, the task is typically started in a separate thread.
*/

#include <iostream>
#include <future>
#include <memory>
#include <random>
#include <thread>
#include <queue>

/// a) Consider the thread function. Write code to start a task.
// Thread function
double compute(double x, double y)
{
    // Wait a while
    std::default_random_engine dre(42);
    std::uniform_int_distribution<int> delay(0, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));
    return std::cos(x) * std::exp(y);
}

int main() {
    /// a) Consider the thread function. Write code to start a task.
    std::cout << "======Part(A)======\n";
    double x = 0.0; double y = 2.71;
    // A. 'Direct' tasks
    std::future<double> fut = std::async(compute, x, y);
    // Get the shared data
    double result = fut.get();
    std::cout << "Result: " << result << '\n';

    /// b) Rewrite / port the code in order to use a packaged task and delayed execution.
    std::cout << "======Part(B)======\n";
    // create a task and its future
    std::packaged_task<double(double, double)> compute_task(&compute);
    std::cout << "starting task\n";
    std::future<double> res = compute_task.get_future();

    // create a separate thread to execute compute_task
    // we must use std::move here to transfer ownership of the packaged_task into std::thread,
    // because std::thread requires a callable object and then takes ownership of the callable provided to it.
    std::thread t{ std::move(compute_task), x, y};
    std::cout << "waiting for task to finish..." << std::endl;
    std::cout << res.get() << '\n';
    std::cout << "task complete\n";
    t.join();

    // or we can simply compute_task(x, y)
    //compute_task(x, y); // start the task
    //std::cout << res.get() << std::endl; // wait for task to end and process result

    /// c) Create a queue of packaged tasks, dequeue each task and execute it.
    std::cout << "======Part(C)======\n";
    std::queue<std::packaged_task<double(double, double)>> package_queue;
    // Enqueue 10 packaged_task
    for (int i = 0; i < 10; i++) {
        std::packaged_task<double(double, double)> pack_task(&compute);
        package_queue.push(std::move(pack_task));
    }
    // Dequeue each task
    for (int i = 0; i < 10; i++) {
        // get the task and future
        auto pack_task = std::move(package_queue.front()); // still, use std::move since packaged_task is only moveable
        auto pack_fut = pack_task.get_future(); 
        // execute the task
        pack_task(x, y);
        std::cout << pack_fut.get() << std::endl; // wait for task to end and process result
        package_queue.pop();
    }

}