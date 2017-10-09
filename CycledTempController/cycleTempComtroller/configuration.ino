/*--------------------------Relay Control Variables--------------------------------*/
// Min and Max temperature settings in Degrees Fahrenheit
const float minTempSys1 = 78;
const float maxTempSys1 = 82;
const float minTempSys2 = 88;
const float maxTempSys2 = 92;
const float firstTemp = 80.0;
const float secondTemp = 90.0;
//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
const int relayAPin = 8;
const int relayBPin = 12;
const int ledPin = 13; // Used for debugging


/*--------------------------Temp Control Variables--------------------------------*/
const int sensor1 = 0; // Assigning analog pin A0 to variable 'sensor1'
const int sensor2 = 1; // Assigning analog pin A1 to variable 'sensor2'
