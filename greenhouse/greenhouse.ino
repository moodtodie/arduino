// #include <Wire.h>
// #include <microDS3231.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>

// #define TEMPERATURE_SENSOR_PIN 2

// #define THERMAL_SENSOR_0 "ceiling"
// #define THERMAL_SENSOR_1 "window"
// #define THERMAL_SENSOR_2 "floor"

// MicroDS3231 rtc;

// OneWire ow(TEMPERATURE_SENSOR_PIN);
// DallasTemperature thermal_sensors(&ow);

#include "ESP8266.h"
#include "moisture_sensor.h"

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
    tg_send_message("Arduino is run!");

    Serial.println("----------------------------");
}

short int counter = 35;

void loop() {
    printMessage();
    counter++;
    if (counter >= 40)  //  2 min
    {
        counter = 0;
        send_message();
    }

    delay(3000);       //  3 sec
    // delay(120000);
}

void send_message() {
    String message = "";
    message += "Time: ¯\\_(ツ)_/¯ ;\n";
    message += getSoilMoisture();
    message += "Temperature: In develping...;\n";
    tg_send_message(message);
}

void printMessage() {
    Serial.println("======= Notification =======");
    // Serial.println(getData());
    Serial.print(getSoilMoisture());
    // int digital = digitalRead(2);
    // Serial.printf("Pin D2: %d;\n", digital);
    // Serial.print(getTemperature());
    Serial.println("============================");
}

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

// String getData() {
//     DateTime dt = rtc.getTime();
//     return "[" + String(dt.year) + "-" + String(dt.month) + "-" + String(dt.date) + " " + String(dt.hour) + ":" + String(dt.minute) + ":" + String(dt.second) + "] ";
// }
