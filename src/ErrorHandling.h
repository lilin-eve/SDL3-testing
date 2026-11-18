#pragma once 
#include <SDL3/SDL.h>
#include <iostream>

#define ERROR_LOGGING

#ifdef ERROR_LOGGING
void checkSDLError( const std::string& action );
#endif
