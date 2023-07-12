// #include <Wire.h>
// #include <microDS3231.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>

// #define AIR_MOISTURE_VALUE 620
// #define WATER_MOISTURE_VALUE 336
// #define MOISTURE_SENSOR_PIN A0
// #define TEMPERATURE_SENSOR_PIN 2

// #define THERMAL_SENSOR_0 "ceiling"
// #define THERMAL_SENSOR_1 "window"
// #define THERMAL_SENSOR_2 "floor"

// MicroDS3231 rtc;

// OneWire ow(TEMPERATURE_SENSOR_PIN);
// DallasTemperature thermal_sensors(&ow);

// int soilMoistureValue = 0;      //  влажность почвы
// int soilMoisturePercent = 0;    //  процент влажности почвы

#include "ESP8266.h"

void setup() {
//    pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
    Serial.begin(115200);
    // Wire.begin();

    Serial.println("Source: https://github.com/moodtodie/arduino/tree/main/greenhouse");
    Serial.println("-------Arduino-is-run-------");
    
    // if (!rtc.begin())       // проверка наличия модуля на линии i2c
    //     Serial.println("Error: RTC module NOT found.");
    // else
    //     Serial.println("RTC module found");

    // thermal_sensors.begin();
    // Serial.print("Found ");
    // Serial.print(thermal_sensors.getDeviceCount());
    // Serial.println(" temperature sensors");

    wifi_connect();

    Serial.println("----------------------------");
}

void loop() {
    // printMessage();
    tg_send_message("Hi, Admin!");
    delay(120000);
}

// void printMessage() {
//     Serial.println("======= Notification =======");
//     Serial.println(getData());
//     Serial.print(getSoilMoisture());
//     Serial.print(getTemperature());
//     Serial.println("============================");
// }

// String getTemperature() {
//     // Send the command for all devices on the bus to perform a temperature conversion:
//     thermal_sensors.requestTemperatures();
//     String message = "";
//     for (int i = 0; i < thermal_sensors.getDeviceCount(); i++)
//     {
//         // Fetch the temperature in degrees Celsius for device index:
//         float tempC = thermal_sensors.getTempCByIndex(i); // the index 0 refers to the first device

//         // Print the temperature in Celsius in the Serial Monitor:
//         message += "Temperature ";
//         switch (i)
//         {
//         case 0:
//             message += THERMAL_SENSOR_0;
//             break;
//         case 1:
//             message += THERMAL_SENSOR_1;
//             break;
//         case 2:
//             message += THERMAL_SENSOR_2;
//             break;
//         default:
//             message += "sensor #" + String(i + 1);
//             break;
//         }
//         message += ": " + String(tempC) + " \xC2\xB0" + "C\n";
//     }
//     return message;
// }

// String getSoilMoisture() {
//     soilMoistureValue = analogRead(MOISTURE_SENSOR_PIN);
//     String message = "";
//     message += "Moisture sensor value: " + String(soilMoistureValue) + "\n";   //  Показывает значение датчика
//     message += "Relative soil moisture: ";  //  Отнасительная влажность
//     soilMoisturePercent = map(soilMoistureValue, AIR_MOISTURE_VALUE, WATER_MOISTURE_VALUE, 0, 100);

//     if (soilMoisturePercent >= 100)
//         message += "100";
//     else if (soilMoisturePercent <= 0)
//         message += "0";
//     else if (soilMoisturePercent > 0 && soilMoisturePercent < 100)
//         message += String(soilMoisturePercent);

//     message += " %\n";
//     return message;
// }

// String getData() {
//     DateTime dt = rtc.getTime();
//     return "[" + String(dt.year) + "-" + String(dt.month) + "-" + String(dt.date) + " " + String(dt.hour) + ":" + String(dt.minute) + ":" + String(dt.second) + "] ";
// }
