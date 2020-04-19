// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Arduino.h"
#include "Configuration.h"

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef ACMDEBUG

#define SERIAL_SPEED 9600

#define DEBUG_PRINTLN( f_, ... ) { \
		char __tmp[80]; \
		sprintf( __tmp, (f_), ##__VA_ARGS__ ); \
		__tmp[79] = '\0'; \
		Serial.println( __tmp ); \
	}

#define DEBUG_PRINT( f_, ... ) { \
		char __tmp[80]; \
		sprintf( __tmp, (f_), ##__VA_ARGS__ ); \
		__tmp[79] = '\0'; \
		Serial.print( __tmp ); \
	}

#define DEBUG_PRINTLN_STRING( STRING ) { \
		Serial.println( STRING ); \
	}

#define DEBUG_PRINT_STRING( STRING ) { \
		Serial.print( STRING ); \
	}

#define MESSAGE_CODE_TO_TEXT( CODE ) __ACMDebug.getStringByCode( CODE )

#define DEBUG_SETUP __ACMDebug.Init();

class ACMDebug
{
public:
	ACMDebug();
	void Init();

	void addCodeString( int code, String string );
	String getStringByCode( int code );

private:
	String *codesToStrings;
};

extern ACMDebug __ACMDebug;

#else

#define DEBUG_SETUP

#define DEBUG_PRINTLN( f_, ... )
#define DEBUG_PRINT( f_, ... )
#define DEBUG_PRINTLN_STRING( STRING )
#define DEBUG_PRINT_STRING( STRING )
#define MESSAGE_CODE_TO_TEXT( CODE )

#endif
#endif
