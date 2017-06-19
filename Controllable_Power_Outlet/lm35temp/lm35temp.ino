/* ReadMe
 * Ingredients:
 * -LM35 Sensor
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
  tempDualControlSetup();

  cleanSetup();
  delay(1000);
}

void loop(){
  //Printing the Temp readings to LCD
  printTempFahLCD(tempFahrenheit(sensor1));
  
  //Printing the Temp readings to Monitor screen for debug
  //printTempSerialDebug(tempCelsius(sensor1),tempFahrenheit(sensor1));

  //Temperature Controller see relayController_functions
  tempDualControl(tempFahrenheit(sensor1));
  
  //Uncomment to Debug Temperature Controller see relayController_functions
  //tempControlDebug(tempFahrenheit(sensor1));
  
  //Uncomment the line below to Print the Dual Fahrenehit readings to the LCD
  //printDualFTempLCD(tempFahrenheit(sensor1),tempFahrenheit(sensor2));
  
  //For dual Fahrenheit Debug uncomment line below
  //printTempSerialDebug(tempFahrenheit(sensor1),tempFahrenheit(sensor2));
  //delay(2000);
  //cleanReading(sensor1);
}


