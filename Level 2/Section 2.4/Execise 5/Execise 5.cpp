/*
    Level 2.2: Smart Pointers in Boost and C++
    Problem 5: Custom Deleter

    Name: Boyu Yang

    Problem objective:
    This exercise studies the "deleters" supported by shared pointers and unique pointers
    a) The goal of this exercise is to open a file, write some data to the file an then close it when we are
    finished writing. Under normal circumstances we are able to close the file. However, if an exception
    occurs before the file can be closed the file pointer will still be open and hence it cannot be accessed.
    In order to ensure exception safety we employ a shared pointer with a delete function in the
    constructor, for example by using a function object:
    std::shared_ptr<FILE> mySharedFile(myFile, FileFinalizer());
    where FileFinalizer is a function object.
    b) Create a free function and a stored lambda function that also play the role of custom deleters for this
    problem.
    c) Test the code for the three kinds of deleter functions (the delete closes the file).
    d) Create a small loop in which records are added to the file; throw an exception at some stage in the
    loop, catch the exception and then open the file again. Does it work?
*/

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <cstdio>

/// a) employ a shared pointer with a deleter as a function object
// function object as a deleter
struct FileFinalizer {
    void operator()(FILE* file) const {
        if (file) {
            fclose(file);
            printf("File closed.\n");
        }
    }
};

/// b) Create a free function and a stored lambda function that also play the role of custom deleters for this problem.
// free function as a deleter. 
// as required, the delete closes the file
void closeFile(FILE* file) {
    if (file) {
        fclose(file);
        printf("File closed.\n");
    }
}

// lambda function as a deleter
auto fileDeleter = [](FILE* file) {
    if (file) {
        fclose(file);
        printf("File closed.\n");
    }
};

int main() {
    /// c) Test the code for the three kinds of deleter functions (the delete closes the file).
    std::cout << "========Part (C) results========\n";
    try {
        FILE* myFile;
        fopen_s(&myFile, "1.txt", "w"); // open file and write mode
        // test the function object as deleter
        std::shared_ptr<FILE> mySharedFile(myFile, FileFinalizer());
        // test the free function as deleter
        std::shared_ptr<FILE> mySharedFile2(myFile, closeFile);
        // test the lambda function as deleter
        std::shared_ptr<FILE> mySharedFile23(myFile, fileDeleter);

        throw 1;
    }
    catch (const int err) {
        FILE* myFile2;
        fopen_s(&myFile2, "2.txt", "w");
        fclose(myFile2);
    }
    // Since we directly throw an error after creating the file pointers, there maybe dangling pointers 
    // as the file pointers go out of the try-catch scope. However as seen from the output, the deleter function is called
    // when the file pointer go out of scope and successfully closes the file.

    /// d) Create a small loop in which records are added to the file; throw an exception at some stage in the
    /// loop, catch the exceptionand then open the file again.Does it work ?
    std::cout << "========Part (D) results========\n";
    try {
        FILE* myFile3;
        fopen_s(&myFile3, "3.txt", "w");
        std::shared_ptr<FILE> mySharedFile(myFile3, closeFile);

        for (int i = 1; i <= 10; ++i) {
            fprintf(myFile3, "Record %d\n", i);

            // Throw an exception at some point in the middle
            if (i == 5)
                throw std::runtime_error("Exception occurred.");
        }
    }
    catch (const std::exception& e) {
        printf("Exception caught: %s\n", e.what());
        printf("Reopening the file...\n");

        FILE* myFile3;
        fopen_s(&myFile3, "3.txt", "a");  // Open the file in append mode
        std::shared_ptr<FILE> mySharedFile(myFile3, closeFile);

        // Continue writing to the file...

    }
    // We can see the delete function still works when we throw exception in the middle, catch it and continue to open the file.
}