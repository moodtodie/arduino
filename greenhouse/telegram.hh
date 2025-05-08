#ifndef GREENHOUSE_TELEGRAM_HH
#define GREENHOUSE_TELEGRAM_HH

#include <ArduinoJson.h>

#include "config.h"
#include "network.hh"
#include "command_handler.hh"

void tg_send_message(String message, String chat_id = "");
String tg_get_updates();

#endif // GREENHOUSE_TELEGRAM_HH
