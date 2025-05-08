#include "telegram.hh"

const String url = "https://api.telegram.org:443/bot" + String(TELEGRAM_BOT_TOKEN);

// 
void tg_send_message(String message, String chat_id) {
    String chats_id[] = CHAT_ID;

    if (chat_id != "")
        chats_id[0] = chat_id;

    for (auto id : chats_id) {
        // Создание JSON-строки с данными сообщения
        String json = "{\"chat_id\":\"" + id + "\",\"text\":\"" + message + "\"}";

        post_request(url + "/sendMessage", json);
        
        if (chat_id != "")
            break;
    }
}

// Get commands form the Bot 
int id = 0;

String tg_get_updates() {
    String payload = get_request(url + "/getUpdates?offset=" + String(id));

    DynamicJsonDocument json(1024);
    deserializeJson(json, payload);

    auto result = json["result"][0];

    id = result["update_id"].as<String>().toInt();
    String command = result["message"]["text"].as<String>();

    if (id != 0) {
        id += 1;

        String chat_id = result["message"]["chat"]["id"].as<String>();
        processCommand(command, chat_id);
    }

    return command;
}
