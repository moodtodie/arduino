#ifndef GREENHOUSE_CONFIG_H
#define GREENHOUSE_CONFIG_H

#include "lang/ru.h"
#include <Arduino.h>

//  Параметры для Wi-Fi модуля
#define STASSID "your_SSID"   //  Название Wi-Fi сети
#define STAPSK "your_password"   //  Пароль от Wi-Fi сети
#define LOCATION_IP "your_IP"   //  IP-адрес, для которого будет получено текущее время
#define FREQUENCY N         // Периодичность уведомлений (N * 5 min)

//  Настройка API Telegram
#define TELEGRAM_BOT_TOKEN "your_token"
#define CHAT_ID {"your_chat_id"}    //  Single
// #define CHAT_ID {"chat_id_1", "chat_id_2"}  //  Multi

//  Настройка датчика влажности
#define AIR_MOISTURE_VALUE 856      //  Значение датчика в воздухе
#define WATER_MOISTURE_VALUE 488    //  Значение датчика в воде
#define MOISTURE_SENSOR_PIN A0      //  Пин (аналоговый)

//  Настройка датчика температуры
#define TEMPERATURE_SENSOR_PIN 4    //  Пин (цифровой)
#define THERMAL_SENSOR_0 "name_1"   //  Имя термо-датчика №1
#define THERMAL_SENSOR_1 "name_2"   //  Имя термо-датчика №2
#define THERMAL_SENSOR_2 "name_3"    //  Имя термо-датчика №3

#endif //GREENHOUSE_CONFIG_H
