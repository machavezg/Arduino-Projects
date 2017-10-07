// Min and Max temperature settings in Degrees Fahrenheit
extern const float minTemp;
extern const float maxTemp;
//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
extern const int relayAPin;
extern const int relayBPin;
extern const int ledPin;
// Calling temp from tempSensor_functions
extern float temp;
// control is used for the temperature controller function, 1 = On, 0 = Off. 
int control = 1;

void tempControlSetup(int numberOfSensors){
  switch (numberOfSensors) {
    case 1:
       pinMode(ledPin, OUTPUT);
       pinMode(relayAPin, OUTPUT);
       break;
    case 2:
       pinMode(ledPin, OUTPUT);
       pinMode(relayAPin, OUTPUT);
       pinMode(relayBPin, OUTPUT);
       digitalWrite(relayAPin, LOW);
       digitalWrite(relayBPin, LOW);
       break;
  }
}

// Control oneor two relay, pin 12 or 8, PICK ONE!!
//(tempRead is the input temperature read by the temp sensor)
bool tempControl(float tempRead, int oneOrTwo){
  if (control == 1 && (tempRead > minTemp && tempRead < maxTemp ) && RTCPowerController() ){ //true as long as < minTemp
    numberOfHeaters(oneOrTwo, HIGH);    //digitalWrite(relayAPin, HIGH);
    return true;
  } else if (control == 1 && tempRead >= maxTemp ) {
    numberOfHeaters(oneOrTwo, LOW);    //digitalWrite(relayAPin, LOW);
    control = 0;
    return false;
  } else if ( control == 0 && (tempRead > minTemp && tempRead < maxTemp)) {
    numberOfHeaters(oneOrTwo, LOW);    //digitalWrite(relayAPin, LOW);
    return false;
  } else if ( tempRead <= minTemp && RTCPowerController() ) {
    numberOfHeaters(oneOrTwo, HIGH);    //digitalWrite(relayAPin, HIGH);
    control = 1;
    return true;
  } else {
    numberOfHeaters(oneOrTwo, LOW);    //digitalWrite(relayAPin, LOW);
    return false;
  }
}

void numberOfHeaters(int oneOrTwo, bool highOrLow) {
  switch ( oneOrTwo ) {
    case 1:
       digitalWrite(relayAPin, highOrLow);
       break;
    case 2:
       digitalWrite(relayAPin, highOrLow);
       digitalWrite(relayBPin, highOrLow);
       break;
  }
}

// IGNORE THIS IF YOU DON'T KNOW THIS
void tempControlDebug(float tempRead){
  //Define min temp and max temp at top
  if (tempRead <= maxTemp && tempRead <= minTemp){ //true as long as < minTemp
    digitalWrite(relayAPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } else if ( tempRead >= minTemp && tempRead <= maxTemp ){ //true as long as temF is between minTemp and maxTemp
    digitalWrite(relayAPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } else if ( tempRead >= maxTemp){
    digitalWrite(relayAPin, LOW);
    digitalWrite(ledPin, LOW);
      while ( tempRead >= minTemp ){
        digitalWrite(relayAPin, LOW);
        digitalWrite(ledPin, LOW);
        tempRead = temp;
      }
  } else{
    digitalWrite(relayAPin, LOW);
    digitalWrite(ledPin, LOW);
  }
}
