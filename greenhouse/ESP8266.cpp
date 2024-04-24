#include "ESP8266.h"

const char* ssid = STASSID;
const char* password = STAPSK;

//Connecting to Wi-Fi
void wifi_connect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
        delay(500);
}

//  Use API Telegram
//  Telegram Bot send text message
void tg_send_message(String message) {
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) {

        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

        // Ignore SSL certificate validation
        client->setInsecure();

        //create an HTTPClient instance
        HTTPClient https;

        //Initializing an HTTPS communication using the secure client
        String url = "https://api.telegram.org:443/bot" + String(TELEGRAM_BOT_TOKEN) + "/sendMessage";

        String chats_id[] = CHAT_ID;

        for (auto id : chats_id) {
            if (https.begin(*client, url)) {  // HTTPS

                https.addHeader("Content-Type", "application/json");

                // Создание JSON-строки с данными сообщения
                String json = "{\"chat_id\":\"" + id + "\",\"text\":\"" + message + "\"}";

                // start connection and send HTTP header
                int httpCode = https.POST(json);

                // httpCode will be negative on error
                if (httpCode > 0) {
                    // HTTP header has been send and Server response header has been handled
                    if (Serial.available())
                        Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
                }
                else
                    if (Serial.available())
                        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
                https.end();
            }
            else
                if (Serial.available())
                    Serial.printf("[HTTPS] Unable to connect\n");
        }
    }
}

void send_stat() {
    String message = "";
    message += getData();
    message += getSoilMoisture();
    message += getTemperature();
    tg_send_message(message);
}

String formatDate(String inputDate) {
  // Разделить строку по символу '/'
  int firstSlash = inputDate.indexOf('/');
  int secondSlash = inputDate.lastIndexOf('/');

  if (firstSlash == -1 || secondSlash == -1) {
    return "Invalid date format";
  }

  // Извлечь месяц, день и год
  String month = inputDate.substring(0, firstSlash);
  String day = inputDate.substring(firstSlash + 1, secondSlash);
  String year = inputDate.substring(secondSlash + 1);

  // Проверить, что длина каждого компонента корректная
  if (month.length() != 2 || day.length() != 2 || year.length() != 4) {
    return "Invalid date format";
  }

  // Сформировать новую строку в формате YYYY-MM-DD
  String formattedDate = year + "-" + month + "-" + day;
  return formattedDate;
}

String getDataTimeFromJson(String input) {
    String output = "";
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    String date = formatDate(json["date"].as<String>());

    output += String(MSG_DATE) + ": ";
    output += date;
    output += " " + json["time"].as<String>() + "\n";
    return output;
}

//  Получает текущее время часового пояса по IP-адресу
String getData() {
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) {

        String dataTime;

        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

        // Ignore SSL certificate validation
        client->setInsecure();

        //create an HTTPClient instance
        HTTPClient https;

        //Initializing an HTTPS communication using the secure client
        String url = "https://timeapi.io/api/Time/current/ip?ipAddress=" + String(LOCATION_IP);

        if (https.begin(*client, url)) {  // HTTPS

            https.addHeader("accept", "application/json");

            // Создание JSON-строки с данными сообщения
            // String json = "";

            // start connection and send HTTP header
            int httpCode = https.GET();

            // httpCode will be negative on error
            if (httpCode > 0) {
                // HTTP header has been send and Server response header has been handled
                if (Serial.available())
                    Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
                // json += https.getString();
                dataTime = getDataTimeFromJson(https.getString());
            }
            else
                if (Serial.available())
                    Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            https.end();
        }
        else
            if (Serial.available())
                Serial.printf("[HTTPS] Unable to connect\n");

        return dataTime;
    }
    return MSG_NO_CONNECTION;
}
