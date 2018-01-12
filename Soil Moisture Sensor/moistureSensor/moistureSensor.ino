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

const int           threshold       = 2626;
const unsigned long textingInterval = 1800000;//30 minutes (1000ms * 60s * 30mins)
const unsigned long timeDelay       = 1000;
unsigned long       lastTextTime    = 0;
unsigned long       waitDelay       = 0;
bool                textSent        = false;


//Returns false as long as the time you need to wait has not passed
bool timeWait(unsigned long timerVar, unsigned long timeToWait) {
  return millis() - timerVar > timeToWait;
}

void setup() { 
    pinMode(SENSOR_PIN, INPUT);
    Serial.begin(9600);
    
} 
void loop() { 
    int moistureLevel = analogRead(SENSOR_PIN);
    if(moistureLevel > threshold && textSent == false && timeWait(waitDelay, timeDelay)  ) 
    {
        Spark.publish("moistureState","dry",60,PRIVATE);
        textSent = true;
        lastTextTime = millis();
        waitDelay = millis();
        Serial.println("1st message Sent");
        Serial.println(moistureLevel);
    } 
    else if(moistureLevel > threshold && textSent == true && timeWait(waitDelay, timeDelay) && timeWait(lastTextTime,textingInterval) )
    { 
      Spark.publish("moistureState","dry",60,PRIVATE);
      lastTextTime = millis();
      waitDelay = millis();
      Serial.println("sent message again");
      Serial.println(moistureLevel);
    }
    else
    {
        if (  moistureLevel < threshold && timeWait(waitDelay, timeDelay) ) {
          textSent = false;
          Serial.println("else 2");
          Serial.println(moistureLevel);
          waitDelay = millis();
        } else {
          if ( timeWait(waitDelay, timeDelay ) ) {
            Serial.println("else");
            Serial.println(moistureLevel);
            waitDelay = millis();
          }
        }
    }
}
