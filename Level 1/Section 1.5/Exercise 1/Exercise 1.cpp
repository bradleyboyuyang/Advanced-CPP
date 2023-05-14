#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <tuple>
#include <span>

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
    

    
    
    /// Are these views readonly? Prove or disprove this question
     

    
    /// Part (F) Create 3 print functions for spans using a) range-based for loops, b) iterators and c) indexing operator []



    /// Part (G) Write functions to return the first and last N elements of a span
    
    /// Part (H) Write a function to test std::subspan
    

    /// Part (I) Investigate and extend the following code to create “byte views of spans”
    // Bytes stuff
    //float data[1]{ 3.141592f };
    //auto const const_bytes = std::as_bytes(std::span{ data });
    //for (auto const b : const_bytes)
    //{
    //    std::cout << std::setw(2)
    //        << std::hex
    //        << std::uppercase
    //        << std::setfill('0')
    //        << std::to_integer<int>(b) << ' ';
    //}
    // Exx. test 
    //std::as_writable_bytes



}