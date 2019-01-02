#include <Wire.h>

// Hardware Constants

#define PIN_RED 9
#define PIN_GREEN 5
#define PIN_BLUE 3

// Configuration

#define I2C_ADDRESS 0x56

#define MAX_CMD_LEN 2 // Maximum command length we accept

#define WRITE_DELAY 4

// Global Variables, State

byte brightness_red   = 0xFF;
byte brightness_green = 0xFF;
byte brightness_blue  = 0xFF;

byte brightness_red_old   = 0xFF;
byte brightness_green_old = 0xFF;
byte brightness_blue_old  = 0xFF;

byte command[MAX_CMD_LEN + 1];

// Config

byte register_red   = 'R';
byte register_green = 'G';
byte register_blue  = 'B';

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2C_ADDRESS);
  //Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(57600);
  command[MAX_CMD_LEN] = 0;
}

void loop() {
  if (brightness_red != brightness_red_old) {
    analogWrite(PIN_RED, brightness_red);
  }
  if (brightness_green != brightness_green_old) {
    analogWrite(PIN_GREEN, brightness_green);
  }
  if (brightness_blue != brightness_blue_old) {
    analogWrite(PIN_BLUE, brightness_blue);
  }

  brightness_red_old = brightness_red;
  brightness_green_old = brightness_green;
  brightness_blue_old = brightness_blue;

  /*
  Serial.print((int) brightness_red); Serial.print(' ');
  Serial.print((int) brightness_green); Serial.print(' ');
  Serial.print((int) brightness_blue); Serial.print(' ');
  Serial.print('\n');
  */

  delay(WRITE_DELAY);
}

/*void requestEvent() {

}*/

void receiveEvent(int count) {
  for (int i = 0; Wire.available() > 0; i++) { // loop through all but the last
    if (i < MAX_CMD_LEN) {
      command[i] = Wire.read();
    } else {
      Wire.read();
    }
  }
  Serial.print((char)command[0]); Serial.print(' ');
  Serial.println((int)(unsigned char)command[1]);
  switch(command[0]) {
    case 'R':
      brightness_red = command[1];
      break;
    case 'G':
      brightness_green = command[1];
      break;
    case 'B':
      brightness_blue = command[1];
      break;
    default:
      return;
  }
}
