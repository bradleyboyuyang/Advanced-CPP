#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

// C++ 98 approach
// Data storage types
template <typename T> struct Storage
{
    // Possible ADTs and their memory allocators
    // typedef std::vector<T, CustomAllocator<T>> type;
    // typedef std::vector<T, std::allocator<T>> type;
    typedef std::list<T, std::allocator<T>> type;
};


template <typename T>
class Client
{ // An example of Composition
private:
    typename Storage<T>::type data; // typename mandatory
public:
    Client(int n, const T& val) : data(n, val) {}
    void print() const
    {
        std::for_each(data.begin(), data.end(), [](const T& n)
            { std::cout << n << ","; });
        std::cout << '\n';
    }
};


/// Part (A) (re)Create the class using alias template instead of typedef.
template <typename T> 
using Type = std::list<T, std::allocator<T>>;

template <typename T> class ClientNew {
private:
    Type<T> data;
public:
    ClientNew(int n, const T& val) : data(n, val) {}
    void print() const
    {
        std::for_each(data.begin(), data.end(), [](const T& n)
            { std::cout << n << ","; });
        std::cout << '\n';
    }
};

int main()
{

    /// Part (B) Test your code. Do you get the same output as before?

    // Client of storage using typedef (C++ 98)
    int n = 10; int val = 2;
    Client<int> myClient(n, val); myClient.print();

    // Client of storage using alias template
    ClientNew<int> myClient2(n, val); myClient2.print();

    // Yes, we have the same output with much simpler code structure with C++ 11 `using`, rather than C++ 98 `typedef`。
}



