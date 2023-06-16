/*
    Level 3.1: Threads
    Problem 3: Safe Locking

    Name: Boyu Yang

    Problem objective:
    We continue with the code in exercise 2 by using two special lock mechanisms:
    a) Modify the code in exercise 2 to let it work with std::lock_guard. Create a function that increments
    a counter by multiple threads. Check the output.
    b) We now test the functionality of std::unique_lock. In particular, you should investigate its
    interface (for example, www.cpppreference.com) in order to answer the questions in the rest of this exercise.
    c) Lock an associated mutex without locking using std::unique_lock::try_lock. Take care of
    exceptions such as i) no associated mutex and ii) mutex is already locked. You need to use
    std::system::error_code and std::errc as discussed in section 2.7 of the course.
    d) Apply std::unique_lock::try_lock_for that tries to lock a mutex that blocks until a specific
    timeout duration has elapsed or the lock has been acquired. As in part c) you need to catch system errors.
    e) Apply std::unique_lock::unlock that unlocks the associated mutex and releases ownership. As in
    parts c) and d) you need to catch system errors.
    f) Apply std::unique_lock::try_lock_until that tries to lock a mutex that blocks until a specific
    time has been reached or the lock has been acquired. As in parts c), d) and e) you need to catch system errors.
    g) Show how to release an associated mutex without unlocking it.
*/

#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include <system_error>

/// a) Modify the code in exercise 2 to let it work with std::lock_guard. Create a function that increments a counter by multiple threads.
// create mutex
std::mutex m_mutex;
int counter = 0; // a counter

// function that uses the std::lock_guard
void Iprint(const std::string& s, const int& count) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (int i = 0; i < count; i++)
        std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
    counter++; // increase the counter
}

/// b) c) Lock an associated mutex without locking using std::unique_lock::try_lock.
// create mutex
std::mutex m_mutex2;
void Iprint2(const std::string& s, const int& count) {
    std::unique_lock<std::mutex> uniLock(m_mutex2, std::defer_lock);
    try {
        // continuously trying to acquire the lock
        while (true) {
            if (uniLock.try_lock()) { // try to acquire the ownership of the mutex 
                for (int i = 0; i < count; i++)
                    std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
                /// e) Apply std::unique_lock::unlock that unlocks the associated mutex
                // this fulfills the requirement but actually don't need since ownership will be automatically released
                uniLock.unlock();

                break;
            }
        }
    }
    catch (const std::system_error& e) {
        // no associated mutex
        if (e.code() == std::errc::operation_not_permitted) {
            std::cout << "no associated mutex" << std::endl;
        }
        // mutex already locked
        if (e.code() == std::errc::resource_deadlock_would_occur) {
            std::cout << "mutex already locked" << std::endl;
        }

    }
    catch (...) {
        std::cout << "other exceptions" << std::endl;
    }
}

/// d) Apply std::unique_lock::try_lock_for that tries to lock a mutex that blocks until a specific timeout duration has elapsed or the lock has been acquired
// use a timed mutex to achieve the functionality of "try lock for a certain time amount"
std::timed_mutex timed_mutex;
// lock a mutex that blocks until a specific timeout duration has passed
void Iprint3(const std::string& s, const int& count) {
    std::unique_lock<std::timed_mutex> timed_lock(timed_mutex, std::defer_lock);
    // the remaining part similar except for 
    try {
        // trying to acquire the lock for 1 second
        // In fact, we can also use while true to continuously try to acquire the lock. But for small examples,
        // 1 second is fair enough for all the threads to get the lock and finish execution.
        if (timed_lock.try_lock_for(std::chrono::seconds(1))) { // try to acquire the ownership of the mutex 
            for (int i = 0; i < count; i++)
                std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
            /// e) Apply std::unique_lock::unlock that unlocks the associated mutex
            // this fulfills the requirement but actually don't need since ownership will be automatically released
            timed_lock.unlock();
        }
    }
    catch (const std::system_error& e) {
        // no associated mutex
        if (e.code() == std::errc::operation_not_permitted) {
            std::cout << "no associated mutex" << std::endl;
        }
        // mutex already locked
        if (e.code() == std::errc::resource_deadlock_would_occur) {
            std::cout << "mutex already locked" << std::endl;
        }

    }
    catch (...) {
        std::cout << "other exceptions" << std::endl;
    }
}

