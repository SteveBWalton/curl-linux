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

    std::string readBuffer;

    CURL* curl = curl_easy_init();
    if (curl)
    {
        std::cout << "curl connected." << std::endl;

        // Define our custom headers.
        struct curl_slist* curlHeaders = NULL;

        // Add custom headers.
        curlHeaders = curl_slist_append(curlHeaders, "Content-Type: application/json");
        curlHeaders = curl_slist_append(curlHeaders, "Authorization: Bearer code-here");

        // Set the custom headers.
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

        // Set the target url.
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.2.1:8080/CIA/General/BearerToken");

        // Add the callback function.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // This skips the verification of the server certificate (https).
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        // This skips the host name check (https).
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // This adds POST data and turns the request into a POST.
        // A strlen is used to get the size unless CURLOPT_POSTFIELDSIZE is used.
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"param1\":\"value1\",\"param2\":\"value2\"}\n");

        // Override the POST implied by CURLOPT_POSTFIELDS.
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        // Send the request
        std::cout << "Send Request." << std::endl;
        CURLcode curlCode = curl_easy_perform(curl);
        std::cout << "Request Result " << curlCode << std::endl;

        // Display the read buffer.
        std::cout << readBuffer << std::endl;

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
