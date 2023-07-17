#include "ESP8266.h"
#include "moisture_sensor.h"
#include "DS18B20.h"

void setup() {
    Serial.begin(115200);

    Serial.println("Source: https://github.com/moodtodie/arduino/tree/main/greenhouse");
    Serial.println("-------Arduino-is-run-------");

    wifi_connect();

    String telegram_message = "Arduino WeNos D1 R1 is run!\n"
        "Termal sensors: ";

    init_thermal_sensors();

    int sensorsCount = getThermalSensorsCount();
    if (sensorsCount > 0) {
        Serial.print("Found ");
        Serial.print(sensorsCount);
        Serial.println(" temperature sensors");

        telegram_message += String(sensorsCount) + "\n";
    }
    else {
        Serial.println("Temperature sensors NOT found");
    }

    tg_send_message(telegram_message);

    Serial.println("----------------------------");
}

short int counter = 11;

void loop() {
    printMessage();

    counter++;
    if (counter >= 12)  //  1 hourse
    {
        counter = 0;
        send_message();
    }
    // delay(300000);      //  5 min
    delay(10000);      //  10 sec
}

void send_message() {
    Serial.println("*Telegram send message*");
    String message = "";
    message += "Time: ¯\\_(ツ)_/¯ ;\n";
    message += getSoilMoisture();
    message += getTemperature();
    tg_send_message(message);
}

void printMessage() {
    Serial.println("======= Notification =======");
    // Serial.println(getData());
    Serial.print(getSoilMoisture());
    Serial.print(getTemperature());
    Serial.println("============================\n");
}

// String getData() {
//     DateTime dt = rtc.getTime();
//     return "[" + String(dt.year) + "-" + String(dt.month) + "-" + String(dt.date) + " " + String(dt.hour) + ":" + String(dt.minute) + ":" + String(dt.second) + "] ";
// }
