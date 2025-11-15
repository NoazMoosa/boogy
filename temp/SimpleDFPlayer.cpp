#include "SimpleDFPlayer.h"

SimpleDFPlayer::SimpleDFPlayer(uint8_t txPin) {
  tx = txPin;
  dfSerial = new SoftwareSerial(255, tx); // No RX, TX only
}

void SimpleDFPlayer::begin() {
  dfSerial->begin(9600);
  delay(1000); // Wait for DFPlayer to initialize
}

void SimpleDFPlayer::playTrack(uint8_t trackNum) {
  sendCommand(0x03, 0x00, trackNum); // Play track by index
}


void SimpleDFPlayer::setVolume(uint8_t volume) {
  if (volume > 30) volume = 30;
  sendCommand(0x06, 0x00, volume); // Set volume
}

void SimpleDFPlayer::sendCommand(uint8_t cmd, uint8_t param1, uint8_t param2) {
  uint8_t command[10] = {
    0x7E, 0xFF, 0x06, cmd, 0x00, param1, param2, 0x00, 0x00, 0xEF
  };

  uint16_t checksum = 0 - (command[1] + command[2] + command[3] + command[4] + command[5] + command[6]);
  command[7] = (checksum >> 8) & 0xFF;
  command[8] = checksum & 0xFF;

  for (uint8_t i = 0; i < 10; i++) {
    dfSerial->write(command[i]);
  }
}
