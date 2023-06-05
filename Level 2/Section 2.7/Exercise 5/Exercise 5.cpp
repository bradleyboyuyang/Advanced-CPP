/*
    Level 2.7: C++ System Error
    Problem 5: Catch Exceptions

    Name: Boyu Yang

    Problem objective:
    This exercise entails that you may need to research and investigate C++11 libraries and functionality. The 
    objective of this exercise is to catch a (simulated) exception thrown when setting the exception mask of an 
    input file stream. 
    a) In the catch block use e.code() with std::io_errc::stream.
    b) If the comparison in a) is true, then:
    • Create an error code instance ec1 with e.code() as argument.
    • Create an error condition ec2 instance with ec1 as argument.
    • Print the properties value, message and error category of ec2.
    c) Test your code.

*/

#include <iostream>
#include <fstream>


int main() {

    std::ifstream file(std::string("DOESNOTEXIST.txt"));
    try
    {
        // exception mask of the file stream
        // In this case 1) logical error on I/O operation or 
        // 2) read/write error on I/O operation
        file.exceptions(file.failbit | file.badbit);
    }
    catch (const std::ios_base::failure& e)
    {
        /// Part (A) In the catch block use e.code() with std::io_errc::stream.
        /// Part (B) If the comparison in a) is true, then:
        //• Create an error code instance ec1 with e.code() as argument.
        //• Create an error condition ec2 instance with ec1 as argument.
        //• Print the properties value, messageand error category of ec2.
        /// Part (C) Test your code.
        if (e.code() == std::io_errc::stream) {
            std::error_code ec1(e.code());
            std::error_condition ec2(ec1.value(), ec1.category());
            std::cout << "error code: " << ec2.value() << std::endl;
            std::cout << "error message: " << ec2.message() << std::endl;
            std::cout << "error category: " << ec2.category().name() << std::endl;
            std::cout << "the error description:\n" << e.what();
        }
    }
    catch (...)
    {
        std::cout << "catch all\n";
    }

}