/*
    Level 3.1: Threads
    Problem 2: Controlling Thread Execution: Synchronising Access to Shared Resources

    Name: Boyu Yang

    Problem objective:
    Moving on from exercise 1 we now synchronise access to the shared resource that is the console. In this
    exercise we use synchronising mechanisms to make the code thread-safe and hence avoid race conditions.
    In short, we use locking mechanisms to ensure that only one thread can access the console at one time.
    Answer the following questions:
    a) Use the std::mutex synchronisation to control access to the shared resource. Use lock() and
    unlock(). Measure processing time.
    b) Now use try_lock() and measure the number of times each thread has failed to acquire the lock.
    Again, measure processing time.
    c) Simulate deadlock (for example, a thread that never unlocks a mutex) by commenting out unlock()
    in your code. What happens?
*/

#include <thread>
#include <iostream>
#include <functional>
#include <mutex>

// create mutex
std::mutex m_mutex;

/// a) Use the std::mutex synchronisation to control access to the shared resource.
// same as exercise 1 but add mutex synchronization to control access
void Iprint(const std::string& s, const int& count) {
    m_mutex.lock();
    for (int i = 0; i < count; i++)
        std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
    m_mutex.unlock();
}

/// b) use try_lock() and measure the number of times each thread has failed to acquire a lock
void Iprint2(const std::string& s, const int& count, int& num) {
    // whether fail to acquire the lock
    while (true) {
        if (m_mutex.try_lock()) {
            for (int i = 0; i < count; i++)
                std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
            m_mutex.unlock();
            break;
        }
        else {
            num += 1; // increase the number of times that thread has failed to acquire the lock
        }
    }

}

// function to check whether a thread has completed and join it if yes
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
    /// a) Use the std::mutex synchronisation to control access to the shared resource. Use lock() and
    /// unlock(). Measure processing time.
    // mark the start time
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    // create threads for some callable objects
    auto lambda1 = []() {Iprint("lambda function", 3); };
    std::thread t1a{ lambda1 };
    std::thread t2a{ lambda1 };
    std::thread t3a{ lambda1 };
    join(t1a);
    join(t2a);
    join(t3a);
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time (a): " << duration.count() << "s" << std::endl;

    /// b) Now use try_lock() and measure the number of times each thread has failed to acquire the lock, measure processing time.
    // mark the start time
    start = std::chrono::system_clock::now();
    // measure the number of times each thread has failed to acquire the lock
    int thread1_count = 0;
    int thread2_count = 0;
    int thread3_count = 0;
    auto lambda2 = [](int& thread_count) {Iprint2("lambda function", 3, thread_count); };
    std::thread t1b{ lambda2, std::ref(thread1_count) };
    std::thread t2b{ lambda2, std::ref(thread2_count) };
    std::thread t3b{ lambda2, std::ref(thread3_count) };
    join(t1b);
    join(t2b);
    join(t3b);
    end = std::chrono::system_clock::now();
    duration = end - start;
    std::cout << "Elapsed time (b): " << duration.count() << "s" << std::endl;
    std::cout << "Number of times thread 1 has failed to acquire the lock: " << thread1_count << std::endl;
    std::cout << "Number of times thread 2 has failed to acquire the lock: " << thread2_count << std::endl;
    std::cout << "Number of times thread 3 has failed to acquire the lock: " << thread3_count << std::endl;

    // By comparing time with the previous exercise, the program takes longer to run when the threads are synchronized using mutex.
    // Also, the console output becomes tidier and cleaner because of the sequential execution of threads ensured by mutex.
    // Also, every execution the number of times each thread has failed to acquire the lock is different.

    /// c) Simulate deadlock (for example, a thread that never unlocks a mutex) by commenting out unlock()
    /// in your code. What happens ?
    // The program hangs because the thread that acquires the lock necer releases it, creating a deadlock and 
    // preventing other threads from getting the shared resouces.


}