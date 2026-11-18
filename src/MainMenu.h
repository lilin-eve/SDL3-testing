#pragma once
#include <SDL3/SDL.h>
#include <iostream>

#include "MenuEvents.h"
#include "LevelEvents.h"

#include "MenuButtons.h"
#include "SettingsMenu.h"

class MainMenu {
    public:
    MainMenu( const SDL_FRect& floatRect )
    : menuRect{floatRect} {}

    void handleEvent( SDL_Event& event ){
        
        playButton.handleEvent( event );

        settingsButton.handleEvent( event );

        quitButton.handleEvent( event );

    }

    void render( SDL_Renderer* renderer ) const {

        auto [ r, g, b, a ]{menuColor};

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        
        SDL_RenderFillRect( renderer, &menuRect );


        playButton.render( renderer );

        settingsButton.render( renderer );

        quitButton.render( renderer );

    }

    private:
    // main menu itself
    SDL_FRect menuRect;
    SDL_Color menuColor{ 50, 75, 250, 255 };
    //

    // main menu buttons
    Play1Button playButton{{50.0f, 50.0f, 150.0f, 50.0f}};
    //
    SettingsMenuButton settingsButton{{300.0f, 50.0f, 150.0f, 50.0f}};
    //
    QuitAppButton quitButton{{550.0f, 50.0f, 150.0f, 50.0f}};
    //  
    
};
