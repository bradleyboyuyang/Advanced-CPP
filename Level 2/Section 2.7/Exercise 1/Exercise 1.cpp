/*
    Level 2.7: C++ System Error
    Problem 1: Boost and C++11 Error Condition

    Name: Boyu Yang

    Problem objective:
    The objective of this exercise is to open a file by giving the location of the file as a string and using
    std::ifstream. Print each record in the file and then close it.
    Answer the following questions:
    a) Write the code and test it using an existing file as input. The return type is boost::system::error condition.
    b) We now need to check if the file exists. To this end, employ the function make_error_condition
    and the scoped enumeration errc.
    c) Test the code with an existing file and a non-existing file.
    d) Port the Boost code to C++11 and test your program again.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <boost/system/error_code.hpp>
#include <system_error>
#include <filesystem>
/// Part (A) Using an existing file as input, open file, print file, and close fild. The return type is boost::system::error condition.
boost::system::error_condition read(const std::string& file_name) {
    std::ifstream file(file_name.c_str()); // read file
    std::cout << "File content of " << file_name << ":\n";
    std::cout << file.rdbuf() << std::endl; // print file content
    file.close(); // close file
    return boost::system::error_condition();
}

/// Part (B) Check if the file exists. To this end, employ the function make_error_condition and the scoped enumeration errc.
boost::system::error_condition ReadFile(const std::string& file_name) {
    std::ifstream file(file_name.c_str());

    if (!file.is_open()) // check whether the file exists
        return boost::system::errc::make_error_condition(boost::system::errc::no_such_file_or_directory);
    std::cout << "File content of " << file_name << ":\n";
    std::cout << file.rdbuf() << std::endl; // print file content
    file.close(); // close file

    // return no error
    return boost::system::error_condition();
}

/// Part (D) Same as (B) but replace boost with STL implementations
std::error_condition stlReadFile(const std::string& file_name) {
    std::ifstream file(file_name.c_str());

    if (!file.is_open()) // check whether the file exists
        return std::make_error_condition(std::errc::no_such_file_or_directory);
    std::cout << "File content of " << file_name << ":\n";
    std::cout << file.rdbuf() << std::endl; // print file content
    file.close(); // close file

    // return no error
    return std::error_condition();
}

int main() {
    /// Part (A) Using an existing file as input, open file, print file, and close fild. The return type is boost::system::error condition.
    std::string file("1.txt");
    std::cout << "Opening file: " << file << std::endl;
    std::cout << "Error condition: " << read(file).message() << std::endl;

    /// Part (B) Check if the file exists. To this end, employ the function make_error_condition and the scoped enumeration errc.
    /// Part (C) Test the code with an existing file and a non-existing file.
    //std::filesystem::path absolutePath = std::filesystem::current_path(); // get absolute path
    //std::cout << "Absolute path: " << absolutePath << std::endl;
    //std::filesystem::path joinPath = absolutePath / "Exercise 1.cpp"; // concatenate path
    //std::cout << "file path: " << absolutePath << std::endl;
    //std::string file1(joinPath.string()); // convert filesystem::path to string object

    // existing file
    std::string file1("1.txt");
    std::cout << std::endl << "Opening file: " << file1 << std::endl;
    std::cout << "Error condition 1: " << ReadFile(file1).message() << std::endl;
    // non-existing file
    std::string file2("random_file.txt");
    std::cout << std::endl << "Opening file: " << file2 << std::endl;
    std::cout << "Error condition 2: " << ReadFile(file2).message() << std::endl;

    /// Part (D) Port the Boost code to C++11 and test your program again.
    std::string file1("1.txt");
    std::cout << std::endl << "Opening file: " << file1 << std::endl;
    std::cout << "Error condition 1: " << stlReadFile(file1).message() << std::endl;
    // non-existing file
    std::string file2("random_file.txt");
    std::cout << std::endl << "Opening file: " << file2 << std::endl;
    std::cout << "Error condition 2: " << stlReadFile(file2).message() << std::endl;
}