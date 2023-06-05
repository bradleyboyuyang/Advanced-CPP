/*
    Level 2.7: C++ System Error
    Problem 4: Error Code Fundamentals

    Name: Boyu Yang

    Problem objective:
    a) Create a default error code and an error code with a platform-dependent error code value and an error category.
    b) Create a function that returns the following information pertaining to instances of std::error_code:
    • Its error code (an integer).
    • Its message (a string).
    • The name of its category (a string).
    The return type is std::tuple < std::string, int, std::string> .
    c) Test equality/inequality of instances of std::error_code and std::error_condition using operators == and !=.
*/

#include <iostream>
#include <tuple>

/// Part (B) Create a function that returns error code, message, category name of std::error_code
std::tuple<std::string, int, std::string> errCodeMsg(std::error_code err_code) {
    // error code
    int code = err_code.value();
    // error message
    std::string msg = err_code.message();
    // error category name
    std::string cat_name = err_code.category().name();
    return std::make_tuple(msg, code, cat_name);
}



int main() {

    /// Part (A) Create a default error code and an error code with a platform-dependent error code value and an error category.
    // default error code
    std::error_code erc1;
    std::cout << "Default error message: " << erc1.message() << std::endl;
    // error code with platform-dependent error code value and error category
    std::error_code erc2(3, std::generic_category());
    std::cout << "Error message with code 3: " << erc2.message() << std::endl;


    /// Part (B) Create a function that returns error code, message, category name of std::error_code
    auto err_info = errCodeMsg(erc1);
    std::cout << std::get<0>(err_info) << ", " << std::get<1>(err_info) << ", " << std::get<2>(err_info) << std::endl;
    auto err_info2 = errCodeMsg(erc2);
    std::cout << std::get<0>(err_info2) << ", " << std::get<1>(err_info2) << ", " << std::get<2>(err_info2) << std::endl;

    /// Part (C) Test equality/inequality of instances of std::error_code and std::error_condition using operators == and !=.
    std::error_code err_code(8, std::generic_category());
    std::error_condition err_cond(10, std::generic_category());
    std::cout << "err_code (8) == err_condition (10): " << std::boolalpha << (err_code == err_cond) << std::endl;
    std::cout << "err_code (8) != err_condition (10): " << std::boolalpha << (err_code != err_cond) << std::endl;
    std::cout << "err_code (8) != err_code (3): " << std::boolalpha << (err_code != erc2) << std::endl;

}