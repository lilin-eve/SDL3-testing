#pragma once
#include <SDL3/SDL.h>
#include "MenuEvents.h"
#include "MenuButtons.h"

class SettingsMenu {
    public:
    SettingsMenu( const SDL_FRect& floatRect )
    : settingsMenuRect{floatRect} {}

    void handleEvent( SDL_Event& event ){

    }

    void render( SDL_Renderer* renderer ) const {

        auto [ r, g, b, a ]{menuColor};

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        
        SDL_RenderFillRect( renderer, &settingsMenuRect );

    }

    private:
    SDL_FRect settingsMenuRect;
    SDL_Color menuColor{ 50, 75, 250, 255 };

    //  MenuBackButton backButton{{}};

};
