#include "config.h"
#include "ESP8266.h"
#include "moisture_sensor.h"
#include "DS18B20.h"

void setup() {
    Serial.begin(115200);

    Serial.println(MSG_SOURCE);
    Serial.println(MSG_HEADER);

    Serial.print(MSG_CONNECTING_TO);
    Serial.print(STASSID);
    Serial.print("...\n");
    wifi_connect();
    Serial.println(MSG_CONNECTED);


    String telegram_message = TG_HEADER;
    telegram_message += TG_COUNT_TERAL_SENSORS;

    init_thermal_sensors();

    int sensorsCount = getThermalSensorsCount();
    if (sensorsCount > 0) {
        Serial.print(MSG_FOUND_TERAL_SENSORS_PT_1);
        Serial.print(sensorsCount);
        Serial.println(MSG_FOUND_TERAL_SENSORS_PT_2);

        telegram_message += String(sensorsCount) + "\n";
    }
    else {
        Serial.println(MSG_TERAL_SENSORS_NOT_FOUND);
    }

    tg_send_message(telegram_message);

    Serial.println(MSG_FOOTER);
}

auto counter = FREQUENCY;

void loop() {
    printMessage();

    counter++;
    if (counter >= FREQUENCY) {
        counter = 0;
        send_message(); //  FREQUENCY * 5 min
    }
    delay(300000);      //  5 min
}

void send_message() {
    Serial.println(MSG_SEND_TG_MESSAGE);
    String message = "";
    message += getData();
    message += getSoilMoisture();
    message += getTemperature();
    tg_send_message(message);
}

void printMessage() {
    Serial.println("======= Notification =======");
    Serial.print(getData());
    Serial.print(getSoilMoisture());
    Serial.print(getTemperature());
    Serial.println("============================\n");
}
