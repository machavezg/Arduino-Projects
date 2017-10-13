/* ReadMe
 * Ingredients:
 * -Arduino Uno R3
 * -4 Relay Module
 * -Sparkfun Serial LCD-09067
 * -serLCD library from https://github.com/scogswell/ArduinoSerLCD
 * -Sparkfun Beefcake Relay Control Kit (Ver.2.0)
 * 
 * Instructions:
 *  LM35 Pins:
 *    -(+) to 3.3v and AREF
 *    -(-) to GND
 *    -(~) Signal to A0
 *  LCD Pins:
 *    -(+) 5V pin to 5V 
 *    -(-) GND pin to GND
 *    -(RX) RX pin to Digital 2
 *  Beefcake Pins;
 *    -(+) 5V pin to 5V ICSP
 *    -(-) GND pin to GND ICSP
 *    -(CTRL) pin to Digital 12
 *  
 *  ICSP Pin Out (3):
 *  ( )( )( )
 *  (-)( )(+)
 *  
 * Resources:
 *  (1)-https://sites.google.com/site/myscratchbooks/home/projects/project-05-using-lm35-lm34
 *  (2)-http://www.circuitstoday.com/lm35-and-arduino-interfacing
 *  (3)-http://www.pighixxx.com/test/portfolio-items/uno/#prettyPhoto
 */
const int pushButton = 6;
const int relayPin = 12;

bool buttonState = true;

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  initializeLowHigh(relayPin, 1);
  toggleButtonSetup(pushButton);
  delay(2000);
}

void loop() {
  toggleButton1(pushButton, relayPin);
  //RTCPowerControllerDebug();
}
