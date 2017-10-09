extern const int temp1pin;
extern const int temp2pin;
extern const int sensor1; // Assigning analog pin A0 to variable 'sensor1' see tempSensor_Functions

void setup() {
  // put your setup code here, to run once:
  tempControlSetup(1);
  LM35setup(1);
  cleanSetup();
  Serial.begin(9600);
  pinMode(temp1pin, OUTPUT);
  pinMode(temp2pin, OUTPUT);
  digitalWrite(temp1pin, HIGH);
  digitalWrite(temp2pin, HIGH);
  delay(2000);
  digitalWrite(temp1pin, LOW);
  digitalWrite(temp2pin, LOW);
  LCDComicSetup();
  printTempCycle();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
//  heater(tempFahrenheit(sensor1), 1);
  cycleHeat( tempFahrenheit(sensor1), 1 , 80.0 , 90.0);
  //Printing the Temp readings to LCD
  printTempFahLCD(tempFahrenheit(sensor1));


  //Clean display reading
  //cleanReading(sensor1);
}

