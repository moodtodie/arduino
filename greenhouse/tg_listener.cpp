#include "tg_listener.h"

int id = 0;

String getTextFromJson(String input, String text) {
    String output = "";
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    output = json[text].as<String>();
    return output;
}

int getUpdateIdFromJson(String input) {
    DynamicJsonDocument json(1024);

    deserializeJson(json, input);

    String output = json["update_id"].as<String>();
    return output.toInt();
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
    } else {
        // Если пробел не найден, первая часть равна всей строке, а вторая часть - пустая
        firstPart = input;
        secondPart = "";
    }
}

void executeCommand(String command) {
    String cmd, value;
    splitCommand(command, cmd, value);


    if (cmd.equals("/info")) {
        tg_send_message("/setlimit [знач.] - Что бы установить новый лимит температуры;\n/setairval [знач.] - Что бы значение датчика влажности в воздухе;\n/setwaterval [знач.] - Что бы значение датчика влажности в воде;\n/show - Что бы узнать параметры;\n/info - Что бы увидить это меню");
    } else if (cmd.equals("/setlimit")) {
        // setTLimit(value.toInt());
        tg_send_message("In development...");
        // tg_send_message("Установлена новое значение температуры: " + getTLimit());
    } else if (cmd.equals("/setairval")) {
        tg_send_message("In development...");
        // setAirMoisture(value.toInt());
    } else if (cmd.equals("/setwaterval")) {
        tg_send_message("In development...");
        // setWaterMoisture(value.toInt());
    } else if (cmd.equals("/show")) {
        // String message = "";
        // message += getData();
        // message += getSoilMoisture();
        // message += getTemperature();
        tg_send_message("In development...");
    } else if (cmd.equals("/add")) {
        //  In progress...
    } else if (cmd.equals("/delete")) {
        //  In progress...
    } else {
        String s = "command: ";
        // s += command;
        // s += "\ncmd: ";
        // s += cmd;
        // s += "\nval: ";
        // s += value;
        tg_send_message(s);
    }
}

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