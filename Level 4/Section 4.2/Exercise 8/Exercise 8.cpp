/*
    Level 3.2: STL Algorithms II
    Problem 8: Classifying Algorithms

    Name: Boyu Yang

    Problem objective:
    Consider a stack ADT (First-In-First-Out) and a selection of its operations:
    max(), min() : leaves on the stack the larger and lesser of the two top values, respectively.
    over() : duplicates the second stack value on top of the stack.
    rot() : rotate the stack's third data value to the top of the stack.
    swap() : interchange the top two values on the stack.
    drop() : discard the value on the top of the stack.
    If we consider these operations as simple algorithms, in which categories do they belong?
    Implement a simple version of this stack ADT showing how these operations work.

*/
#include "StackADT.hpp"

int main() {
    StackADT stack;
    for (int i = 0; i < 8; i++) {
        stack.push(i * i - 4 * i + 10);
    }
    // the leftmost is the top of the stack
    stack.print("original stack"); // 31, 22, 15, 10, 7, 6, 7, 10

    stack.max(); // since 22<35, remove 22
    stack.print("stack after max()"); // 31, 15, 10, 7, 6, 7, 10

    stack.min(); // since 31>15, remove 31
    stack.print("stack after min()"); // 15, 10, 7, 6, 7, 10

    stack.over(); // duplicate 15
    stack.print("stack after over()"); // 15, 15, 10, 7, 6, 7, 10

    stack.rot(); // the third element now on top
    stack.print("stack after rot()"); // 10, 15, 15, 7, 6, 7, 10

    stack.swap(); // swap the top and second top
    stack.print("stack after swap()"); // 15, 10, 15, 7, 6, 7, 10

    stack.drop(); // discard the top value on the stack
    stack.print("stack after drop()"); // 10, 15, 7, 6, 7, 10

    /// which algorithms do they belong to?
    // min, max, drop, over are modifying algorithms; rot and swap are mutating algorithms

    return 0;
}