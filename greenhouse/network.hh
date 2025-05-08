#ifndef GREENHOUSE_NETWORK_H
#define GREENHOUSE_NETWORK_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

#include "config.h"
#include "service.hh"
#include "sensors.hh"


void wifi_connect();
void post_request(String url, String json_data);
String get_request(String url);
void send_stat(String chat_id = "");

#endif //GREENHOUSE_NETWORK_H
