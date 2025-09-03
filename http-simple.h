/// Definitions for the HttpSimple class.
///@file http-simple.h

#pragma once

// System Headers.
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>



// Class to represent a request to http server.
class HttpSimple
{
public:
    HttpSimple();
    ~HttpSimple();
};
