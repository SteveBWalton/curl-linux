/// Implmentation for the Parallel class.
///@file parallel.cpp

// File Header.
#include "curl-test.h"

// System Headers.
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>       // unique_ptr

// Application Headers.
#include "http-simple.h"


/// Main entry point for the curl-test program,
int main
(
    int             argc,
    const char**    argv
)
{

    // Welcome message.
    std::cout << "Hello from curl-test." << std::endl;

    // Create a HttpSimple object.
    std::unique_ptr<HttpSimple> httpSimple (new HttpSimple());

    // Return success.
    std::cout << "Goodbye from curl-test." << std::endl;
    return 0;
}

