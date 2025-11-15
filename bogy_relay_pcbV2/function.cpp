# include "function.h"
# include <Arduino.h>



int level = 0;



  
// return the state of the relay true is conduction and false is not conduction turn
void turn_relay(bool start){
    if(start != relayState && start) {
      digitalWrite(relayOnPin, HIGH);
      delay(100);
      digitalWrite(relayOnPin, LOW);
      delay(1000);
      //Serial.println("Relay on");
    }
    else if(relayState != start && !start) {
      digitalWrite(relayOffPin, HIGH);
      delay(100);
      digitalWrite(relayOffPin, LOW);
      delay(1000);
      //Serial.println("Relay off");
    }  
    
    relayState = start;
}
  
// interrupt function that check all the temperture and humidety 



void pwm_stop(bool yes){
  if (yes){
    servoCtrl.disable();
  }
  else if (!yes){
    servoCtrl.enable();
  }
  
}
  
void limit_pwm(int level){
      servoCtrl.setMaxAngle(level); // Set the maximum angle for the servo
  } 
  
  
  
  
  
  
