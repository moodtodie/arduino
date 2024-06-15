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

void extractValues(String input, String &val1, String &val2, String &val3) {
  // Разделение строки на подстроки по пробелу
  int spaceIndex1 = input.indexOf(' ');
  int spaceIndex2 = input.indexOf(' ', spaceIndex1 + 1);

  // Если найдены все три пробела, извлекаем подстроки
  if (spaceIndex1 != -1 && spaceIndex2 != -1) {
    val1 = input.substring(0, spaceIndex1);
    val2 = input.substring(spaceIndex1 + 1, spaceIndex2);
    val3 = input.substring(spaceIndex2 + 1);
  } else {
    // Вывод сообщения об ошибке, если не удалось найти все три значения
    Serial.println(ERR_MSG_FAILED_TO_EXTRACT_VALUES);
  }
}

void handle_set_limit_command(String type, String param, String val){
    if (type == "t") {
        auto value = val.toFloat();

        if (param == "max") {
            setMaxTemperature(value); 
        } else if (param == "min") {
            setMinTemperature(value);
        } else {
            tg_send_message(TG_UNKNOWN_PARAMETER);
            return;
        }
    } else if (type == "m") {
        auto value = val.toInt();
        
        if (param == "max") {
            setWaterMoisture(value);
            return; 
        } else if (param == "min") {
            setAirMoisture(value);
        } else {
            tg_send_message(TG_UNKNOWN_PARAMETER);
            return;
        }
    } else {
        tg_send_message(TG_UNKNOWN_TYPE);
        return;
    }
    tg_send_message(TG_SUCCESSFULLY_MODIFIED);
}

void executeCommand(String command, String chat_id = "") {
    String cmd, value;
    splitCommand(command, cmd, value);

    String message = "";
    
    if (cmd.equals("/info")) {
        message = "/setlimit [type] [param] [value] - " + String(TG_DESC_TO_SET_NEW_LIMITS) + "\n";
        message += " type:\n";
        message += "  t - " + String(TG_DESC_TYPE_TEMPERATURE) + "\n";
        message += "  m - " + String(TG_DESC_TYPE_MOISTURE) + "\n";
        message += " param:\n";
        message += "  max - " + String(TG_DESC_UPPER_LIMIT) + "\n";
        message += "  min - " + String(TG_DESC_LOWER_LIMIT) + "\n";
        message += "/show - " + String(TG_DESC_TO_PRINT_PARAMETERS) + "\n";
        message += "/limits - " + String(TG_DESC_TO_PRINT_LIMITS) + "\n";
        message += "/info - " + String(TG_DESC_TO_PRINT_THIS_MESSAGE) + "\n";
    } else if (cmd.equals("/setlimit")) {
        String type, param, val;
        extractValues(value, type, param, val);
        handle_set_limit_command(type, param, val);
    } else if (cmd.equals("/show")) {
        send_stat(chat_id);
    } else if (cmd.equals("/limits")) {
        message = String(TG_LIMITATIONS) + ":\n";
        message += String(TG_MAX_TEMPERATURE) + ": " + String(getMaxTemperature()) +  "\n";
        message += String(TG_MIN_TEMPERATURE) + ": " + String(getMinTemperature()) + "\n";
        message += String(TG_AIR_MOISTURE) + ": " + String(getAirMoisture()) + "\n";
        message += String(TG_WATER_MOISTURE) + ": " + String(getWaterMoisture()) + "\n";
    } else {
        message = String(TG_UNKNOWN_COMMAND) + ": ";
        message += cmd;
        // DEBUG
        // message = "max: ";
        // message += getMaxTemperatureOnSensors();
        // message += "\nmin: ";
        // message += getMinTemperatureOnSensors();
    }
    tg_send_message(message, chat_id);
}

//  Use API Telegram
//  Telegram Bot get updates
String tg_get_updates() {
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