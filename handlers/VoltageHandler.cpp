
# include "function.h"
# include "Arduino.h"
# include "Pins.h"
# include "ErrorHandler.h"
# include "VoltageHandler.h"


void VoltageHandler::report_error(int code) const {
    Serial.println(code);
    // sound(); 
}
    
void VoltageHandler::check(){
    voltageReading = analogRead(voltagePin); // 0-1023
    inputVoltage = (voltageReading / 1023.0) * 5.0*6.23;

    Serial.print("Voltage: ");
    Serial.println(inputVoltage);

    if (inputVoltage < threshold_shutdown) {
        ok_shutdown = true;
        
    }
    else if (inputVoltage < threshold_limit) {
        ok_limit = true;
    }
    else{ error_code = 0; 
        ok_shutdown = false;
        ok_limit = false;
    } 
}

void VoltageHandler::handle()  { 

    if (ok_shutdown && error_code!=2) {
        react_type("critical"); // React to the error condition 
        Serial.print("critical: ");
        //report_error(2); 
        error_code = 2; // Set error code to 2 for critical low voltage
    } else if (ok_limit && error_code==0) {
        react_type("low_power"); // React to the error condition 
        Serial.print("low_power: ");
        //report_error(1); 
        error_code = 1; // Set error code to 1 for low voltage
    } 

}