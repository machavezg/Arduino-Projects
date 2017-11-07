#include <Adafruit_NeoPixel.h>

extern const int sensor1; // Assigning analog pin A0 to variable 'sensor1' see tempSensor_Functions
extern const float firstTemp;
extern const float secondTemp;
extern const int sensorType;
extern const int PIXEL_PIN;    // Digital IO pin connected to the NeoPixels.
extern const int PIXEL_COUNT;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tempControlSetup(2);
  LM35setup(1);
  cleanSetup();
  doorOvenSetup();
  LCDComicSetup();
  printTempCycle();
  RGBLedSetup();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
//  heater(tempFahrenheit(sensor1), 1);
  cycleHeat( tempFahrenheit(sensor1, sensorType), 2 , firstTemp, secondTemp); //cycleHeat( temperature sensor, number of heaters, lower temp limit, upper temp limit);
  //Printing the Temp readings to LCD
  printTempFahLCD(tempFahrenheit(sensor1, sensorType));


  //Clean display reading
  //cleanReading(sensor1);
}

