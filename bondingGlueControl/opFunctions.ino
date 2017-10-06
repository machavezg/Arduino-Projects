//This constant is used to control the amount of time allowed to pass before another button press is registered
const long timerWait = 500;
//This variable is used to compare time passed to the constant above
long timer = 0;
int countVar = 0;
long timerPrint = 0;
extern bool buttonState;
int secPassed = 0;

//Timer variables
long runForCheck = 0;
long runFor = 5000; //Run air for this much time
//Countdown var
int countDown = 5;

//Add to setup to initialize and use the toggleButton function
void toggleButtonSetup(int inputPin) {
  pinMode(inputPin, INPUT_PULLUP);
}

void initializeLowHigh(int componentPin, int lowOrHigh) {
  switch (lowOrHigh) {
    case 0:
       digitalWrite(componentPin, LOW);
       break;
    case 1:
       digitalWrite(componentPin, HIGH);
       break;
    default:
       digitalWrite(componentPin, LOW);
       break;
  }
}

bool timeWait(long timerVar, long timeToWait = 500) {
  return millis() - timerVar > timeToWait;
}

int count(int countVariable, int downOrUp) {
  switch (downOrUp) {
    case 0:
       return countVariable -= 1;
       break;
    case 1:
       return countVariable += 1;
       break;
    default:
       return 999;
       break;
  }
}

//Toggle button variable, use momentary button for this
void toggleButton(int inputPin, int toggledItem) {
  int toggleState;
  toggleState = digitalRead(inputPin);
  
  if (toggleState == LOW && buttonState == true && timeWait(timer) )
  {
    digitalWrite(toggledItem, LOW);
    buttonState = false;
    timer = millis();
    runForCheck = millis();
    countVar = count(countVar, 1);
  } else if (toggleState == LOW && buttonState == false && timeWait(timer) && false ) {
    digitalWrite(toggledItem, HIGH);
    buttonState = true;
    timer = millis();
  } else if (timeWait(timerPrint, 1000)) {
    Serial.print("Button State: "); Serial.println(buttonState);
    Serial.print("Count: "); Serial.println(countVar);
    Serial.println(secPassed += 1);
    Serial.println(timeWait(runForCheck, runFor));
    Serial.print("Count Down: ");Serial.println(countDown);
    timerPrint = millis();
  } else if (timeWait(runForCheck, runFor) && buttonState == false) {
    digitalWrite(toggledItem, HIGH);
    buttonState = true;
    Serial.println("TimeCheck ran");
  } 
//  else if (!timeWait(runForCheck, runFor) && buttonState == false && timeWait(timerPrint, 1000)) {
//    countDown -= 1;
//    Serial.print("Count Down: ");Serial.println(countDown);
//    timerPrint = millis();
//  }
}






