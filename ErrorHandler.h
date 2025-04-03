#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <memory>
#include <unordered_map>

class ErrorHandler {
protected:
    int error_code;
    std::string name;

public:
    ErrorHandler(int code, std::string err_name);
    virtual ~ErrorHandler();

    virtual void report_error() = 0;
    virtual void handle() = 0;
};

#endif // ERROR_HANDLER_H