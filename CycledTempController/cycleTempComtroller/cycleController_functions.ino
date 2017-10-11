extern const int led1pin;
extern const int led2pin;

extern const long heatPhase1;
extern const long heatPhase2;

extern const float minTempSys1;
extern const float maxTempSys1;
extern const float minTempSys2;
extern const float maxTempSys2;

extern const float firstTemp; 
extern const float secondTemp; 

bool avoid = false;
bool avoid1 = false;

bool cycle1Complete = false;
bool cycle2Complete = false;

long cycle1Timer = 0;
long cycle2Timer = 0;

bool indicatorLED = false;

long printTime = 0;

int count = 0;

void doorOvenSetup() {
  // put your setup code here, to run once:
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  digitalWrite(led1pin, HIGH);
  digitalWrite(led2pin, HIGH);
  delay(2000);
  digitalWrite(led1pin, LOW);
  digitalWrite(led2pin, LOW);
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
        digitalWrite(led1pin, LOW);
        indicatorLED = true;
        break;
      case true:
        digitalWrite(led1pin, HIGH);
        indicatorLED = false;
        break;
    }
    printTime = millis();
    Serial.println("IF STATEMENT");
    theLCD.setPosition(2,0);theLCD.print("Heating to 100F");
  }
  
  else if ( !checkTemp(tempReading, firstCycleTemp) && !avoid && printWait(printTime))
  {
    avoid = true;
    cycle1Timer = millis();
    Serial.println("EF 1");
  }
  
  else if ( !cycle1Complete && !timeWait(cycle1Timer, heatPhase1) && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys1, maxTempSys1, true);
    Serial.println("EF 2");
    Serial.println(count+=1);
    digitalWrite(led1pin, HIGH);
    while(timeWait(cycle1Timer, heatPhase1-1000)) {
      cycle1Complete = true;
      Serial.println("While");
      digitalWrite(led1pin, LOW);
      break;
    }
    printTime = millis();
    theLCD.setPosition(2,0);theLCD.print("100F For 90min");
  }
  
  else if ( cycle1Complete && checkTemp(tempReading, secondCycleTemp) && !avoid1 && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys2, maxTempSys2, true);
    Serial.println("EF 3");
    switch (indicatorLED) {
      case false:
        digitalWrite(led2pin, LOW);
        indicatorLED = true;
        break;
      case true:
        digitalWrite(led2pin, HIGH);
        indicatorLED = false;
        break;
    }
    printTime = millis();
    theLCD.setPosition(2,0);theLCD.print("Heating to 120F");
  }
  
  else if ( !checkTemp(tempReading, firstCycleTemp) && !avoid1 && printWait(printTime))
  {
    avoid1 = true;
    cycle2Timer = millis();
    count = 0;
    Serial.println("EF 4");
  } 

  else if ( !cycle2Complete && !timeWait(cycle2Timer, heatPhase2) && printWait(printTime) && avoid1) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys2, maxTempSys2, true);
    Serial.println("EF 5");
    Serial.println(count+=1);
    digitalWrite(led2pin, HIGH);
    while(timeWait(cycle2Timer, heatPhase1-1000)) {
      cycle2Complete = true;
      Serial.println("While2");
      digitalWrite(led2pin, LOW);
      break;
    }
    printTime = millis();
    theLCD.setPosition(2,0);theLCD.print("120F For 120min");
  }
  
  else if ( cycle2Complete && printWait(printTime) ) 
  {
    tempControl(tempReading, numberOfHeaters, minTempSys1, maxTempSys1, false);
    printTime = millis();
    Serial.println("EF 6");
    return true;
    theLCD.setPosition(2,0);theLCD.print("Heating Complete");
  }
  
}

