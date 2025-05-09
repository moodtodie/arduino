#include "network.hh"

const char* ssid = STASSID;
const char* password = STAPSK;

//Connecting to Wi-Fi
void wifi_connect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
        delay(500);
}

String get_request(String url) {
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) {
        String response = "null";

        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

        // Ignore SSL certificate validation
        client->setInsecure();

        //create an HTTPClient instance
        HTTPClient https;

        if (https.begin(*client, url)) {  // HTTPS
            https.addHeader("accept", "application/json");

            // start connection and send HTTP header
            int httpCode = https.GET();

            // httpCode will be negative on error
            if (httpCode > 0) {
                // HTTP header has been send and Server response header has been handled
                if (Serial.available())
                    Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

                response = https.getString();
            } else if (Serial.available())
                Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());

            https.end();
        } else if (Serial.available())
            Serial.printf("[HTTPS] Unable to connect\n");

        return response;
    }
    return String(MSG_DATE) + ": " + String(MSG_NO_CONNECTION);
}

void post_request(String url, String json_data){
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) {

        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

        // Ignore SSL certificate validation
        client->setInsecure();

        //create an HTTPClient instance
        HTTPClient https;

        if (https.begin(*client, url)) {  // HTTPS

            https.addHeader("Content-Type", "application/json");

            // start connection and send HTTP header
            int httpCode = https.POST(json_data);

            // httpCode will be negative on error
            if (httpCode > 0 && Serial.available())
                // HTTP header has been send and Server response header has been handled
                Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
            else if (Serial.available())
                Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
            https.end();
        }
        else
            if (Serial.available())
                Serial.printf("[HTTPS] Unable to connect\n");
    }
}

//  Получает текущее время на основании IP-адреса
String get_formatted_datetime() {
    int attempt = 0;

    do {
        attempt++;

        String response = get_request(String(TIME_API));
        String datetime = getDataTimeFromJson(response);

        if (response == "null"){
            continue;
        } else {
            return datetime;
        }
    } while (attempt < 5);

    return MSG_NO_CONNECTION;
}

void send_stat(String chat_id) {
    String message = String(MSG_DATE) + ": " + get_formatted_datetime() + "\n";
    message += get_soil_moisture();
    message += getTemperature();
    tg_send_message(message, chat_id);
}
