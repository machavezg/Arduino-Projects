/*
Calibration Code
Source: https://www.dfrobot.com/wiki/index.php/Capacitive_Soil_Moisture_Sensor_SKU:SEN0193#Tutorial
*/

#define SENSOR_PIN      A0
#define DELAY           100
void setup() {
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
}
void loop() {
  int val;
  val = analogRead(SENSOR_PIN); //connect sensor to Analog 0
  Serial.println(val); //print the value to serial port
  delay(DELAY);
}
