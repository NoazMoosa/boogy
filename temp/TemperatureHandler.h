#include "ErrorHandler.h"
#include "SimpleDFPlayer.h"
#include <Arduino.h> 
#include "Pins.h"

class TemperatureHandler : public ErrorHandler {
    private:
        SimpleDFPlayer* player;
        static const int number_NTC = 3;

        struct NTC {
            String name;
            String type;
            int s; // sound to play when the temperature is over the threshold
            float threshold;
            int pin;
            volatile bool ok ; // true if the temperature is ok, false if it is  not
            volatile float temperature; // Temperature value 
            volatile bool known ; // true if the temperature is known, false if it is not
        };

        NTC NTCs[number_NTC] = {
            {"bat1","critical", 1, 50.0, temp_bat1,true,25.0,false},  //NTCs[0]
            {"bat2","critical", 1, 50.0, temp_bat2,true,25.0,false},  //NTCs[1]
            {"relay","critical",1, 35.0, temp_relay,true,25.0,false} //NTCs[2]
        };
        
    public:
        TemperatureHandler(int code, SimpleDFPlayer* dfp) : ErrorHandler(code),player(dfp) {}

        void report_error() const override;
        void handle() override; 
        void check() override;  // Check if the error condition is met
        bool is_over_temp(NTC& X); // Check if the temperature is over the threshold


        ~TemperatureHandler() override = default;
};
