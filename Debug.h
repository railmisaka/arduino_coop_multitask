// ACM
// Created by railmisaka (railmisaka@gmail.com)

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef AVR

	#define INIT_DEBUG InitDebug();
	extern void InitDebug();

	#include <stdio.h>

	// not an arduino
	#define DEBUG_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

	// Messages debug
	#include "Messages.h"
	#include <map>
	#include <string>
	extern std::map<int, std::string> MessagesMap;

	#define MESSAGE_CODE_TO_TEXT( CODE ) MessagesMap[CODE]

#else
	// arduino

	#define INIT_DEBUG

	#define DEBUG_PRINTF(f_, ...)

#endif

#endif
