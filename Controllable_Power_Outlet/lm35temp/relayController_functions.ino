
// Min and Max temperature settings in Degrees Fahrenheit
extern const float minTemp;
extern const float maxTemp;
//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
extern const int relayAPin;
extern const int relayBPin;
extern const int relayCPin;
extern const int ledPin;
// Calling temp from tempSensor_functions
extern float temp;
// control is used for the temperature controller function, 1 = On, 0 = Off. 
int control = 1;
//LED Variables
extern bool indicatorLED;

long timer = 0;
long waitTime = 1000;

//Returns false as long as the time you need to wait has not passed
bool timeWait(long timerVar, long timeToWait) {
  return millis() - timerVar > timeToWait;
}

void tempControlSetup(int numberOfSensors){
  switch (numberOfSensors) {
    case 1:
       pinMode(ledPin, OUTPUT);
       pinMode(relayAPin, OUTPUT);
       digitalWrite(relayAPin, LOW);
       break;
    case 2:
       pinMode(ledPin, OUTPUT);
       pinMode(relayAPin, OUTPUT);
       pinMode(relayBPin, OUTPUT);
       digitalWrite(relayAPin, LOW);
       digitalWrite(relayBPin, LOW);
       break;
    case 3:
       pinMode(ledPin, OUTPUT);
       pinMode(relayAPin, OUTPUT);
       pinMode(relayBPin, OUTPUT);
       pinMode(relayCPin, OUTPUT);
       digitalWrite(relayAPin, LOW);
       digitalWrite(relayBPin, LOW);
       digitalWrite(relayCPin, LOW);
    break;
  }
}

// Control oneor two relay, pin 12 or 8, PICK ONE!!
//(tempRead is the input temperature read by the temp sensor)
bool tempControl(float tempRead, int oneOrTwo){
  if (control == 1 && (tempRead > minTemp && tempRead < maxTemp ) && RTCPowerController() )//&& timeWait(timer, waitTime) )
  { //true as long as < minTemp
    numberOfHeaters(oneOrTwo, HIGH);    //digitalWrite(relayAPin, HIGH);
    switch (indicatorLED) {
      case false:
        pixels.setPixelColor(0, pixels.Color(0,0,0));
        pixels.show();
        indicatorLED = true;
        break;
      case true:
        pixels.setPixelColor(0, pixels.Color(0,255,0));
        pixels.show();
        indicatorLED = false;
        break;
    }
    timer = millis();
    return true;
  } 
  else if ( (control == 1 | control == 0)  && tempRead >= maxTemp )//&& timeWait(timer, waitTime)) 
  {
    numberOfHeaters(oneOrTwo, LOW);    //digitalWrite(relayAPin, LOW);
    pixels.setPixelColor(0, pixels.Color(0,255,0));
    pixels.show();
    control = 0;
    timer = millis();
    return false;
  } 
  else if ( control == 0 && (tempRead > minTemp && tempRead < maxTemp) )//&& timeWait(timer, waitTime)) 
  {
    numberOfHeaters(oneOrTwo, LOW);    //digitalWrite(relayAPin, LOW);
    pixels.setPixelColor(0, pixels.Color(0,255,0));
    pixels.show();
    timer = millis();
    return false;
  } 
  else if ( tempRead <= minTemp && RTCPowerController() )//&& timeWait(timer, waitTime)) 
  {
    numberOfHeaters(oneOrTwo, HIGH);    //digitalWrite(relayAPin, HIGH);
    control = 1;
    switch (indicatorLED) {
      case false:
        pixels.setPixelColor(0, pixels.Color(0,0,0));
        pixels.show();
        indicatorLED = true;
        break;
      case true:
        pixels.setPixelColor(0, pixels.Color(0,255,0));
        pixels.show();
        indicatorLED = false;
        break;
    }
    timer = millis();
    return true;
  } 
  else 
  {
    numberOfHeaters(oneOrTwo, LOW);    //digitalWrite(relayAPin, LOW);
    pixels.setPixelColor(0, pixels.Color(255,0,0));
    pixels.show();
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
    case 3:
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
