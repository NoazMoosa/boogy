#include "ErrorHandler.h"


ErrorHandler::ErrorHandler(int code, std::string err_name) : error_code(code), name(err_name) {}

ErrorHandler::~ErrorHandler() {}

tur

virtual void report_error() = 0;
    virtual void handle() = 0;