#pragma once
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "function.h"
#include <Arduino.h> 
#include "Pins.h"

class ErrorHandler {
protected:
    volatile int error_code = 0;
    volatile bool active ;
public:
ErrorHandler(int code); // Constructor to initialize the error code
    virtual void check() = 0; // Check if the error condition is met
    virtual void report_error() const = 0;
    virtual void handle() = 0;

    
    void react_type(String type); // React to the error type
    bool is_active() const { return active; }
    int get_error_code() const { return error_code; } // Get the error code

    virtual ~ErrorHandler()= default;
};

#endif // ERROR_HANDLER_H