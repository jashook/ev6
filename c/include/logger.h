////////////////////////////////////////////////////////////////////////////////
//
// Module:        logger
//
// Version:       1.0
//
// Modifications: 
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef __LOGGER_H__
#define __LOGGER_H__

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <io.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct logger {
	FILE* _s_logger;
} LOGGER;

bool initialize_logger(LOGGER*);



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif   // __LOGGER_H__