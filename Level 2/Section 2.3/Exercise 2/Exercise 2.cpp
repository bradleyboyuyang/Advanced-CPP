/*
    Level 2.2: Advanced Lambda Programming
    Problem 2: C++14: Using init Captures to move Objects into Closures

    Name: Boyu Yang

    Problem objective:
    This exercise is concerned with the issue of captured variables when working with lambda functions. In
    particular, copying objects into the closure can lead to performance hits and capture-by-reference can
    lead to dangling pointers. Furthermore, these two capture modes do not work with move-only objects (for
    example, std::unique_ptr or std::future). For this reason, we discuss the init capture syntax.
*/

#include <iostream>
#include <vector>
#include <array>
#include <functional>

int main()
{
    /// a) Modify this code using move semantics, that is the vector data is moved into the lambda function. Test 
    /// the new code, including the values in data after the code has run.
    int size = 4; double val = 2.71;
    std::vector<double> data(size, val);
    // change into move semantics
    auto fun = [data=std::move(data)]() mutable
    {
        for (std::size_t i = 0; i < data.size(); ++i)
        {
            data[i] = 3.14; std::cout << data[i] << ",";
        }
        std::cout << '\n';
    };
    fun();
    // Now the data has no elements since it's out of scope
    if (data.size() == 0)
        std::cout << "The data has disappeared!" << std::endl;


    /// b) Create the following code snippet:
    // C++14 init capture with local variables
    int x = 1'000'000; // This is a digit separator
    auto fun4 = [&r = x]()
    {
        r *= 2;
        std::cout << "\nr: " << r;
    };
    fun4();

    /// c) Migrate the following C++11 code that uses std::bind to emulate C++14 code that uses init capture
    // Emulating generalized lambda capture with C++11
    // The original fun3 wants to move assign the data2 and data3 to array and array2
    int size2 = 3; double val2 = 1.41;
    std::vector<double> data2(size2, val2);
    std::array<double, 3> data3 = { 1.2, 2.4, 4.7 };
    // use init capture with std::move to replace the std::bind
    auto fun3 = [array = std::move(data2), array2 = std::move(data3)]() mutable{
        for (std::size_t i = 0; i < array.size(); ++i)
        {
            array[i] = 3.14; std::cout << array[i] << "/";
        }
        std::cout << '\n';
        for (std::size_t i = 0; i < array2.size(); ++i)
        {
            array2[i] = 2.71; std::cout << array2[i] << "/";
        }
    };

    // We can check the data2 and data3 now become empty
    if (0 == data2.size() || 0 == data3.size())
    {
        std::cout << "\nDouble arrays have no elements, OK\n";
    }
    else
    {
        std::cout << "\n Ouch!\n";
        for (std::size_t i = 0; i < data2.size(); ++i)
        {
            std::cout << data2[i] << "^";
        }
        for (std::size_t i = 0; i < data3.size(); ++i)
        {
            std::cout << data3[i] << "^";
        }
    }

}


