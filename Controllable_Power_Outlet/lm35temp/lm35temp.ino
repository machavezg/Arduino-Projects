/* ReadMe
 * Ingredients:
 * -Arduino Uno R3
 * -LM35 Sensor
 * -Sparkfun Serial LCD-09067
 * -serLCD library from https://github.com/scogswell/ArduinoSerLCD
 * -Sparkfun Beefcake Relay Control Kit (Ver.2.0)
 * -Adafruit DS3231
 * -Adafruit ProtoShield Uno
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
 *    -(CTRL1) pin to Digital 8
 *    If 2 Relays
 *    -(CTRL2) pin to Digital 12
 *  DS3231 Pins:
 *    -(+) Vin pin to 5V
 *    -(-) to GND
 *    -(SCL) to Analog 5
 *    -(SDA) to Analog 4
 *  ICSP Pin Out (3):
 *  ( )( )( )
 *  (-)( )(+)
 *  
 * Resources:
 *  (1)-https://sites.google.com/site/myscratchbooks/home/projects/project-05-using-lm35-lm34
 *  (2)-http://www.circuitstoday.com/lm35-and-arduino-interfacing
 *  (3)-http://www.pighixxx.com/test/portfolio-items/uno/#prettyPhoto
 */
extern const int sensor1; // Assigning analog pin A0 to variable 'sensor1' see tempSensor_Functions
extern const int sensor2; // Assigning analog pin A1 to variable 'sensor2' see tempSensor_Functions

void setup(){
  //Serial Mon to debug
  Serial.begin(19200);
  
  //LCD being initialized
  LCDsetup();
  
  //LM35 being initialized
  LM35setup();
  
  //Displaying TempC and TempF labels to lcd permanently
  printTempHeaderFah();
  
  //Uncomment below if using two LM35 sensors
  //LM35DualSetup()
  
  //Uncomment line below to print Fahrenheit only
  //printFTempHeader();

  //Temerature Controller Setup
  tempControlSetup(2);  //tempControlSetup(int oneOrTwo) 1: for one heater, 2: for two heaters

  //RTC DS3231 Setup
  RTCSetup();

  //Setup the temp reading accuracy code
  cleanSetup();  
  
  //Wait for Console to start
  delay(3000);
}

void loop(){
  
  //Printing the Temp readings to LCD
  printTempFahLCD(tempFahrenheit(sensor1));
  
  //Printing the Temp readings to Monitor screen for debug
  //printTempSerialDebug(tempCelsius(sensor1),tempFahrenheit(sensor1));

  //Temperature Controller see relayController_functions
  tempControl(tempFahrenheit(sensor1), 2);
  
  //Uncomment to Debug Temperature Controller see relayController_functions
  //tempControlDebug(tempFahrenheit(sensor1));
  
  //Uncomment the line below to Print the Dual Fahrenehit readings to the LCD
  //printDualFTempLCD(tempFahrenheit(sensor1),tempFahrenheit(sensor2));
  
  //For dual Fahrenheit Debug uncomment line below
  //printTempSerialDebug(tempFahrenheit(sensor1),tempFahrenheit(sensor2));

  //RTC Debug Power clock controller started, should loop through first to make sure it should be running
  //RTCPowerControllerDebug();
  
  //Clean display reading
  cleanReading(sensor1);
    
  delay(1000);
  
}


