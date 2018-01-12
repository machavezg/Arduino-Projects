Solar Powered Particle Photon Soil Moisture Alarm
---------------------------------------

**Introduction**

For a while I've had a small solar panel, rechargeable battery and a solar battery charger sitting at my desk. After a month of having bought a basil plant, I've decided to create a notification system that will automatically notify me once my plant needs water. After searching around for a similar projects, I found [this example](https://www.hackster.io/AlexWulff/annoying-soil-moisture-sensor-with-photon-and-ifttt-549222). I've decided to use some of the hardware components in that project along with the components I've had lying around.

**Hardware Components**

1. [Particle Photon](https://www.adafruit.com/product/2721)
2. [Gravity: Analog Capacitive Soil Moisture Sensor- Corrosion Resistant](http://a.co/cACKNFt) or [Here](https://www.dfrobot.com/product-1385.html)
3. [Large 6V 3.5W Solar panel - 3.5 Watt](https://www.adafruit.com/product/500)
4. [USB / DC / Solar Lithium Ion/Polymer charger - v2](https://www.adafruit.com/product/390)
5. [Lithium Ion Polymer Battery - 3.7v 2500mAh](https://www.adafruit.com/product/328)
6. [USB cable - A/MicroB - 3ft](https://www.adafruit.com/product/592)
7. [Tiny breadboard](https://www.adafruit.com/product/65)

**Wiring**

![schematic](https://github.com/machavezg9/RPi-Arduino-Projects/blob/master/Soil%20Moisture%20Sensor/images/schematic.png)

**Instructions**

1. Wire everything according to the schematic above.

2. Run the [calibration](Calibration/moistureSensorV1.ino) code to obtain your 'Dry Condition' value and your 'Wet Condition' value and record that.

- Dry Condition
![Dry Condition](https://github.com/machavezg9/RPi-Arduino-Projects/blob/master/Soil%20Moisture%20Sensor/images/dry.png)
- Wet Condition
![Wet Condition](https://github.com/machavezg9/RPi-Arduino-Projects/blob/master/Soil%20Moisture%20Sensor/images/wet.png)
- Make note of your Dry and Wet condition values, subtract Dry-Wet to get your range, divide the result by 3 and subtract that result from your Dry condition to obtain your threshold. See below:

https://community.particle.io/t/serial-tutorial/26946

https://www.dfrobot.com/product-1385.html

***PENDING CONTINUATION***
