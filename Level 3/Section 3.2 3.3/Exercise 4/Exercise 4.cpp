/*
    Level 3.2 3.3: C++ Concurrency
    Problem 4: My First Master-Worker Pattern in C++11

    Name: Boyu Yang

    Problem objective:
    create a simple application consisting of one master and one worker. The worker is
    responsible for the updating of a shared resource (in this case, a string) on behalf of the master. Some
    hints on the design of this exercise are:
    • The master initiates the computation and sets up the problem.
    • Then the master creates a bag of tasks (in our case just one worker).
    • The master waits until the job is done, consumes the results and then shuts down.
    Answer the following questions:
    a) We start with the following global data that is needed in order to implement this pattern:
    1: The resource that the worker updates.
    2: A mutex to synchronise access to the resource.
    3: A condition variable for thread notification.
    4: Two atomic Booleans to model the status of the master and worker.
    b) Create the thread function: it updates the resource by acquiring the lock, waiting on the worker ready
    flag to be set, updating the resource and then finally notifying the master.
    c) Create the code that implements the master’s duties. Test the code.
    d) We now replace atomic Booleans by class std::atomic_flag which is a bare-bones lock-free data
    type. It does not provide load nor store operations. It has functions to set and clear. Modify the code
    accordingly and test again.
*/

#include <thread>
#include <iostream>
#include <random>
#include <functional>
#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>

/// a) We start with the following global data that is needed in order to implement this pattern:
/// 1 : The resource that the worker updates.
/// 2 : A mutex to synchronise access to the resource.
/// 3 : A condition variable for thread notification.
/// 4 : Two atomic Booleans to model the status of the master and worker.
// Data Structures 
std::string data;// Shared data between master and worker
std::mutex m; // Ensures no race condition
// Synchronisation between master and worker
std::condition_variable cv;
// Initial state of worker and master
std::atomic<bool> workerReady = false;
std::atomic<bool> masterReady = false;


/// b) Create the thread function: it updates the resource by acquiring the lock, waiting on the worker ready 
/// flag to be set, updating the resourceand then finally notifying the master.
// WorkerThread function
void WorkerThread()
{
    std::cout << "Worker is called...\n";
    // False state: wait until master sends data
    std::unique_lock<std::mutex> myLock(m);
    cv.wait(myLock, [] { return workerReady.load(); }); // atomically load the value
    // Now in True state
    std::cout << "Worker is processing data\n";
    data += "addition from worker";
    // Notify master
    masterReady.store(true); // atomically replace the boolean value
    // Postprocess
    cv.notify_one();
    std::cout << "Worker is exited...\n";
}

/// c) Create the code that implements the master’s duties. Test the code
void masterThread() {
    // simple master/worker pattern: two threads operating on a shared resource "data"
    std::cout << "Master is called...\n";
    data = "Master data"; // shared source

    // the main thread will be master and we create a separate thread for worker
    std::thread worker(WorkerThread);

    // transition into true state
    std::unique_lock<std::mutex> myLock(m);
    workerReady.store(true); // atomically replace the boolean value
    std::cout << "Master has notified worker, wait for response...\n";
    cv.notify_one();
    cv.wait(myLock, [] {return masterReady.load(); }); // atomically load the value

    std::cout << "Master back again...\n";
    worker.join();
}


/// d) We now replace atomic Booleans by class std::atomic_flag 
std::atomic_flag workerReady2 = ATOMIC_FLAG_INIT;  // Initial state of the worker
std::atomic_flag masterReady2 = ATOMIC_FLAG_INIT;  // Initial state of the master

void workerThread2()
{
    std::cout << "Worker is called...\n";
    // False state: wait until master sends data
    std::unique_lock<std::mutex> myLock(m);
    cv.wait(myLock, [] { return workerReady2.test_and_set(); }); // atomically set the flag again
    // Now in True state
    std::cout << "Worker is processing data\n";
    data += "addition from worker";
    // Notify master
    masterReady2.clear(); // atomically clear the flag
    // Postprocess
    cv.notify_one();
    std::cout << "Worker is exited...\n";
}

void masterThread2()
{
    // simple master/worker pattern: two threads operating on a shared resource "data"
    std::cout << "Master is called...\n";
    data = "Master data"; // shared source

    // the main thread will be master and we create a separate thread for worker
    std::thread worker(WorkerThread);

    // transition into true state
    std::unique_lock<std::mutex> myLock(m);
    workerReady2.clear(); // atomically clear the flag
    std::cout << "Master has notified worker, wait for response...\n";
    cv.notify_one();
    cv.wait(myLock, [] {return masterReady2.test_and_set(); }); // atomically set the flag again

    std::cout << "Master back again...\n";
    worker.join();
}


int main() {
    /// c) Create the code that implements the master's duties. Test the code
    std::cout << "=======Use atomic boolean======= \n";
    masterThread();


    /// d) We now replace atomic Booleans by class std::atomic_flag 
    std::cout << "=======Use std::atomic_flag======= \n";
    masterThread2();
}
