/*
    Level 3.1: STL Algorithms I
    Problem 2: Compile-Time Vector Class

    Name: Boyu Yang

    File: Vector.hpp
    Description: compile-time vector class implementation
*/

#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

// I choose std::array<type, N> as the ADT
template<typename T, int N> class Vector {
private:
    std::array<T, N> data;
public:
    /// c) Implement the required constructors and operations
    Vector() {}; // default constructor
    // value constructor
    Vector(const T& val) : data({}) {
        data.fill(val);
    }
    Vector(const std::array<T, N>& arr) {
        for (int i = 0; i < N; i++) {
            data[i] = arr[i];
        }
    }
    // copy constructor
    Vector(const Vector& vec) : data(vec.data) {};

    // accessing elements using []
    T& operator[](int idx) { return this->data[idx]; };

    // addition
    Vector operator+(const Vector& vec) {
        Vector res(data); // call value constructor
        for (int i = 0; i < N; i++) {
            res[i] += vec.data[i];
        }
        return res;
    }
    // subtraction
    Vector operator-(const Vector& vec) {
        Vector res(data);
        for (int i = 0; i < N; i++) {
            res[i] -= vec.data[i];
        }
        return res;
    }
    // unary minus
    Vector operator-() {
        Vector res(data);
        for (int i = 0; i < N; i++) {
            res[i] = -res[i];
        }
        return res;
    }

    // friend function for printing vector
    friend std::ostream& operator<<(std::ostream& out, const Vector& vec) {
        out << "[";
        for (T t : vec.data) { std::cout << t << ","; };
        out << "]";
        return out;
    };

    // Friend function for scalar multiplication
    template <typename F>
    friend Vector operator* (const F& a, const Vector& pt) {
        Vector<T, N> res(pt.data);
        for (int i = 0; i < N; ++i) {
            // as F can be different then T, we need to convert it
            res[i] *= a;
        };
        return res;
    };

    // Modify all elements using std::function
    void modify(const std::function<T(T&)>& f) {
        for (int i = 0; i < N; i++) {
            data[i] = f(data[i]);
        }
    }
};



