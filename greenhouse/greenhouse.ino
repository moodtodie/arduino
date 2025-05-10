#include "config.h"
#include "network.hh"
#include "telegram.hh"
#include "limits.hh"
#include "sensors.hh"

void setup() {
    Serial.begin(115200);

    Serial.println(MSG_SOURCE);
    Serial.println(MSG_HEADER);

    pinMode(RELAY_PIN, OUTPUT);
    relayOff();

    setMaxTemperature(MAX_TEMPERATURE_VALUE);
    setMinTemperature(MIN_TEMPERATURE_VALUE);
    setAirMoisture(AIR_MOISTURE_VALUE);
    setWaterMoisture(WATER_MOISTURE_VALUE);
    setRelayOnTemperature(RELAY_ON_TEMPERATURE_VALUE);
    setRelayOffTemperature(RELAY_OFF_TEMPERATURE_VALUE);

    Serial.println("\nThe limits are set up");

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
    check_limits();
    send_stat();
}

unsigned long previousMillis = 0;
unsigned long previousLimitMillis = 0;
const long interval = 1000 * 60;  //  1 min

void loop() {
    unsigned long currentMillis = millis();

    String updates = tg_get_updates();
    if (updates != "null")
        Serial.println("GET Update: " + updates);

    if (abs((long long) (currentMillis - previousMillis)) >= (interval * FREQUENCY)) {
        previousMillis = currentMillis;

        // Выполняем функцию в "отдельном потоке"
        String updates = tg_get_updates();
        if (updates != "null")
            Serial.println("GET Update: " + updates);
        Serial.println(MSG_SEND_TG_MESSAGE);
        send_stat();
    }

    check_relay_limits();

    if (abs((long long) (currentMillis - previousLimitMillis)) >= (interval * 30)) {
        if (!check_limits()) {
            previousLimitMillis = currentMillis;
            send_stat();
        }
    }
}
