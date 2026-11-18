#pragma once
#include <SDL3/SDL.h>

class GameMenu {
    public:
    GameMenu( const SDL_FRect& floatRect )
    : gameMenuRect{floatRect} {}

    void handleEvent( SDL_Event& event ){ 

    }

    void render( SDL_Renderer* renderer ) const {

        if ( !MenuEvents::menuFlip[0] ) return;

        auto [ r, g, b, a ]{gameMenuColor};

        SDL_SetRenderDrawColor( renderer, r, g, b, a );
        
        SDL_RenderFillRect( renderer, &gameMenuRect );


        mainMenuButton.render( renderer );

        settingsButton.render( renderer );

        quitButton.render( renderer );

    }

    private:
    // main menu itself
    SDL_FRect gameMenuRect;
    SDL_Color gameMenuColor{ 50, 75, 250, 255 };
    //

    // game menu buttons
    MainMenuButton mainMenuButton{{50.0f, 50.0f, 150.0f, 150.0f}};
    //
    SettingsMenuButton settingsButton{{250.0f, 50.0f, 150.0f, 150.0f}};
    //
    QuitAppButton quitButton{{450.0f, 50.0f, 150.0f, 150.0f}};
    //  
    
};
