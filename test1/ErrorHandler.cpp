#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(int code) : error_code(code), active(false) {}


void ErrorHandler::react_type(String type){
    if(type == "critical"){   
        pwm_stop(true); // Stop the PWM signal
        turn_relay(false); // Turn off the relay
        error_code = 2; // Set error code to 2 for critical low voltage
    } else if (type == "low_power"){
        limit_pwm(135); // Limit the PWM signal
        error_code = 1; // Set error code to 1 for low voltage or worming temperature
    } 
    else if (type == "normal"){
        pwm_stop(false); // Start the PWM signal
        error_code = 0; // Set error code to 0 for normal voltage or temperature
    }
}

