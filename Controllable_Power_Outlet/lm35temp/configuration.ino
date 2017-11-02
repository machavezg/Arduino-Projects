/*--------------------------Relay Control Variables--------------------------------*/
// Min and Max temperature settings in Degrees Fahrenheit
const float minTemp = 78;
const float maxTemp = 82;
//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
const int relayAPin = 8;
const int relayBPin = 12;
const int ledPin = 13; // Used for debugging


/*--------------------------Temp Control Variables--------------------------------*/
const int sensor1 = 0; // Assigning analog pin A0 to variable 'sensor1'
const int sensor2 = 1; // Assigning analog pin A1 to variable 'sensor2'

/*--------------------------Timer Control Variables--------------------------------*/
//0-24 Military Time
int heaterStartTime = 7; 
int heaterStopTime = 18;
//
String heaterDayOff_1 = "Saturday";
String heaterDayOff_2 = "Sunday";

/*--------------------------Temp Cycle Variables--------------------------------*/
//Time variables
String adhesiveType = "1508WHITE";


/*--------------------------LED Variables--------------------------------*/
bool indicatorLED = false;
const int PIXEL_PIN = 7;    // Digital IO pin connected to the NeoPixels.
const int PIXEL_COUNT = 1;

