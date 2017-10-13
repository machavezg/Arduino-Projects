/* Input-side (button) Arduino code */
#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
int BUTTON = 6;
int BOARDLEDPIN = 13;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  Serial.begin(19200);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BOARDLEDPIN, OUTPUT);
  XBee.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(BUTTON));
  if (digitalRead(BUTTON) == LOW)
  {
    digitalWrite(BOARDLEDPIN, HIGH);
    XBee.write('H');
    delay(50);
  }
  delay(100);
}
