/*
    Level 3.4: C++11 Tasks
    Problem 6: Task Graphs: Implementation in C++11

    Name: Boyu Yang

    Problem objective:
    In this exercise we start from a high-level data dependency graph for a system to be developed and we
    map it to an implementation in C++11. The bodies of the functions can be anything you like while the data is also arbitrary.
    a) Write single-threaded code for this dependency graph. This will be the baseline code. Measure the
    processing time.
    b) Implement the graph using std::async and std::future.
    c) Implement the graph using promises.
    d) Implement the graph using packaged tasks.
    Experiment with various data types (built-in types, vectors and matrices) and functions
    (lightweight/heavyweight). Measure speedup and load balancing efforts.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <execution>

// we randomly design functions F1, F2, F3, F4
double F1(double a) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double b = a * a;
    return b;
}

double F2(double a) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double c = a * 2;
    return c;
}

double F3(double c) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    double d = c + 1;
    return d;
}

double F4(double b, double d) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    double f = b + d;
    return f;
}

// Simple function that measures processing time of a function
template <typename TFunc, typename... Args> void RunAndMeasure(const char* title, TFunc func, Args...args) {
    const auto start = std::chrono::steady_clock::now();
    auto ret = func(args...);
    const auto end = std::chrono::steady_clock::now();
    std::cout << title << ": " << std::chrono::duration<double, std::milli>(end - start).count() << " ms, res " << ret << std::endl;
}

/// a) Write single-threaded code for this dependency graph. This will be the baseline code. Measure the processing time.
// Task graph
// F1 and F2 in parallel; F3 depends on F2; 
// F4 depends on F1 and F3
double SequentialTaskGraph(double a)
{ // Single thread of control 
    double b = F1(a);
    double c = F2(a);
    double d = F3(c);
    double f = b + d;
    return f;
}

/// b) Implement the graph using std::async and std::future.
double ParallelTaskGraphI(double a)
{ // Parallel with futures
    std::future<double> b(std::async(F1, a));
    double c = F2(a);
    double d = F3(c);
    double f = b.get() + d; // use get() to retrieve the return value
    return f;
}

/// c) Implement the graph using promises.
double ParallelTaskGraphII(double a)
{ 
    // create a promise and its future
    std::promise<double> promise;
    std::future<double> b = promise.get_future();
    // create a separate thread function for F1() and store the value in the promise
    auto threadF1 = [&promise](double a) {promise.set_value(F1(a)); };
    std::thread t(threadF1, a);
    double c = F2(a);
    double d = F3(c);
    double f = b.get() + d;
    t.join(); // wait until the thread has finished
    return f;
}

/// d) Implement the graph using packaged tasks.
double ParallelTaskGraphIII(double a)
{
    // create a task associated with F1 and its future
    std::packaged_task<double(double)> pack_task(&F1);
    std::future<double> b = pack_task.get_future();
    pack_task(a); // execute the task
    double c = F2(a);
    double d = F3(c);
    double f = b.get() + d; // the get() function will wait for the packaged task to end and then process the result
    return f;
}

/// Create some heavyweight computation function for more test
// A function that computes within a vector
double HeavyComputation(double a, const std::vector<double>& data) {
    // Perform a computationally intensive task using the input data
    double result = a;
    for (const auto& value : data) {
        result += value * value;
    }
    return result;
}
// same as previous but replace F1() with a heavy computation function that will increase the load balancing effort
// use promises to implement
double ParallelTaskGraphWithPromises(double a, const std::vector<double>& data) {
    std::promise<double> promise;
    std::future<double> b = promise.get_future();
    // create a separate thread function for F1() and store the value in the promise
    std::thread t([&promise, a, data]() {
        double result = HeavyComputation(a, data);
        promise.set_value(result);
        });
    // Perform other computations
    double c = F2(a);
    double d = F3(c);
    double f = b.get() + d;
    t.join(); // wait for the thread to finish
    return f;
}
// same as previous but replace F1() with a heavy computation function that will increase the load balancing effort
// use packaged_task to implement
double ParallelTaskGraphWithPackagedTasks(double a, const std::vector<double>& data) {
    std::packaged_task<double()> pack_task([a, data]() {
        return HeavyComputation(a, data);
        });
    std::future<double> b = pack_task.get_future();
    std::thread t(std::move(pack_task)); // here we use thread to execute pack_task
    // Perform other computations
    double c = F2(a);
    double d = F3(c);
    double f = b.get() + d;
    t.join();
    return f;
}

int main() {
    /// Measure the time and experiment with various data types (built-in types, vectors and matrices) and functions
    /// (lightweight / heavyweight).Measure speedupand load balancing efforts.
    
    // Measure the time for double input/output with all the designed task graphs
    RunAndMeasure("Sequential task graph", SequentialTaskGraph, 13.4);
    RunAndMeasure("Parallel task graph I", ParallelTaskGraphI, 13.4);
    RunAndMeasure("Parallel task graph II", ParallelTaskGraphII, 13.4);
    RunAndMeasure("Parallel task graph III", ParallelTaskGraphIII, 13.4);
    // It can be seen that the parallel task graph is faster than sequential task graph.

    /// Experiment with vectors and heavyweight functions
    std::vector<double> data(100000000, 0.000001); // a very large vector therefore F1() now becomes heavyweight
    // We use variadic template so it can accept variadic number of parameters
    RunAndMeasure("Parallel heavy task graph with promises", ParallelTaskGraphWithPromises, 13.4, data);
    RunAndMeasure("Parallel heavy task graph with packaged tasks", ParallelTaskGraphWithPackagedTasks, 13.4, data);
    // We can see that if F1 is too computationally expensive then it increases the load balancing effort, the 
    // overall speedup outcome will be less significant.
}