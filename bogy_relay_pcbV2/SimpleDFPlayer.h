#ifndef SIMPLE_DFPLAYER_H
#define SIMPLE_DFPLAYER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class SimpleDFPlayer {
  public:
    SimpleDFPlayer(uint8_t txPin);  // Constructor with TX pin
    void begin();
    void playTrack(uint8_t trackNum);         // 0001.mp3, 0002.mp3
    void setVolume(uint8_t volume);           // 0-30
    
  private:
    SoftwareSerial* dfSerial;
    uint8_t tx;
    void sendCommand(uint8_t cmd, uint8_t param1, uint8_t param2);
};

#endif
