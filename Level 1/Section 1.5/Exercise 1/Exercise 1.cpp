#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <span>
#include <array>
#include <iomanip>

#include <boost/date_time.hpp>
#include <boost/asio.hpp>


// Recursive case to print tuple
template <typename Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& pack) {
        TuplePrinter<Tuple, N - 1>::print(pack);
        std::cout << std::get<N - 1>(pack) << std::endl;
    }
};

// specialization for the base case
template <typename Tuple> struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& pack) {
        std::cout << std::get<0>(pack) << std::endl;
    }

};

// another method to print tuple elements, require C++ 17
template <std::size_t index, typename... Args>
void printTuple(const std::tuple<Args...>& pack) {
    if constexpr (index < sizeof...(Args)) {
        std::cout << std::get<index>(pack) << std::endl;
        printTuple<index + 1>(pack);
    }
}

// function that compares elements of a tuple for some index
template<int index> struct TupleLess {
    template <typename Tuple>
    bool operator () (const Tuple& left, const Tuple& right) {
        return std::get<index>(left) < std::get<index>(right);
    }
};

// range based loop
void printSpanRange(const std::span<int>& span) {
    for (auto& element : span) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// iteration based loop
void printSpanIter(const std::span<int>& span) {
    for (auto it = span.begin(); it != span.end(); ++it)
    {
        std::cout << *it << " ";

    }
    std::cout << std::endl;
}

// index based loop
void printSpanIndex(const std::span<int>& span) {
    for (std::size_t i = 0; i < span.size(); ++i) {
        std::cout << span[i] << " ";
    }
    std::cout << std::endl;
}

// return first n elements of a span
std::span<int> firstNSpan (const std::span<int>& span, const int N) {
    return span.first(N);
}

// return last n elements of a span
std::span<int> lastNSpan (const std::span<int>& span, const int N) {
    return span.last(N);
}

// function that tests the std::subspan
void testSubSpan(const std::span<int>& span, const int start, const int end) {
    std::span<int> subSpan = span.subspan(start, end);
    printSpanRange(subSpan);
}


int main()
{
    /// Part (A) define a tuple that models attributes of a Person
    typedef std::tuple<std::string, std::string, boost::gregorian::date> Person; //name, address, birth date
    Person p1("Brad", "NY", boost::gregorian::date {2001, 5, 27});
    Person p2("Julia", "LA", boost::gregorian::date{ 2003, 8, 2 });
    Person p3("John", "LA", boost::gregorian::date{ 1999, 3, 7 });
    // modify the elements
    std::get<0>(p3) = std::string("Mary");
    std::get<1>(p3) = std::string("CA");
    std::get<2>(p3) = boost::gregorian::date( 2001, 3, 25 );

    /// Part (B) Create a function to print the elements of Person
    std::cout << "Print elements of Person: " << std::endl;

    const int N = std::tuple_size<decltype(p1)>::value;
    TuplePrinter<Person, N>::print(p1);
    printTuple<0>(p2);

    /// Part (C) Create a list/vector of Person and add some instances of Person to it
    std::vector<Person> collection;
    collection.push_back(p1);
    collection.push_back(p2);
    collection.push_back(p3);

    /// Part (D) write a function that sorts the list based on one of the elements
    // We give an example that sorts the Person collection based on the birth date
    std::cout << "Collections before sorting: " << std::endl;
    for (const auto& element : collection) {
        TuplePrinter<Person, N>::print(element);
    }
    // We use the self-defined comparator at a given index together with STL sort algorithm
    std::sort(collection.begin(), collection.end(), TupleLess<2>());

    std::cout << "Collections after sorting: " << std::endl;
    for (const auto& element : collection) {
        TuplePrinter<Person, N>::print(element);
    }

    /// Part (E) Create fixed-sized and variable-sized arrays and create span views of them 
    std::array<int, 5> fixedArr = { 1, 2, 3, 4, 5 };
    std::span<int> fixedSpan(fixedArr); // create a span view of the fixed-sized array

    std::array<int, 5> dynamicArr = { 5, 4, 3, 2, 1 };
    std::span<int> dynamicSpan(dynamicArr); // create a span view of the variable-sized array
    
    /// Are these views read only? Prove or disprove this question
    // std::span does not enforce read-only access to the underlying data. It allows both read and write operations. 
    // But we can restrict to read-only using const keyword


    /// Part (F) Create 3 print functions for spans using a) range-based for loops, b) iterators and c) indexing operator []
    std::cout << "Print span of fixed array and dynamic array: " << std::endl;
    // Range based loops
    printSpanRange(fixedSpan);
    printSpanRange(dynamicSpan);
    // Iterator based loops
    printSpanIter(fixedSpan);
    printSpanIter(dynamicSpan);
    // Index based loops
    printSpanIndex(fixedSpan);
    printSpanIndex(dynamicSpan);

    /// Part (G) Write functions to return the first and last N elements of a span
    std::cout << "Print first/last n elements of a span: " << std::endl;
    printSpanRange(firstNSpan(fixedSpan, 3));
    printSpanRange(lastNSpan(dynamicSpan, 3));


    /// Part (H) Write a function to test std::subspan
    std::cout << "Test functionalities of STL subspan: " << std::endl;
    testSubSpan(fixedSpan, 1, 3);
    testSubSpan(dynamicSpan, 1, 4);

    /// Part (I) Investigate and extend the following code to create "byte views of spans"
    std::cout << "Create byte views of spans: " << std::endl;

    // See the byte-level view of `data` array using std::as_bytes and std::span
    float data[1]{ 3.141592f }; // `data` is a float array
    // const_bytes is indeed a "byte view of span": std::span<const std::byte>, rather than the original float
    auto const const_bytes = std::as_bytes(std::span{ data }); // use a series of bytes to represent `data`
    // print as hexadecimal format
    for (auto const b : const_bytes)
    {
        std::cout << std::setw(2)
            << std::hex
            << std::uppercase
            << std::setfill('0')
            << std::to_integer<int>(b) << ' ';
    }
    //Another way (std::as_writable_bytes) is a C++ 20 way of "std::as_bytes"
    auto writable_bytes = std::as_writable_bytes(std::span{ data });
    for (auto& b : writable_bytes) {
        std::cout << std::setw(2)
            << std::hex
            << std::uppercase
            << std::setfill('0')
            << std::to_integer<int>(b) << ' ';
    }




}