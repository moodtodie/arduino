#ifndef GREENHOUSE_TG_LISTENER_H
#define GREENHOUSE_TG_LISTENER_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "config.h"
#include "ESP8266.h"

String tg_getUpdates();

#endif //GREENHOUSE_TG_LISTENER_H
