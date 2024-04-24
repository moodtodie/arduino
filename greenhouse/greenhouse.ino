#include "config.h"
#include "ESP8266.h"
#include "moisture_sensor.h"
#include "DS18B20.h"
#include "tg_listener.h"

void setup() {
    Serial.begin(115200);

    Serial.println(MSG_SOURCE);
    Serial.println(MSG_HEADER);

    Serial.print("\n " + String(MSG_CONNECTING_TO) + " ");
    Serial.print(STASSID);
    Serial.print("...\n");
    wifi_connect();
    Serial.println(MSG_CONNECTED);

    String telegram_message = String(TG_HEADER) + "\n";
    telegram_message += String(TG_COUNT_TERAL_SENSORS) + ": ";

    init_thermal_sensors();

    int sensorsCount = getThermalSensorsCount();
    if (sensorsCount > 0) {
        Serial.print(String(MSG_FOUND_TERAL_SENSORS_PT_1) + " ");
        Serial.print(sensorsCount);
        Serial.println(" " + String(MSG_FOUND_TERAL_SENSORS_PT_2));

        telegram_message += String(sensorsCount) + "\n";
    } else {
        Serial.println(MSG_TERAL_SENSORS_NOT_FOUND);
    }

    tg_send_message(telegram_message);

    Serial.println(MSG_FOOTER);
    send_stat();
}

unsigned long previousMillis = 0;
unsigned long previousLimitMillis = 0;
const long interval = 1000 * 60;  //  1 min

void loop() {
    unsigned long currentMillis = millis();
    Serial.println("GET Update: " + tg_get_updates());

    if (currentMillis - previousMillis >= (interval * FREQUENCY)) {
        previousMillis = currentMillis;

        // Выполняем функцию в "отдельном потоке"
        // printMessage(); //  Debug
        Serial.println("GET Update: " + tg_get_updates());
        Serial.println(MSG_SEND_TG_MESSAGE);
        send_stat(); //  FREQUENCY * 5 min
    }

    if (currentMillis - previousLimitMillis >= (interval * 25)) {
        if (!check_limits()) {
            previousLimitMillis = currentMillis;
            send_stat();
        }
    }
    // delay(250); // Debug
}

void printMessage() {
    Serial.println("======= Notification =======");
    Serial.print(getData());
    Serial.print(getSoilMoisture());
    Serial.print(getTemperature());
    Serial.println("============================\n");
}
