const int temp1pin = 6;
const int temp2pin = 7;
const float cycle1temp = 100.0;
bool avoid = false;
bool avoid1 = false;
extern const float minTempSys1;
extern const float maxTempSys1;
extern const float minTempSys2;
extern const float maxTempSys2;
bool indicatorLED = false;
long printTime = 0;
bool cycle1Complete = false;
bool cycle2Complete = false;
long cycle1Timer = 0;
long cycle2Timer = 0;
int count = 0;
long waitTime = 30000; //10 sec
long waitTime1 = waitTime;


extern const float firstTemp; //80.0 F
extern const float secondTemp; //90.0 F

void doorOvenSetup() {
  // put your setup code here, to run once:
  pinMode(temp1pin, OUTPUT);
  pinMode(temp2pin, OUTPUT);
  digitalWrite(temp1pin, HIGH);
  digitalWrite(temp2pin, HIGH);
  delay(2000);
  digitalWrite(temp1pin, LOW);
  digitalWrite(temp2pin, LOW);
}

//Returns false as long as the time you need to wait has not passed
bool timeWait(long timerVar, long timeToWait = 500) {
  return millis() - timerVar > timeToWait;
}
//redundant, same as above
bool printWait(long timerVar, long timeToWait = 1000) {
  return millis() - timerVar > timeToWait;
}
//checks temp and returns true as long as the reading is lower than the target
bool checkTemp(float reading, float targetReading){
  return reading <= targetReading;
}

void cycleHeat( float tempReading, int numberOfHeaters , float firstCycleTemp, float secondCycleTemp) 
{
  if( checkTemp(tempReading, firstCycleTemp) && !avoid && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys1, maxTempSys1, true);
    switch (indicatorLED) {
      case false:
        digitalWrite(temp1pin, LOW);
        indicatorLED = true;
        break;
      case true:
        digitalWrite(temp1pin, HIGH);
        indicatorLED = false;
        break;
    }
    printTime = millis();
    Serial.println("IF STATEMENT");
  }
  
  else if ( !checkTemp(tempReading, firstCycleTemp) && !avoid && printWait(printTime))
  {
    avoid = true;
    cycle1Timer = millis();
    Serial.println("EF 1");
  }
  
  else if ( !cycle1Complete && !timeWait(cycle1Timer, waitTime) && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys1, maxTempSys1, true);
    Serial.println("EF 2");
    Serial.println(count+=1);
    digitalWrite(temp1pin, HIGH);
    while(timeWait(cycle1Timer, waitTime-1000)) {
      cycle1Complete = true;
      Serial.println("While");
      digitalWrite(temp1pin, LOW);
      break;
    }
    printTime = millis();
  }
  
  else if ( cycle1Complete && checkTemp(tempReading, secondCycleTemp) && !avoid1 && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys2, maxTempSys2, true);
    Serial.println("EF 3");
    switch (indicatorLED) {
      case false:
        digitalWrite(temp2pin, LOW);
        indicatorLED = true;
        break;
      case true:
        digitalWrite(temp2pin, HIGH);
        indicatorLED = false;
        break;
    }
    printTime = millis();
  }
  
  else if ( !checkTemp(tempReading, firstCycleTemp) && !avoid1 && printWait(printTime))
  {
    avoid1 = true;
    cycle2Timer = millis();
    count = 0;
    Serial.println("EF 4");
  } 

  else if ( !cycle2Complete && !timeWait(cycle2Timer, waitTime1) && printWait(printTime) && avoid1) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys2, maxTempSys2, true);
    Serial.println("EF 5");
    Serial.println(count+=1);
    digitalWrite(temp2pin, HIGH);
    while(timeWait(cycle2Timer, waitTime-1000)) {
      cycle2Complete = true;
      Serial.println("While2");
      digitalWrite(temp2pin, LOW);
      break;
    }
    printTime = millis();
  }
  
  else if ( cycle2Complete && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys1, maxTempSys1, false);
    printTime = millis();
    Serial.println("EF 6");
    return true;
  }
  
}

