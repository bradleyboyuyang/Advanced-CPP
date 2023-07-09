/*
    Level 3.2: STL Algorithms II
    Problem 8: Classifying Algorithms

    Name: Boyu Yang

    Problem objective:
    File: StackADT.hpp
    Description: A simple realization of the required stack ADT

*/

#pragma once

#include <iostream>
#include <algorithm>
#include <stack>

class StackADT {
private:
    std::stack<int> stack;

public:
    // push operation
    void push(int value) {
        stack.push(value);
    }
    // pop operation
    // we rewrite the pop to return the top element while popping which makes it easy for other operations
    int pop() {
        int top = stack.top();
        stack.pop();
        return top;
    }

    // max: leave the larger of the two top values on the stack
    void max() {
        int top = pop();
        int secondTop = pop();
        push(std::max(top, secondTop));
    }
    // min: leave the lesser of the two top values on the stack
    void min() {
        int top = pop();
        int secondTop = pop();
        push(std::min(top, secondTop));
    }
    // over() : duplicates the second stack value on top of the stack
    void over() {
        int top = stack.top();
        stack.push(top);
    }
    // rot() : rotate the stack's third data value to the top of the stack
    void rot() {
        int thirdTop = pop();
        int secondTop = pop();
        int top = pop();
        push(secondTop);
        push(thirdTop);
        push(top);
    }
    // swap() : interchange the top two values on the stack
    void swap() {
        int top = pop();
        int secondTop = pop();
        push(top);
        push(secondTop);
    }
    // drop() : discard the value on the top of the stack
    void drop() {
        pop();
    }

    // print elements of the container
    void print(const std::string& comment) {
        std::cout << comment << ": ";
        auto copy{ stack };
        std::cout << "{";
        while (!copy.empty()) {
            std::cout << copy.top() << ", ";
            copy.pop();
        }; 
        std::cout << "}" << std::endl;
    }
};


