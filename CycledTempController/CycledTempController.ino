long waitTime = 10000; //1 min
long waitTime2 = 10000; //30 sec

long timePassed = 0;
long timePassed2 = 0;
int buttonPressed = 1;
int notPressedBefore = 0;
long printTime = 0;

double firstTemp = 20.0;
double secondTemp = 40.0;

bool firstRun = true;
#define temp1pin 6
#define temp2pin 7

double tempMeasure = 0.0;
int tempTimePassed = 0;
int tempTimePassed2 = 0;

int timePassedCheck = waitTime / 1000;
int timePassedCheck2 = waitTime2 / 1000;

bool hitTemp = false;
bool hitTemp2 = false;
bool lightOnOff = false;
bool lightOnOff2 = false;
bool cycleComplete = false;

bool F1hit = false;
bool F2hit = false;
bool cycle1complete = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(temp1pin, OUTPUT);
  pinMode(temp2pin, OUTPUT);
  digitalWrite(temp1pin, HIGH);
  digitalWrite(temp2pin, HIGH);
  delay(2000);
  digitalWrite(temp1pin, LOW);
  digitalWrite(temp2pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  heater();
}

bool timeWait(long timerVar, long timeToWait = 500) {
  return millis() - timerVar >= timeToWait;
}

bool printWait(long timerVar, long timeToWait = 1000) {
  return millis() - timerVar >= timeToWait;
}

bool checkTemp(double temp, double tempCheck){
  return temp >= tempCheck;
}

void heater(){
/*----------------------------------------------CHECK FIRST RUN----------------------------------------------*/
  if (firstRun == true) 
  {
    firstRun = false;
    digitalWrite(temp1pin, HIGH);
    tempMeasure = tempMeasure + 1;
    printTime = millis();
    Serial.println("First run check");
  } 
/*----------------------------------------------LIGHT ON AND OFF HEAT TO 100----------------------------------------------*/
  else if ( !checkTemp(tempMeasure, firstTemp) && printWait(printTime) && lightOnOff == false && !cycle1complete) 
  { //if the temp is lower than max true and keep heater on
    digitalWrite(temp1pin, HIGH);
    printTime = millis();
    tempMeasure = tempMeasure + 1.0;
    lightOnOff = true;
    Serial.print("1st ef Heater on heading to 100 for 90min. Current temp: ");Serial.println(tempMeasure);
  } 
  else if ( !checkTemp(tempMeasure, firstTemp) && printWait(printTime) && lightOnOff == true && !cycle1complete) 
  { //if the temp is lower than max true and keep heater on
    digitalWrite(temp1pin, LOW);
    printTime = millis();
    tempMeasure = tempMeasure + 1.0;
    lightOnOff = false;
    Serial.print("2nd ef Heater on heading to 100 for 90min. Current temp: ");Serial.println(tempMeasure);
  } 
/*----------------------------------------------LIGHT ON KEEP AT 100----------------------------------------------*/
  else if ( checkTemp(tempMeasure, firstTemp) && printWait(printTime) && hitTemp == false && !cycle1complete) 
  {
    digitalWrite(temp1pin, HIGH);
    printTime = millis();
    tempMeasure = firstTemp;
    timePassed = millis();
    tempTimePassed = tempTimePassed + 1;
    Serial.print("3rd ef Heater at 100 staying here for 90 min. Current temp: ");Serial.print(tempMeasure);Serial.print(" Time Passed: ");Serial.println(tempTimePassed);
    hitTemp = true;
  } 
  
  else if ( checkTemp(tempMeasure, firstTemp) && printWait(printTime) && !timeWait(timePassed, waitTime) && hitTemp == true && !cycle1complete) 
  {
    digitalWrite(temp1pin, HIGH);
    printTime = millis();
    tempMeasure = firstTemp;
    tempTimePassed = tempTimePassed + 1;
    Serial.print("4th ef Heater at 100 staying here for 90 min. Current temp: ");Serial.print(tempMeasure);Serial.print(" Time Passed: ");Serial.println(tempTimePassed);
  } 
  else if ( tempTimePassed == timePassedCheck && F1hit == false) {
    F1hit = true;
    cycle1complete = true;
  }
/*----------------------------------------------LIGHT ON AND OFF HEAT TO 120----------------------------------------------*/
  else if ( timeWait(timePassed, waitTime) && printWait(printTime) && !checkTemp(tempMeasure, secondTemp) && lightOnOff2 == false && F1hit == true) 
  {
    printTime = millis();
    digitalWrite(temp1pin, LOW);
    digitalWrite(temp2pin, LOW);
    lightOnOff2 = true;
    tempMeasure = tempMeasure + 1.0;
    hitTemp = false;
    Serial.print("5th ef Heater on heading to 120 for 120 min. Current temp: ");Serial.println(tempMeasure);
  } 
  
  else if ( timeWait(timePassed, waitTime) && printWait(printTime) && !checkTemp(tempMeasure, secondTemp) && lightOnOff2 == true && F1hit == true) 
  {
    printTime = millis();
    digitalWrite(temp2pin, HIGH);
    lightOnOff2 = false;
    tempMeasure = tempMeasure + 1.0;
    tempTimePassed = 0;
    Serial.print("6th ef Heater on heading to 120 for 120 min. Current temp: ");Serial.println(tempMeasure);
  } 
/*----------------------------------------------LIGHT ON KEEP AT 120----------------------------------------------*/
  else if ( checkTemp(tempMeasure, secondTemp) && printWait(printTime) && hitTemp2 == false && F1hit) 
  {
    digitalWrite(temp2pin, HIGH);
    printTime = millis();
    tempMeasure = secondTemp;
    timePassed2 = millis();
    tempTimePassed2 = tempTimePassed2 + 1;
    Serial.print("7th ef Heater at 100 staying here for 90 min. Current temp: ");Serial.print(tempMeasure);Serial.print(" Time Passed: ");Serial.println(tempTimePassed2);
    hitTemp2 = true;
  }
  else if ( checkTemp(tempMeasure, secondTemp) && printWait(printTime) && !timeWait(timePassed2, waitTime2) && hitTemp2 == true && F1hit == true) 
  {
    digitalWrite(temp2pin, HIGH);
    printTime = millis();
    tempMeasure = secondTemp;
    timePassed = millis();
    tempTimePassed2 = tempTimePassed2 + 1;
    Serial.print("8th ef Heater at 100 staying here for 90 min. Current temp: ");Serial.print(tempMeasure);Serial.print(" Time Passed: ");Serial.println(tempTimePassed2);
  } 
  else if ( tempTimePassed2 == timePassedCheck2 && F2hit == false ) 
  {
    F2hit = true;
  }
  
  else if ( printWait(printTime) && F2hit == true ) 
  {
    digitalWrite(temp2pin, LOW);
    printTime = millis();
    Serial.println("HEATER IS OFF");
  }
}
