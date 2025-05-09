#include "TemperatureHandler.h"

void TemperatureHandler::report_error(int code) const {
    if(code == 1) {
        for (int i = 0; i < number_NTC; i++) {
            if (!NTCs[i].ok) {
                Serial.println("Temperature error: " + NTCs[i].name + " is over the threshold."+
                               " Temperature: " + String(NTCs[i].temperature) +
                               ", Threshold: " + String(NTCs[i].threshold));
            }
        }
   
    }
}
    
void TemperatureHandler::check(){
    for(int i=0; i<number_NTC; i++){
        is_over_temp(NTCs[i]);  
      }
    // change active to true if the temperature is over the threshold
    error_code = 0;
    for (int i = 0; i < number_NTC; i++) {
        if (!NTCs[i].ok) {
            error_code = 1;
            break;  // Exit the loop if any NTC is not ok
        }
    }
}

void TemperatureHandler::handle()  { 
    for(int i=0; i<number_NTC; i++){
        if (!NTCs[i].ok && !NTCs[i].known){
            react_type(NTCs[i].type); // React to the error condition 
            NTCs[i].known = true; // Set the known flag to true  
            //report_error(error_code); // Report the error if any NTC is not ok
        }
      }
    
}



bool TemperatureHandler :: is_over_temp(NTC& X){
    float temperature=0;
    float thermistor_resistance=0;
    const int B_CONSTANT=3940;
      
    // Read the analog value (0-1023)
    temperature = analogRead(X.pin); // Read the analog value from the pin
    // Calculate the thermistor resistance using voltage divider formula
    thermistor_resistance = (10000 * (temperature * (5.0 / 1023.0))) / (5 - (temperature * (5.0 / 1023.0)));
    // Calculate the temperature using the Steinhart-Hart equation (simplified version)
    temperature = (1.0 / (1.0 / 298.15 + (1.0 / B_CONSTANT) * log(thermistor_resistance / 10000.0)))- 273.15;
 
    Serial.println("sensor: " + X.name + ", th: " + String(X.threshold)+ ", temp: " + String(temperature));
    //Serial.print(X.threshold);
    //Serial.println(temperature);
    X.temperature = temperature; // Update the temperature value in the struct
    if (X.ok == false && (temperature <= X.threshold)) {
        X.known = false; // Reset the known flag if temperature is ok
    }
    X.ok = (temperature <= X.threshold); // Update the ok status based on the temperature
    return(temperature > X.threshold);
}