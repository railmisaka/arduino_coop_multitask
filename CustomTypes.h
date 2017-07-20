/**
    Created 10 July 2017
    CustomTypes.h
    MIT License

    @author railmisaka
    @version 0.11 7/20/17 
*/

#include "Arduino.h"

#define MAX_UNSIGNED_LONG 4294967295

#ifndef LONG_MESSAGES
typedef byte MESSAGE_INT;
#else
typedef word MESSAGE_INT;
#endif

