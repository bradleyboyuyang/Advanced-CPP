/*
    Level 3.5: Complexity and STL Containers
    Problem 3: Forward List 101

    Name: Boyu Yang

    Problem objective:
    The C++11 std::forward_list is a container that supports fast insertion and removal of elements from
    anywhere in the container. Fast random access is not supported. It is implemented as a singly-linked list
    and essentially does not have any overhead compared to its implementation in C. Compared to
    std::list this container provides more space efficient storage when bidirectional iteration is not needed.
    This exercise entails investigating this new class.
    Answer the following questions:
    a) Create default list, a list with n elements and a given value, and a list that is built from an initialiser list
    (two forms).
    b) Forward lists have no member functions to give their size. Write you own function in terms of
    std::distance().
    c) Create code to insert values after a given position based on value, value and a count, two iterators and
    initialiser list. The code makes direct calls to std::forward_list::insert_after.
    d) Create functions to erase values after a given positon as well as in a range of iterators.
    e) Create examples to show how splice and merge functionality work.

*/

#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <forward_list>
#include <vector>

/// b) Forward lists have no member functions to give their size. Write you own function in terms of std::distance().
template <typename T>
int getSize(std::forward_list<T>& f) {
    return std::distance(f.begin(), f.end());
}


// simple code to print a forward list element
template<typename T>
std::ostream& operator<<(std::ostream& s, const std::forward_list<T>& v) {
    s.put('[');
    char comma[3] = { '\0', ' ', '\0' };
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']' << std::endl;
}

int main() {
    /// a) Create default list, a list with n elements and a given value, and a list that is built from an initialiser list
    /// (two forms).
    const std::size_t N = 5;
    std::forward_list<double> fList1(N, 3.14);
    std::forward_list<double> fList2{ 3.14, 3.14, 3.14, 3.14, 3.14 };


    /// b) Forward lists have no member functions to give their size. Write you own function in terms of std::distance().
    std::cout << "size of list 1: " << getSize<double>(fList1) << std::endl;
    std::cout << "size of list 2: " << getSize<double>(fList2) << std::endl;

    /// c) Create code to insert values after a given position based on value, value and a count, two iterators and
    /// initialiser list. The code makes direct calls to std::forward_list::insert_after.
    std::forward_list<std::string> words{ "I", "am", "happy" };
    std::cout << words;
    // insert based on value
    auto beginIt = words.begin();
    words.insert_after(++beginIt, "not");
    std::cout << words;
    // insert based on value and count
    words.insert_after(++beginIt, 2, "that");
    std::cout << words;
    // insert based on two iterators
    std::vector<std::string> V = { "apple", "banana", "cherry" };
    words.insert_after(words.begin(), V.begin(), V.end());
    std::cout << words;
    // insert based on initialiser list
    words.insert_after(words.begin(), { "another", "trial" });
    std::cout << words;

    /// d) Create functions to erase values after a given positon as well as in a range of iterators.
    std::forward_list<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    l.erase_after(l.before_begin()); // Removes first element, 1
    l.erase_after( l.begin() ); // remove second element, 3
    std::cout << l; // output [2, 4, 5, 6, 7, 8, 9]
    l.erase_after(++l.begin(), l.end()); // remove third element all the way to last
    std::cout << l; // output [2, 4]

    /// e) Create examples to show how splice and merge functionality work.
    // merge: merge two sorted lists into one
    std::forward_list<int> list1 = { 5, 9, 1, 3, 3 };
    std::forward_list<int> list2 = { 8, 7, 2, 3, 4, 4 };
    list1.sort();
    list2.sort();
    std::cout << "list1: " << list1;
    std::cout << "list2: " << list2;
    list1.merge(list2);
    std::cout << "merged:" << list1; // result: [1, 2, 3, 3, 3, 4, 4, 5, 7, 8, 9]

    // splice_after: move elements from another forward_list to *this
    std::forward_list<int> l1 = { 5, 9, 1, 3, 3 };
    std::forward_list<int> l2 = { 8, 7, 2, 3, 4, 4 };

    // Take care of difference between l1.begin() and l1.before_begin();
    // move all elements after the first position and before the end of l1 (which is [9,1,3,3]), to after the first position of l2
    l2.splice_after(l2.begin(), l1, l1.begin(), l1.end()); // l2: [8, 9, 1, 3, 3, 7, 2, 3, 4, 4]
           
    // only move one element after the first element of l1 (which is 9) after the first position of l2
    //l2.splice_after(l2.begin(), l1, l1.begin()); // l2: [8, 9, 7, 2, 3, 4, 4]
    
    // move all the elements in l1 after the first position of l2
    //l2.splice_after(l2.begin(), l1); // l2: [8, 5, 9, 1, 3, 3, 7, 2, 3, 4, 4]

    std::cout << "l1: " << l1 << "l2: " << l2;
}