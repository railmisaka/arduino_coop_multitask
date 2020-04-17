// ACM
// Created by railmisaka (railmisaka@gmail.com)

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef AVR

	#include <stdio.h>

	// not an arduino
	#define DEBUG_PRINTF(f_, ...) printf((f_), __VA_ARGS__)

#else

	// arduino
	#define DEBUG_PRINTF(f_, ...)

#endif

#endif
