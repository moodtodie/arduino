#include "config.h"
#include "ESP8266.h"
#include "moisture_sensor.h"
#include "DS18B20.h"

void leds_on(){
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
}

void leds_off(){
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void setup() {
    Serial.begin(115200);

    Serial.println(MSG_SOURCE);
    Serial.println(MSG_HEADER);

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    leds_on();
    delay(200);   //  0,5s
    leds_off();
    delay(500);  //  1s
    leds_on();
    delay(200);   //  0,5s
    leds_off();
    delay(500);  //  1s
    leds_on();
    delay(200);   //  0,5s
    leds_off();

    digitalWrite(GREEN_LED, LOW);
   
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
    
    digitalWrite(GREEN_LED, HIGH);

//    pinMode(12, OUTPUT);
    // pinMode(GREEN_LED, OUTPUT);
    leds_off();
}

auto counter = FREQUENCY;

void loop() {
    digitalWrite(RED_LED, HIGH);
    printMessage();

    counter++;
    // tg_send_message("counter: " + String(counter));
    // tg_send_message("max: " + String(getMaxTemperature()));
    // tg_send_message("limit: " + String(getTLimit()));
    if ((getTLimit() == getMaxTemperature()) || (counter >= FREQUENCY)) {
        digitalWrite(GREEN_LED, HIGH);
        counter = 0;
        send_message(); //  FREQUENCY * 5 min
        digitalWrite(GREEN_LED, LOW);
    }

    Serial.println("GET Update: " + tg_getUpdates());

    // if (counter % 10 == 0) {
        digitalWrite(RED_LED, LOW);
    // }
    
    delay(500);
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
