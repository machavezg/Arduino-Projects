/*
AnalogRead on particle ranges from 0 to 4095, so the values for Arduino will be different 
Pick 3 non equal values, average, and utilize the whole number as your value.
The values below are from my sensor.
Dry: 3150
Wet: 1579
Define Low Med High Moisture by Subtracting Dry from Wet and dividing by 3
High         Med        Low
0-523       523-1047    1047-1571
1579+523    1579+1047   1579+1571
1579-2102   2102-2626   2626-3150

My Threshold would be 2626
*/
#define THRESHOLD           2626 
#define SENSOR_PIN          A0 
#define TEXTING_INTERVAL    1800000 //30 minutes (1000ms * 60s * 30mins) 
int thresholdMet = false; 
unsigned long lastTextTime = 0; 
void setup() { 
   pinMode(SENSOR_PIN, INPUT); 
} 
void loop() { 
   if (analogRead(SENSOR_PIN) > THRESHOLD) { 
       thresholdMet = true; 
       unsigned long now = millis(); 
       if (now - lastTextTime >= TEXTING_INTERVAL) { 
           Particle.publish("Water Me Now!"); 
       } 
   } 
   else { 
       thresholdMet = false; 
   } 
}
