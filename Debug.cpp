// ACM
// Created by railmisaka (railmisaka@gmail.com)

#include "Debug.h"

#ifdef ACMDEBUG

ACMDebug __ACMDebug;

#include "Messages.h"

ACMDebug::ACMDebug()
{
	codesToStrings = new String[MESSAGES_TYPES_COUNT];

	#define MESSAGES_LIST
	#define MESSAGES_LIST_END
	#define DECLARE_MESSAGE( MESSAGE ) __ACMDebug.addCodeString( MESSAGE, #MESSAGE );
	#include "MessagesConfiguration.h"
	#undef MESSAGES_LIST
	#undef MESSAGES_LIST_END
	#undef DECLARE_MESSAGE
}


void ACMDebug::Init()
{
	Serial.begin( SERIAL_SPEED );
	Serial.println( "ACM debug started" );
}

void ACMDebug::addCodeString( int code, String string )
{
	if( code != MESSAGES_TYPES_COUNT ) {
		codesToStrings[code] = string;
	}
}

String ACMDebug::getStringByCode( int code )
{
	if( code != MESSAGES_TYPES_COUNT ) {
		return codesToStrings[code];
	}
	return "UNDEFINED MESSAGE";
}

#endif
