/// Implmentation for the HttpSimple class.
/// Class to represent a request to a http server.
///@file http-simple.cpp

// File Header.
#include "http-simple.h"

// System Headers.
#include <iostream> // cout() Remove this, debugging only.
#include <string>
#include <curl/curl.h>



// Callback function to add blocks of content to the response.
static size_t writeCallBack
(
    void*   contents,       // The new data to add to the response.
    size_t  size,           // The size of the new data.
    size_t  nmemb,          //
    void*   userPointer     // The pointer to the string to append the data to.
)
{
    ((std::string*)userPointer)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



// Class constructor.
// Initialise the specified number of threads.
HttpSimple::HttpSimple
(
    const char* urlAddress,     // Specifies the http or https address to send the request to.  Include the http or https at the start.
    const char* token,          // Specifies the authorization bearer token header to use or NULL.
    const char* postData,       // Specifies the POST data to include with the request.
    bool isGet                  // Specifies true to force the request to be a GET regardless of post data.
)
{
    // std::cout << "HttpSimple constructor." << std::endl;

    // The response from the server.
    _response = "";

    // Start a curl session.
    CURL* curl = curl_easy_init();
    if (curl)
    {
        // std::cout << "curl connected." << std::endl;

        // Define our custom headers.
        struct curl_slist* curlHeaders = NULL;

        // Add custom headers.
        curlHeaders = curl_slist_append(curlHeaders, "Content-Type: application/json");
        if (token != nullptr)
        {
            // curlHeaders = curl_slist_append(curlHeaders, "Authorization: Bearer code-here");
            curlHeaders = curl_slist_append(curlHeaders, token);
        }

        // Set the custom headers.
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

        // Set the target url.
        curl_easy_setopt(curl, CURLOPT_URL, urlAddress);

        // Add the callback function.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_response);

        // This skips the verification of the server certificate (https).
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        // This skips the host name check (https).
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // This adds POST data and turns the request into a POST.
        // A strlen is used to get the size unless CURLOPT_POSTFIELDSIZE is used.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

        // Override the POST implied by CURLOPT_POSTFIELDS.
        if (isGet)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        }

        // Set the timeout to 60 seconds.
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);

        // Send the request.
        // std::cout << "Send Request." << std::endl;
        _responseCode = 0;
        CURLcode curlCode = curl_easy_perform(curl);

        // Check the result of the request.  CURLE_OK is zero and this represents success.
        switch (curlCode)
        {
        case CURLE_OK: // Success (0).
            // This only means that the server replied.
            // The server could reply with an error message.

            // Get the response code.
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &_responseCode);

            // Show the html response code.
            // std::cout << "Http Response Code " << _responseCode << std::endl;

            break;

        case CURLE_OPERATION_TIMEDOUT: // Timeout (??).
            std::cout << "Http request timed out." << std::endl;
            break;

        case CURLE_COULDNT_CONNECT: // No connection (7).
            std::cout << "Could not connect to server." << std::endl;
            break;

        default: // Unknown error.
            std::cout << "Error code " << curlCode << std::endl;
            break;
        }

        // Close the curl connection.
        curl_easy_cleanup(curl);
        curl = nullptr;
    }
    else
    {
        // Curl did not start.
    }
}



// Class destructor.
// Close all the threads.
HttpSimple::~HttpSimple()
{
    // std::cout << "HttpSimple destructor." << std::endl;
}



// The response from the html server.
std::string HttpSimple::getResponse()
{
    return _response;
}



// The response code from the html server.  200 is success.
long HttpSimple::getResponseCode()
{
    return _responseCode;
}
