/// Implmentation for the HttpSimple class.
/// Class to represent a request to a http server.
///@file http-simple.cpp

// File Header.
#include "http-simple.h"

// System Headers.
#include <iostream> // cout() Remove this, debugging only.


// Class constructor.
// Initialise the specified number of threads.
HttpSimple::HttpSimple()
{
    std::cout << "HttpSimple constructor." << std::endl;
}



// Class destructor.
// Close all the threads.
HttpSimple::~HttpSimple()
{
    // Wait for all threads to stop.
    std::cout << "HttpSimple destructor." << std::endl;
}
