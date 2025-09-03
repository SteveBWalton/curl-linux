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
    std::unique_ptr<HttpSimple> httpToken (new HttpSimple("http://192.168.2.1:8080/CIA/General/BearerToken", NULL, "{\"param1\":\"value1\",\"param2\":\"value2\"}\n", false));

    if (httpToken->getResponseCode() == 200)
    {
        std::cout << "Success." << std::endl;
        std::cout << httpToken->getResponse() << std::endl;
    }
    else
    {
        std::cout << "Error.  ResponseCode = " << httpToken->getResponseCode() << std::endl;
    }

    // Create a http simple object for PartInfo.
    std::unique_ptr<HttpSimple> httpPartInfo (new HttpSimple("http://192.168.2.1:8080/CIA/Blades/PartInfo", "Authorization: Bearer code-here", "{\"param1\":\"value1\",\"param2\":\"value2\"}\n", true));

    if (httpPartInfo->getResponseCode() == 200)
    {
        std::cout << "Success." << std::endl;
        std::cout << httpPartInfo->getResponse() << std::endl;
    }
    else
    {
        std::cout << "Error.  ResponseCode = " << httpPartInfo->getResponseCode() << std::endl;
    }


    // Return success.
    std::cout << "Goodbye from curl-test." << std::endl;
    return 0;
}

