/*
    Level 2.7: C++ System Error
    Problem 3: Portable Error Conditions corresponding to POSIX Error Codes

    Name: Boyu Yang

    Problem objective:
    a) Create error condition instances based on the following POSIX error codes (use scoped enumerator std::errc ):
    • io_error.
    • network_unreachable.
    • no_such_file_or_directory.
    • not_a_socket.
    • permission_denied.
    b) Create an std::error_condition object based on the value 128 and the generic error category.
    c) Use std::make_error_condition (with std::io_errc as argument) to create an instance of std::error_condition.
*/

#include <iostream>
#include <system_error>

int main() {

    /// Part (A) Create error condition instances based on the following POSIX error codes (use scoped enumerator std::errc ):
    //• io_error.
    //• network_unreachable.
    //• no_such_file_or_directory.
    //• not_a_socket.
    //• permission_denied.
    std::error_condition cond1(std::errc::io_error);
    std::cout << "io_error: " << cond1.message() << std::endl;
    std::error_condition cond2(std::errc::network_unreachable);
    std::cout << "network_unreachable: " << cond2.message() << std::endl;
    std::error_condition cond3(std::errc::no_such_file_or_directory);
    std::cout << "no_such_file_or_directory: " << cond3.message() << std::endl;
    std::error_condition cond4(std::errc::not_a_socket);
    std::cout << "not_a_socket: " << cond4.message() << std::endl;
    std::error_condition cond5(std::errc::permission_denied);
    std::cout << "permission_denied: " << cond5.message() << std::endl;


    /// Part (B) Create an std::error_condition object based on the value 128 and the generic error category
    std::error_condition cond6(128, std::generic_category());
    std::cout << "Error message of code 128: " << cond6.message() << std::endl; // not a socket

    /// Part (C) Use std::make_error_condition (with std::io_errc as argument) to create an instance of std::error_condition.
    std::error_condition cond7 = std::make_error_condition(std::io_errc::stream);
    std::cout << "io_errc error message: " << cond7.message() << std::endl; // io stream error

}