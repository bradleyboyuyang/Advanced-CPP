/*
    Level 2.7: C++ System Error
    Problem 2: std::error_condition Fundamentals

    Name: Boyu Yang

    Problem objective:
    a) Create instances of std::error_condition based on the following requirements:
    • Default constructor.
    • Value (stored error code) and error category.
    • Based on std::errc code.
    b) Create a function that returns the following information pertaining to instances of 
    std::error_condition:
    • Its error code (an integer).
    • Its message (a string).
    • The name of its category (a string).
    The return type is std::tuple < std::string, int, std::string>.
*/

#include <iostream>
#include <tuple>

/// Part (B) Create a function that returns the following information pertaining to instances of std::error_condition:
///    • Its error code(an integer).
///    • Its message(a string).
///    • The name of its category(a string).
std::tuple<std::string, int, std::string> errorInfo(std::error_condition err) {
    // get error code
    int errCode = err.value();
    // get message
    std::string errMsg = err.message();
    // get category name
    std::string errCat = err.category().name();
    return std::make_tuple(errMsg, errCode, errCat);
}


int main() {

    /// Part (A) Create instances of std::error_condition based on the following requirements:
    /// default constructor
    std::error_condition err_cond1;
    std::cout << "Default constructor error message: " << err_cond1.message() << std::endl;

    /// Value(stored error code) and error category
    std::error_condition err_cond2(3, std::generic_category());
    std::cout << "Value constructor error message: " << err_cond2.message() << std::endl;

    /// Based on std::errc code
    std::error_condition err_cond3(std::errc::not_enough_memory);
    std::cout << "std::errc constructor error message: " << err_cond3.message() << std::endl;

    /// Part (B) Create a function that returns the following information pertaining to instances of std::error_condition
    auto errInfo1 = errorInfo(err_cond1);
    std::cout << "Error message: " << std::get<0>(errInfo1) << ", ";
    std::cout << "Error code: " << std::get<1>(errInfo1) << ", "; 
    std::cout << "Error category name: " << std::get<2>(errInfo1) << std::endl;
    
    auto errInfo2 = errorInfo(err_cond2);
    std::cout << "Error message: " << std::get<0>(errInfo2) << ", ";
    std::cout << "Error code: " << std::get<1>(errInfo2) << ", ";
    std::cout << "Error category name: " << std::get<2>(errInfo2) << std::endl;

    auto errInfo3 = errorInfo(err_cond3);
    std::cout << "Error message: " << std::get<0>(errInfo3) << ", ";
    std::cout << "Error code: " << std::get<1>(errInfo3) << ", ";
    std::cout << "Error category name: " << std::get<2>(errInfo3) << std::endl;

}