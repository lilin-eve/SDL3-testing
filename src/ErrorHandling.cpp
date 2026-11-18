#include <SDL3/SDL.h>
#include "ErrorHandling.h"

#ifdef ERROR_LOGGING
void checkSDLError( const std::string& action ){

    const char* error{ SDL_GetError() };

    if ( *error != '0' ){
        std::cout << "Error " << action << ": " << error << std::endl;
        SDL_ClearError();
    }

};
#endif
