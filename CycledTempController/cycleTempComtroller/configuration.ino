/*--------------------------Relay Control Variables--------------------------------*/
// Min and Max temperature settings in Degrees Fahrenheit
const float firstTemp = 100.0;
const float secondTemp = 120.0;

const float minTempSys1 = firstTemp - 2.0;
const float maxTempSys1 = firstTemp + 3.0;

const float minTempSys2 = secondTemp - 2.0;
const float maxTempSys2 = secondTemp + 3.0;

//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
const int relayAPin = 8;
const int relayBPin = 12;
const int ledPin = 13; // Used for debugging


/*--------------------------Temp Control Variables--------------------------------*/
const int sensor1 = 0; // Assigning analog pin A0 to variable 'sensor1'
const int sensor2 = 1; // Assigning analog pin A1 to variable 'sensor2'


/*--------------------------Cycle Controller Variables--------------------------------*/
const long heatPhase1 = 5400000; //90 minutes to milliseconds 5400000
const long heatPhase2 = 7200000; //120 minutes to milliseconds 7200000

const int led1pin = 6;
const int led2pin = 7;
