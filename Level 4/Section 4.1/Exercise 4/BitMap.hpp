/*
    Level 3.1: STL Algorithms I
    Problem 4: A Bitmap Class

    Name: Boyu Yang
    File: Matrix.hpp
    Description: Compile-time matrix class implementation
*/

#pragma once
#include <array>
#include <iostream>
#include <functional>


template <typename T, int NR, int NC>
class Matrix {
private:
    using NestedMatrix = std::array<std::array<T, NC>, NR>;
    NestedMatrix data;
public:
    // default constructor, set all value to zero
    Matrix() {
        for (auto& row : data)
            for (auto& element : row)
                element = 0;
    }
    // value constructor
    Matrix(T value) {
        for (std::array<T, NC>& row : data) {
            for (T& elem : row) {
                elem = value;
            }
        }
    }
    // copy constructor
    Matrix(const Matrix& copy) {
        for (int i{ 0 }; i < NR; ++i) {
            for (int j{ 0 }; j < NC; ++j) {
                this->data[i][j] = copy.data[i][j];
            }
        }
    }
    // access row
    std::array<T, NC> operator()(int row) {
        return data[row];
    }
    // addition
    Matrix operator+(Matrix& other) {
        Matrix res(other);
        for (int i = 0; i < NR; i++)
            for (int j = 0; j < NC; j++)
                res(i, j) += data[i][j]; // we have defined the accessing element operator
        return res;
    }
    // subtraction
    Matrix operator-(Matrix& other) {
        Matrix res(other);
        for (int i = 0; i < NR; i++)
            for (int j = 0; j < NC; j++)
                res(i, j) -= data[i][j];
        return res;
    }
    // unary minus
    Matrix operator-() {
        Matrix res(*this);
        for (int i = 0; i < NR; i++)
            for (int j = 0; j < NC; j++)
                res(i, j) = -res(i, j);
        return res;
    }
    // premultiplication by a scalar
    template <typename F>
    friend Matrix operator*(const F& a, Matrix& pt) {
        Matrix res(pt); // note: res is a matrix, res.data is the 2d array
        for (auto& row : res.data)
            for (auto& element : row)
                element *= a;
        return res;
    }
    // Modify all elements using std::function
    void modify(const std::function<T(T&)>& f) {
        for (auto& row : data)
            for (auto& element : row)
                element = f(element);
    }
    // function to print the matrix
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
        out << "[";
        for (int i{ 0 }; i < NR; ++i) {
            if (i != 0) { out << " "; };
            out << "[ ";
            for (int j{ 0 }; j < NC; ++j) {
                std::cout << matrix.data[i][j] << " ";
            }
            out << "]";
            if (i != NR - 1) { out << std::endl; };
        }
        out << "]";
        return out;
    };
};

