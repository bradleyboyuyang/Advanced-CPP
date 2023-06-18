/*
    Level 3.5: Complexity and STL Containers
    Problem 1: Synchronising Queue

    Name: Boyu Yang

    Problem objective:
    A priority queue is a collection of elements each of which having a priority value. When an element is
    chosen for deletion it is always the element with the highest priority. We thus see that a priority queue is
    not a queue (the latter being FIFO (First In First Out)). We can implement priority queues as:
    • A list ordered by priority values (highest priority element at the end of the list).
    • A simple unordered list (O (n) complexity in the worst case).
    • A heap (supported in STL) (insertion and deletion have logarithmic complexity).
    a) Create a priority queue whose elements are long long using the above default template parameters.
    In particular, perform the following:
    • Push values 66, 22, 44.
    • Print top element and the pop it.
    • Push values 11,22,33.
    • Pop element.
    • Iterate in the priority until it is empty:
    o Print top element.
    o Pop it.
    Inspect the output and convince yourself that is consistent with your expectations.
    b) Create a priority queue whose elements are long long whose container is std::deque and whose
    comparator is std::greater<long long>. Test this case with the data in part a) of the exercise. Inspect the output.
    c) Modify the code in part b) to use a lambda function instead of std::greater<long long>. Inspect the output
*/

#include <iostream>
#include <queue>

int main() {
    /// a) Create a priority queue whose elements are long long using the above default template parameters.
    std::cout << "========Part(A)========\n";
    std::priority_queue<long long> pQueue; // by default, larger values have higher priority
    // push values 66, 22, 44
    pQueue.push(66);
    pQueue.push(22);
    pQueue.push(44);
    // print top element and then pop it
    std::cout << "The top element: " << pQueue.top() << std::endl;
    pQueue.pop();
    // push values 11, 22, 33
    pQueue.push(11);
    pQueue.push(22);
    pQueue.push(33);
    // pop elements
    pQueue.pop();
    // iterate until it is empty: print top and pop it
    while (pQueue.size()) {
        std::cout << "The top element: " << pQueue.top() << std::endl;
        pQueue.pop();
    }
    /// Inspect the output and convince yourself that is consistent with your expectations.
    // The console output is 66, 33, 22, 22, 11
    // This is consistent, the larger values have higher priority, and hence 66 is first popped. The second time 44 is the second
    // largest and hence it is secondly popped but we do not print it. Then we continue popping and get 22, 22, 11 accordingly.
    
    /// b) Create a priority queue whose elements are long long whose container is std::deque and whose
    /// comparator is std::greater<long long>. Test this case with the data in part a) of the exercise. Inspect the output.
    std::cout << "========Part(B)========\n";
    std::priority_queue<long long, std::deque<long long>, std::greater<long long>> pQueue2;
    // push values 66, 22, 44
    pQueue2.push(66);
    pQueue2.push(22);
    pQueue2.push(44);
    // print top element and then pop it
    std::cout << "The top element: " << pQueue2.top() << std::endl;
    pQueue2.pop();
    // push values 11, 22, 33
    pQueue2.push(11);
    pQueue2.push(22);
    pQueue2.push(33);
    // pop elements
    pQueue2.pop();
    // iterate until it is empty: print top and pop it
    while (pQueue2.size()) {
        std::cout << "The top element: " << pQueue2.top() << std::endl;
        pQueue2.pop();
    }
    // The console output now becomes 22, 22, 33, 44, 66
    // This is because now smaller values have higher weight. Thus 22 is at the top and we pop it. Then we pop 11. Then we 
    // continue popping and get 22, 33, 44, 66.

    /// c) Modify the code in part b) to use a lambda function instead of std::greater<long long>. Inspect the output
    std::cout << "========Part(C)========\n";
    auto comparator = [](long long x, long long y) {return x > y; };
    // note: in C++20 we can simply write pQueue3 without "(comparator)"
    std::priority_queue<long long, std::deque<long long>, decltype(comparator)> pQueue3(comparator);
    // push values 66, 22, 44
    pQueue3.push(66);
    pQueue3.push(22);
    pQueue3.push(44);
    // print top element and then pop it
    std::cout << "The top element: " << pQueue3.top() << std::endl;
    pQueue3.pop();
    // push values 11, 22, 33
    pQueue3.push(11);
    pQueue3.push(22);
    pQueue3.push(33);
    // pop elements
    pQueue3.pop();
    // iterate until it is empty: print top and pop it
    while (pQueue3.size()) {
        std::cout << "The top element: " << pQueue3.top() << std::endl;
        pQueue3.pop();
    }
    // we get exactly the same output as exercise 2

}