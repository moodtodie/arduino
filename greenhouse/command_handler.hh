#ifndef GREENHOUSE_COMMAND_HANDLER_HH
#define GREENHOUSE_COMMAND_HANDLER_HH

#include "config.h"

#include "network.hh"
#include "telegram.hh"
#include "limits.hh" 

//  Use Telegram Bot to get updates
void processCommand(String command, String chat_id);

#endif // GREENHOUSE_COMMAND_HANDLER_HH
