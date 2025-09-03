/// Definitions for the HttpSimple class.
///@file http-simple.h

#pragma once

// System Headers.
#include <string>



// Class to represent a request to http server.
class HttpSimple
{
public:
    HttpSimple(const char*, const char*, const char*, bool);
    ~HttpSimple();

private:
    // The response from the html server.
    std::string _response;
    // The response code from the html server.  200 is success.
    long _responseCode;

public:
    // The response from the html server.
    std::string getResponse();
    // The response code from the html server.  200 is success.
    long getResponseCode();
};
