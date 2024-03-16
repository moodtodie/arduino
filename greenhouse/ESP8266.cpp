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


int getUpdateIdFromJson(String input) {
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    String output = json["update_id"].as<String>();
    return output.toInt();
}

String getTextFromJson(String input, String text) {
    String output = "";
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    output = json[text].as<String>();
    return output;
}

void splitCommand(const String& input, String& firstPart, String& secondPart) {
    // Находим позицию пробела
    int spaceIndex = input.indexOf(' ');

    // Если пробел найден, разделяем строку
    if (spaceIndex != -1) {
        // Выделяем первую часть до пробела
        firstPart = input.substring(0, spaceIndex);
        // Выделяем вторую часть после пробела
        secondPart = input.substring(spaceIndex + 1);
    }
    else {
        // Если пробел не найден, первая часть равна всей строке, а вторая часть - пустая
        firstPart = input;
        secondPart = "";
    }
}

void executeCommand(String command) {
    String cmd, value;
    splitCommand(command, cmd, value);

    if (cmd.equals("/setlimit")) {
        setTLimit(value.toInt());
        tg_send_message("Установлена новое значение температуры: " + getTLimit());
    }
    else if (cmd.equals("/setairval")) {
        setAirMoisture(value.toInt());
    }
    else if (cmd.equals("/setwaterval")) {
        setWaterMoisture(value.toInt());
    }
    else if (cmd.equals("/show")) {
        String message = "";
        message += getData();
        message += getSoilMoisture();
        message += getTemperature();
        tg_send_message(message);
    }
    else if (cmd.equals("/info")) {
        tg_send_message("/setlimit [знач.] - Что бы установить новый лимит температуры;\n/setairval [знач.] - Что бы значение датчика влажности в воздухе;\n/setwaterval [знач.] - Что бы значение датчика влажности в воде;\n/show - Что бы узнать параметры;\n/info - Что бы увидить это меню");
    }
    else if (cmd.equals("/add")) {
        //  In progress...
    }
    else if (cmd.equals("/delete")) {
        //  In progress...
    }
    else {
        // String s = "command: ";
        // s += command;
        // s += "\ncmd: ";
        // s += cmd;
        // s += "\nval: ";
        // s += value;
        // tg_send_message(s);
    }
}

int id = 0;

//  Use API Telegram
//  Telegram Bot get updates
String tg_getUpdates() {
    // wait for WiFi connection
    String payload = "clear";
    if ((WiFi.status() == WL_CONNECTED)) {

        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

        // Ignore SSL certificate validation
        client->setInsecure();

        //create an HTTPClient instance
        HTTPClient https;

        //Initializing an HTTPS communication using the secure client
        String url = "https://api.telegram.org:443/bot" + String(TELEGRAM_BOT_TOKEN) + "/getUpdates?offset=" + String(id);

        if (https.begin(*client, url)) {  // HTTPS

            // start connection and send HTTP header
            int httpCode = https.GET();

            // httpCode will be negative on error
            if (httpCode > 0) {
                payload = https.getString();
            }
            else
                payload = "[HTTPS] POST... failed";
            https.end();
        }
        else
            payload = "[HTTPS] Unable to connect";
    }

    String tmp = getTextFromJson(payload, "result");
    payload = tmp.substring(1, tmp.length() - 1);
    id = getUpdateIdFromJson(payload);

    tmp = getTextFromJson(payload, "message");
    String command = getTextFromJson(tmp, "text");

    if (id != 0) {
        id += 1;
        executeCommand(command);
    }

    return command;
}

String getDataTimeFromJson(String input) {
    String output = "";
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    output += MSG_DATE + json["date"].as<String>() + "\n";
    output += MSG_TIME + json["time"].as<String>() + "\n";
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
