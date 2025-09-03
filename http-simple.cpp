/// Implmentation for the HttpSimple class.
/// Class to represent a request to a http server.
///@file http-simple.cpp

// File Header.
#include "http-simple.h"

// System Headers.
#include <iostream> // cout() Remove this, debugging only.
#include <curl/curl.h>

static size_t writeCallBack
(
    void*   contents,
    size_t  size,
    size_t  nmemb,
    void*   userPointer
)
{
    ((std::string*)userPointer)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



// Class constructor.
// Initialise the specified number of threads.
HttpSimple::HttpSimple()
{
    std::cout << "HttpSimple constructor." << std::endl;

    CURL* curl = curl_easy_init();
    if (curl)
    {
        std::cout << "curl connected." << std::endl;

        // Close the curl connection.
        curl_easy_cleanup(curl);
        curl = nullptr;
    }
}



// Class destructor.
// Close all the threads.
HttpSimple::~HttpSimple()
{
    std::cout << "HttpSimple destructor." << std::endl;
}
