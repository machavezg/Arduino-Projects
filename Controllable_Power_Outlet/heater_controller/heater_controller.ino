#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//set or modify any variables on temp_functions tab
//letting the compiler know this is an external variable pulling it from temp_functions
extern const int ledPin;
extern const int relayPin;
extern const int tim;
extern const float minTemp;
extern const float maxTemp;
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//This runs only at initial run of arduino
void setup()
{ 
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
  analogReference(EXTERNAL);
}

void loop(){
  //Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.println(" degrees F TMP36");
  tempControl(tmp36());
  printMinMax(minTemp, maxTemp);
}

