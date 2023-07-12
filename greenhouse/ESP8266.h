#ifndef GREENHOUSE_ESP8266_H
#define GREENHOUSE_ESP8266_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "config.h"

void wifi_connect();

void tg_send_message(String message);

#endif //GREENHOUSE_ESP8266_H
