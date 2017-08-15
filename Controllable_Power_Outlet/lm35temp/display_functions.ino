/*
 *  The Rx pin of the SerLCD is connected to 
 *  Arduino digital pin 2 (Tx)  We set the SoftwareSerial 
 *  Rx to 0 because the SerLCD has no facility to transmit
 *  back.
 */

#include <SoftwareSerial.h>
#include <SerLCD.h>

SoftwareSerial NSS(0,2);
SerLCD theLCD(NSS);
const int tim = 500;
extern const float minTemp;
extern const float maxTemp;

//Initializing the LCD
void LCDsetup(){
  // Remember to start the NewSoftSerial port before doing things with the SerLCD
  NSS.begin(9600); 
  // This will attempt to initialize the display to blank with the backlight on 
  theLCD.begin();
  theLCD.clear();
  //Give time for screen to initialize
  delay(tim);
}

//Prints the temp header text
void printTempHeader(){
  theLCD.setPosition(1,0);
  theLCD.print("TempC:");
  theLCD.setPosition(2,0);
  theLCD.print("TempF:");
}

void printTempHeaderFah(){
  theLCD.setPosition(1,0);
  theLCD.print("Temp:");
  theLCD.setPosition(2,0);
  theLCD.print(minTemp);theLCD.print("-");theLCD.print(maxTemp);
}

//Prints the temp header text
void printDualFTempHeader(){
  theLCD.setPosition(1,0);
  theLCD.print("Temp1:");
  theLCD.setPosition(2,0);
  theLCD.print("Temp2:");
}

//Prints and updates the temperature displayed no the LCD
void printTempLCD(float tempC, float tempF){
  theLCD.setPosition(1,7);
  theLCD.print(tempC,0);theLCD.print(char(223));theLCD.print("C    ");
  theLCD.setPosition(2,7);
  theLCD.print(tempF,0);theLCD.print(char(223));theLCD.print("F    ");
}

void printTempFahLCD(float tempF){
  theLCD.setPosition(1,6);
  theLCD.print(tempF,0);theLCD.print(char(223));theLCD.print("F     ");
}

//Prints Dual Fahrenheit Temp readings
void printDualFTempLCD(float tempF1, float tempF2){
  theLCD.setPosition(1,7);
  theLCD.print(tempF1,0);theLCD.print(char(223));theLCD.print("F ");
  theLCD.setPosition(2,7);
  theLCD.print(tempF2,0);theLCD.print(char(223));theLCD.print("F ");
}

//Prints to debug screen
void printTempSerialDebug(float tempC, float tempF){
  Serial.print("in DegreeC=");
  Serial.print("\t");
  Serial.print(tempC);
  Serial.println();
  Serial.print("in Fahrenheit=");
  Serial.print("\t");
  Serial.print(tempF);
  Serial.println();
}

//Prints Dual Fahrenheit temp readings to debug screen
void printDualFTempDebug(float tempF1, float tempF2){
  Serial.print("in Fahrenheit Sensor1=");
  Serial.print("\t");
  Serial.print(tempF1);
  Serial.println();
  Serial.print("in Fahrenheit Sensor2=");
  Serial.print("\t");
  Serial.print(tempF2);
  Serial.println();
}
