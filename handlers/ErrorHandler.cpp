#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(int code) : error_code(code), active(false) {}


void ErrorHandler::react_type(String type){
    if(type == "critical"){   
        pwm_stop(); // Stop the PWM signal
        turn_relay(false); // Turn off the relay
    } else if (type == "low_power"){
        limit_pwm(); // Limit the PWM signal
    } 
}
