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

        if (https.begin(*client, url)) {  // HTTPS

            https.addHeader("Content-Type", "application/json");

            // Создание JSON-строки с данными сообщения
            String json = "{\"chat_id\":\"" + String(CHAT_ID) + "\",\"text\":\"" + message + "\"}";

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

String getData(){
    return TG_TIME;
};
