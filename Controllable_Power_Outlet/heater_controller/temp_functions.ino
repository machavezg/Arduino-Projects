
//TMP36 Pin Variables
const int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
//Set the min and max temperatures that you want the heaters to run at.
const float minTemp = 80.0;
const float maxTemp = 85.0;
//The pin that will be controlling the heaters
const int ledPin = 13;

//Aref voltage
const float aref_voltage = 3.28; // tie 3.3V to ARef and measure it with a multimeter

//Used to control the heaters
void tempControl(float tempF){
  //Define min temp and max temp at top
  if (tempF <= maxTemp && tempF <= minTemp){ //true as long as < minTemp
    digitalWrite(ledPin, HIGH);
    Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.print(" degrees F TMP36 "); Serial.println("Heater is on, if loop");
  } else if ( tempF >= minTemp && tempF <= maxTemp ){ //true as long as temF is between minTemp and maxTemp
    digitalWrite(ledPin, HIGH);
    Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.print(" degrees F TMP36 "); Serial.println("Heater is on, else if loop 1");
  } else if ( tempF >= maxTemp){
    digitalWrite(ledPin, LOW);
    Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.print(" degrees F TMP36 "); Serial.println("Heater is off, else if loop 2");
    while ( tempF >= minTemp ){
      digitalWrite(ledPin, LOW);
      Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.print(" degrees F TMP36 "); Serial.println("Heater is off, while loop");
      tempF = tmp36();
      delay(1000);
    }
  } else{
    digitalWrite(ledPin, LOW);
    Serial.print("TMP36: "); Serial.print(tmp36(), 2); Serial.print(" degrees F TMP36 "); Serial.println("Heater is off, else loop");
  }
}

//used to read the data from the temperature sensor
float tmp36(){
   //getting the voltage reading from the temperature sensor
 int tempReading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = tempReading * aref_voltage; //read 3.36
 voltage /= 1024.0; 
 
 // print out the voltage
 //Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //Serial.print(temperatureC); Serial.println(" degrees C");
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 return temperatureF;
}
