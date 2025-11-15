
# include "function.h"
# include "Arduino.h"
# include "Pins.h"
# include "ErrorHandler.h"
# include "VoltageHandler.h"


void VoltageHandler::report_error() const {
    if(error_code!=0){ 
        //Serial.print("Voltage: ");
        //Serial.print(inputVoltage);
        //Serial.print("Error code: ");
        //Serial.println(error_code); // 3 ,1 is the audio track for voltage error
        player->playTrack(error_code); // Play error sound
    }
    
    // sound(); 
}
  
// read voltage and set flags shutdown and limit
void VoltageHandler::check(){
    voltageReading = analogRead(voltagePin); // 0-1023
    inputVoltage = (voltageReading / 1023.0) * 5.0*6.19; // 390kohm and 75k

    if (inputVoltage < threshold_shutdown) {
        ok_shutdown = true;
    }
    else if (inputVoltage < threshold_limit) {
        ok_limit = true;
    }
    else { 
        error_code = 0; 
        ok_shutdown = false;
        ok_limit = false;
    } 

    //Serial.print("Voltage: ");
    //Serial.println(inputVoltage);
}

// handle voltage conditions and set error codes
void VoltageHandler::handle()  { 

    if (ok_shutdown && error_code!=2) {
        react_type("critical"); // React to the error condition 
        //Serial.print("critical: ");
        error_code = 3; // Set error code to 2 for critical low voltage
        report_error(); 
    } else if (ok_limit && error_code==0) {
        react_type("low_power"); // React to the error condition 
        //Serial.print("low_power: ");
        error_code = 1; // Set error code to 1 for low voltage
        //report_error(); 
    } 
    else if(!ok_shutdown && !ok_limit && error_code!=0) {
        react_type("normal"); // React to the error condition 
        //Serial.print("normal: ");
        error_code = 0; // Set error code to 0 for normal voltage
    } 
 
}
