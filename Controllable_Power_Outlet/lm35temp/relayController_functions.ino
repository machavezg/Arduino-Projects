// Min and Max temperature settings in Degrees Fahrenheit
const float minTemp = 118;
const float maxTemp = 124;
//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
const int relayAPin = 8;
const int relayBPin = 12;
const int ledPin = 13;
// Calling temp from tempSensor_functions
extern float temp;
// control is used for the temperature controller function, 1 = On, 0 = Off. 
int control = 1;

void tempControlSetup(){
  pinMode(ledPin, OUTPUT);
  pinMode(relayAPin, OUTPUT);
}

void tempDualControlSetup(){
  pinMode(ledPin, OUTPUT);
  pinMode(relayAPin, OUTPUT);
  pinMode(relayBPin, OUTPUT);
  digitalWrite(relayAPin, LOW);
  digitalWrite(relayBPin, LOW);
}

// Control one relay, pin 12 or 8, PICK ONE!!
void tempControl(float tempRead){
  if (control == 1 && (tempRead > minTemp && tempRead < maxTemp ) && RTCPowerController() ){ //true as long as < minTemp
    digitalWrite(relayAPin, HIGH);
  } else if (control == 1 && tempRead >= maxTemp ) {
    digitalWrite(relayAPin, LOW);
    control = 0;
  } else if ( control == 0 && (tempRead > minTemp && tempRead < maxTemp)) {
    digitalWrite(relayAPin, LOW);
  } else if ( tempRead <= minTemp && RTCPowerController() ) {
    digitalWrite(relayAPin, HIGH);
    control = 1;
  } else {
    digitalWrite(relayAPin, LOW);
  }
}

// Control two relays, pin 12 and 8
void tempDualControl(float tempRead){
  //Define min temp and max temp at top
  if (control == 1 && (tempRead > minTemp && tempRead < maxTemp ) && RTCPowerController() ){ //true as long as < minTemp
    digitalWrite(relayAPin, HIGH);
    digitalWrite(relayBPin, HIGH);
  } else if (control == 1 && tempRead >= maxTemp ) {
    digitalWrite(relayAPin, LOW);
    digitalWrite(relayBPin, LOW);
    control = 0;
  } else if ( control == 0 && (tempRead > minTemp && tempRead < maxTemp)) {
    digitalWrite(relayAPin, LOW);
    digitalWrite(relayBPin, LOW);
  } else if ( tempRead <= minTemp && RTCPowerController() ) {
    digitalWrite(relayAPin, HIGH);
    digitalWrite(relayBPin, HIGH);
    control = 1;
  } else {
    digitalWrite(relayAPin, LOW);
    digitalWrite(relayBPin, LOW);
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
