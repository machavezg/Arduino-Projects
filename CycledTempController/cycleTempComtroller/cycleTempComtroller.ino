

extern const int sensor1; // Assigning analog pin A0 to variable 'sensor1' see tempSensor_Functions
extern const float firstTemp;
extern const float secondTemp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tempControlSetup(1);
  LM35setup(1);
  cleanSetup();
  doorOvenSetup();
  LCDComicSetup();
  printTempCycle();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
//  heater(tempFahrenheit(sensor1), 1);
  cycleHeat( tempFahrenheit(sensor1), 1 , firstTemp, secondTemp);
  //Printing the Temp readings to LCD
  printTempFahLCD(tempFahrenheit(sensor1));


  //Clean display reading
  //cleanReading(sensor1);
}

