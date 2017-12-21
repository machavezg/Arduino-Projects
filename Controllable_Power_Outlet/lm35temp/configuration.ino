/*--------------------------Relay Control Variables--------------------------------*/
// Min and Max temperature settings in Degrees Fahrenheit
const float minTemp = 118;
const float maxTemp = 123;
//The pins that will be controlling the relay
//Pin 13 ledPin is for debugging purposes only
const int relayAPin = 8;
const int relayBPin = 9;
const int relayBPin = 10;
const int ledPin = 13; // Used for debugging


/*--------------------------Temp Control Variables--------------------------------*/
const float aref_voltage = 3.29;//3.43; //3.38;//4.80;//4.98; // tie 3.3V to ARef and measure it with a multimeter

const int sensor1 = 0; // Assigning analog pin A0 to variable 'sensor1'
const int sensor2 = 1; // Assigning analog pin A1 to variable 'sensor2'

/*Define the type of sensor that is being used to measure the temperature
 * Type 1: LM35
 * Type 2: TMP36
*/

const int sensorType = 2; //

//Number of heaters to control
const int heatersToControl = 1; //enter 1 or 2

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

