// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Debug.h"

#ifndef AVR

std::map<int, std::string> MessagesMap;

#define MESSAGES_LIST void InitMessagesMap() {
#define MESSAGES_LIST_END }
#define DECLARE_MESSAGE( MESSAGE ) MessagesMap[MESSAGE] = #MESSAGE;

#include "MessagesTypes.h"

#undef MESSAGES_LIST
#undef MESSAGES_LIST_END
#undef DECLARE_MESSAGE

void InitDebug()
{
	InitMessagesMap();
}

#endif
