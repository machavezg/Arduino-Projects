//AnalogRead on particle ranges from 0 to 4095, so the values for Arduino will be different 
#define THRESHOLD           3000 
#define SENSOR_PIN          A0 
#define LIGHT_PIN           7 
#define BUZZER_PIN          6 
#define TEXTING_INTERVAL    1800000 //30 minutes (1000ms * 60s * 30mins) 
int buzzerOn = 0; 
int thresholdMet = false; 
unsigned long lastTextTime = 0; 
void setup() { 
   pinMode(SENSOR_PIN, INPUT); 
   pinMode(LIGHT_PIN, OUTPUT); 
   pinMode(BUZZER_PIN, OUTPUT); 
} 
void loop() { 
   if (analogRead(SENSOR_PIN) > THRESHOLD) { 
       thresholdMet = true; 
       digitalWrite(LIGHT_PIN, HIGH); 
       digitalWrite(BUZZER_PIN, HIGH); 
       unsigned long now = millis(); 
       if (now - lastTextTime >= TEXTING_INTERVAL) { 
           Particle.publish("Water Me Now!"); 
       } 
   } 
   else { 
       thresholdMet = false; 
       digitalWrite(LIGHT_PIN, LOW); 
       digitalWrite(BUZZER_PIN, LOW); 
   } 
}  
