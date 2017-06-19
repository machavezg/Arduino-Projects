//Aref voltage
const float aref_voltage = 3.38;//4.80;//4.98; // tie 3.3V to ARef and measure it with a multimeter
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading
const int sensor1 = 0; // Assigning analog pin A0 to variable 'sensor1'
const int sensor2 = 1; // Assigning analog pin A1 to variable 'sensor2'
float temp = tempFahrenheit(sensor1);

//Sets up the LM35 sensor
void LM35setup(){
  pinMode(sensor1,INPUT); // Configuring pin A0 as input
  analogReference(EXTERNAL);
}

//Setup dual LM35s for reading
void LM35DualSetup(){
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  analogReference(EXTERNAL);
}

//Converts sensor data to Celsius
float tempCelsius(int sensor){
  //vout=analogRead(sensor);
  vout = cleanReading(sensor);
  vout=(vout*aref_voltage)*100;
  vout /= 1023.0;
  tempc=vout; // Storing value in Degree Celsius
  return tempc;
}
//Converts Celsius to Fahrenheit
float tempFahrenheit(int sensor){
  tempf=(tempCelsius(sensor)*1.8)+32; // Converting to Fahrenheit 
  
  return tempf;
}

/*--------------------------Smoothing software--------------------------------*/
//Source = https://www.arduino.cc/en/tutorial/smoothing
// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void cleanSetup() {
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

float cleanReading(int inputPin) {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  //Serial.println(average);
  return average;
  delay(1);        // delay in between reads for stability
}

