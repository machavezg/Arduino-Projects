// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int StartTime = 7;
int StopTime = 18;
String DayOff_1 = "Saturday";
String DayOff_2 = "Sunday";

//Future time variables
const int futureDays    = 0;
const int futureHours   = 0;
const int futureMinutes = 0;
const int futureSeconds = 0;


void RTCSetup() {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

bool RTCPowerController() {
  DateTime now = rtc.now();
  int currentHour = now.hour();
  String dayOffWeek = daysOfTheWeek[now.dayOfTheWeek()];
  bool powerStatus;

  if ( ( currentHour >= StartTime ) && ( currentHour < StopTime ) && ( dayOffWeek != DayOff_1 ) && ( dayOffWeek != DayOff_2 ) ) {
    powerStatus = true;
  } else {
    powerStatus = false;
  }

  return powerStatus;
}

void RTCPowerControllerDebug() {
  DateTime now = rtc.now();
  DateTime future (now + TimeSpan(futureDays, futureHours, futureMinutes, futureSeconds));
  int currentHour = future.hour();
  String dayOffWeek = daysOfTheWeek[now.dayOfTheWeek()];

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(future.year(), DEC);
  Serial.print('/');
  Serial.print(future.month(), DEC);
  Serial.print('/');
  Serial.print(future.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[future.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(future.hour(), DEC);
  Serial.print(':');
  Serial.print(future.minute(), DEC);
  Serial.print(':');
  Serial.print(future.second(), DEC);
  Serial.println();
  delay(1000);
}
