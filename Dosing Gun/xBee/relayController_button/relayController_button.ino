
//PUSH BUTTON GROUND AND PIN 6
const int pushButton = 6;
const int relayPin = 12;
long timer = 0;
const long time2Wait = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  digitalWrite(relayPin, LOW);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int toggleState;
  toggleState = digitalRead(pushButton);
  
  if (toggleState == LOW  && timeWait(timer, time2Wait) )
  {
    digitalWrite(relayPin, HIGH);
    timer = millis();
    //countVar = count(countVar, 1);
  } 
  else if (toggleState == HIGH && timeWait(timer, time2Wait) ) 
  {
    digitalWrite(relayPin, LOW);
    timer = millis();
  }
}


bool timeWait(long timerVar, long timeToWait) {
  return millis() - timerVar > timeToWait;
}
