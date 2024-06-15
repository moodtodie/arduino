#ifndef GREENHOUSE_ESP8266_H
#define GREENHOUSE_ESP8266_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Regexp.h>
#include <ArduinoJson.h>
#include "moisture_sensor.h"
#include "DS18B20.h"
#include "config.h"

void wifi_connect();

void tg_send_message(String message, String chat_id = "");

// void tg_send_message(String message, String chats_id[]);

void send_stat(String chat_id = "");

String getData();

#endif //GREENHOUSE_ESP8266_H