/// f) Apply std::unique_lock::try_lock_until that tries to lock a mutex that blocks until a specific time has been reached
void Iprint4(const std::string& s, const int& count) {
    std::unique_lock<std::timed_mutex> timed_lock(timed_mutex, std::defer_lock);
    // the remaining part similar except for 
    try {
        // trying to acquire the lock until 1 second later from now
        // Similarly, we do not use while loop since 1 second is enough for all threads to finish
        auto now = std::chrono::system_clock::now();
        if (timed_lock.try_lock_until(now+std::chrono::seconds(1))) { 
            for (int i = 0; i < count; i++)
                std::cout << "Thread " << std::this_thread::get_id() << ": " << s << std::endl;
            /// e) Apply std::unique_lock::unlock that unlocks the associated mutex
            // this fulfills the requirement but actually don't need since ownership will be automatically released
            timed_lock.unlock();
        }
    }
    catch (const std::system_error& e) {
        // no associated mutex
        if (e.code() == std::errc::operation_not_permitted) {
            std::cout << "no associated mutex" << std::endl;
        }
        // mutex already locked
        if (e.code() == std::errc::resource_deadlock_would_occur) {
            std::cout << "mutex already locked" << std::endl;
        }

    }
    catch (...) {
        std::cout << "other exceptions" << std::endl;
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
    /// a) Modify the code in exercise 2 to let it work with std::lock_guard.
    // mark the start time
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    // create threads for some callable objects
    auto lambda1 = []() {Iprint("lock test 1", 3); };
    std::thread t1a{ lambda1 };
    std::thread t2a{ lambda1 };
    std::thread t3a{ lambda1 };
    join(t1a);
    join(t2a);
    join(t3a);
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time (a): " << duration.count() << "s" << std::endl;
    std::cout << "Counter output (a): " << counter << std::endl;


    /// b) c) Lock an associated mutex without locking using std::unique_lock::try_lock. 
    // mark the start time
    start = std::chrono::system_clock::now();
    auto lambda2 = []() {Iprint2("lock test 2", 3); };
    std::thread t1b{ lambda2 };
    std::thread t2b{ lambda2 };
    std::thread t3b{ lambda2 };
    join(t1b);
    join(t2b);
    join(t3b);
    end = std::chrono::system_clock::now();
    duration = end - start;
    std::cout << "Elapsed time (c): " << duration.count() << "s" << std::endl;

    /// d) Apply std::unique_lock::try_lock_for that tries to lock a mutex that blocks until a specific timeout duration has elapsed or the lock has been acquired
    // mark the start time
    start = std::chrono::system_clock::now();
    auto lambda3 = []() {Iprint3("lock test 3", 3); };
    std::thread t1c{ lambda3 };
    std::thread t2c{ lambda3 };
    std::thread t3c{ lambda3 };
    join(t1c);
    join(t2c);
    join(t3c);
    end = std::chrono::system_clock::now();
    duration = end - start;
    std::cout << "Elapsed time (d): " << duration.count() << "s" << std::endl;

    /// e) Apply std::unique_lock::unlock that unlocks the associated mutex and releases ownership
    // As shown in code of c) and d), we add the unlock() in the function body to release ownership

    /// f) Apply std::unique_lock::try_lock_until that tries to lock a mutex that blocks until a specific time has been reached
    // mark the start time
    start = std::chrono::system_clock::now();
    auto lambda4 = []() {Iprint4("lock test 4", 3); };
    std::thread t1d{ lambda4 };
    std::thread t2d{ lambda4 };
    std::thread t3d{ lambda4 };
    join(t1d);
    join(t2d);
    join(t3d);
    end = std::chrono::system_clock::now();
    duration = end - start;
    std::cout << "Elapsed time (f): " << duration.count() << "s" << std::endl;

    /// g) Show how to release an associated mutex without unlocking it
    std::unique_lock<std::timed_mutex> lock(timed_mutex);
    lock.release();

}