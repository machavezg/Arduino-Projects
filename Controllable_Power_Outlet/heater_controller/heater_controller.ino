#include <Wire.h>

//set or modify any variables on temp_functions tab
//letting the compiler know this is an external variable pulling it from temp_functions
extern const int ledPin;
//This runs only at initial run of arduino
void setup()
{ 
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
  analogReference(EXTERNAL);
}

void loop(){
  Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.println(" degrees F TMP36");
  tempControl(tmp36());
  delay(1000);
}

