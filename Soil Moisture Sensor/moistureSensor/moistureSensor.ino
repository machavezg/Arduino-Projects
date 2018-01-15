/*
AnalogRead on particle ranges from 0 to 4095, so the values for Arduino will be different 
Pick 3 non equal values, average, and utilize the whole number as your value.
The values below are from my sensor.
Dry: 3150
Wet: 1579
Define Low Med High Moisture by Subtracting Dry from Wet and dividing by 3
Particle
High         Med        Low
0-523       523-1047    1047-1571
1579+523    1579+1047   1579+1571
1579-2102   2102-2626   2626-3150
My Threshold would be 2626

Arduino
Dry: 544
Wet: 270
High         Med        Low
0-91         91-182     182-274
270+91       270+182    270+274
270-361      361-452    452-544
My Threshold would be 452
*/
#define SENSOR_PIN                    A0

const int           dry             = 3150; //enter your measured value in dry condition
const int           wet             = 1579; //enter your measured value in wet condition
const int           threshold       = calcThreshold(dry, wet); //no need to do anything
const unsigned long textingInterval = 1800000;//30 minutes (1000ms * 60s * 30mins)
const unsigned long timeDelay       = 1000;
unsigned long       lastTextTime    = 0;
unsigned long       waitDelay       = 0;
bool                textSent        = false;


//Returns false as long as the time you need to wait has not passed
bool timeWait(unsigned long timerVar, unsigned long timeToWait) {
  return millis() - timerVar > timeToWait;
}

int calcThreshold(int dry, int wet)  {
    int threshold = dry - ( ( dry - wet ) / 3 );
    return threshold;
}

void setup() { 
    pinMode(SENSOR_PIN, INPUT);
} 
void loop() { 
    int moistureLevel = analogRead(SENSOR_PIN);
    if( moistureLevel > threshold && textSent == false && timeWait(waitDelay, timeDelay)  ) {
        Spark.publish("moistureState","dry",60,PRIVATE);
        textSent = true;
        lastTextTime = millis();
        waitDelay = millis();
    } else if( moistureLevel > threshold && textSent == true && timeWait(waitDelay, timeDelay) && timeWait(lastTextTime,textingInterval) ) { 
        Spark.publish("moistureState","dry",60,PRIVATE);
        lastTextTime = millis();
        waitDelay = millis();
    } else {
        if (  moistureLevel < threshold && timeWait(waitDelay, timeDelay) ) {
          textSent = false;
          waitDelay = millis();
        } else {
            if ( timeWait(waitDelay, timeDelay ) ) {
                waitDelay = millis();
            }
        }
    }
}
