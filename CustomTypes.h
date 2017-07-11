/**
    Created 10 July 2017
    CustomTypes.h
    MIT License

    @author railmisaka
    @version 0.1 7/10/17 
*/

#define MAX_UNSIGNED_LONG 4294967295

#include "Arduino.h"
#ifndef LONG_MESSAGES
typedef byte MESSAGE_INT;
#else
typedef word MESSAGE_INT;
#endif
