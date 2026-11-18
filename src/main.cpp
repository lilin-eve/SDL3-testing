#include <SDL3/SDL.h>

#include "ErrorHandling.h"

#include "MenuEvents.h"
#include "LevelEvents.h"

#include "UI.h"
#include "GameEnv.h"

#include "ErrorHandling.h"
#include "WindowRenderer.h"

#include <iostream>
#include <string>


std::string getLocalPath(){

    std::string localPath{ SDL_GetBasePath() };
    localPath.pop_back();

    size_t pos{ localPath.find_last_of('/')};

    const std::string localDir{ localPath.substr( pos, localPath.length() ) };
    const std::string parentPath{ localPath.substr( 0, pos ) };

    if ( localDir == "/build" ){
        localPath = parentPath + "/src/assets/";
    }
    else if ( localDir == "/src" ){
        localPath = parentPath + localDir + "/assets/";
    }
    else {
        std::cout << "Invalid local path." << std::endl;
        SDL_Event quitApp{ .type = SDL_EVENT_QUIT };
        SDL_PushEvent( &quitApp );
    }

    return localPath;

}

int main (int argc, char* argv[] ){

    if(!SDL_Init(SDL_INIT_VIDEO)){
        #ifdef ERROR_LOGGING
        checkSDLError( "Initializing SDL video" );
        #endif
        return 1;
    }

    WindowRenderer gameWindow0;

    std::vector<int> windowDimensions{ gameWindow0.getWidth(), gameWindow0.getHeight() };

    UI uiManager( gameWindow0.getRenderer() );

    GameEnv environment( gameWindow0.getRenderer(), getLocalPath() );

    SDL_Event event;
    bool isRunning{true};

    
    while (isRunning){

        LevelEvents::confirmRenderLevel = false;
        LevelEvents::renderLevel = false;
        LevelEvents::confirmMax1 = 0;
        LevelEvents::currentLevel = 0;

        for (size_t i = 0; i < LevelEvents::levelFlip.size(); i++ ){
            LevelEvents::renderLevel = LevelEvents::levelFlip[i];
            if ( LevelEvents::renderLevel == true ){
                LevelEvents::currentLevel = i;
                LevelEvents::confirmRenderLevel = true;
                LevelEvents::confirmMax1++;
            }
        }

        MenuEvents::confirmRenderMenu = false;
        MenuEvents::renderMenu = false;
        MenuEvents::confirmMax1 = 0;
        MenuEvents::lastMenuOpen = 0;

        for (size_t i = 0; i < MenuEvents::menuFlip.size(); i++ ){
            MenuEvents::renderMenu = MenuEvents::menuFlip[i];
            if ( MenuEvents::renderMenu == true ){
                MenuEvents::lastMenuOpen = i;
                MenuEvents::confirmRenderMenu = true;
                MenuEvents::confirmMax1++;
            }
        }

        using namespace LevelEvents;
        using namespace MenuEvents;
        while (SDL_PollEvent(&event)){

            uiManager.handleEvent( event );
            
            if ( levelFlip[currentLevel] == true ) environment.handleEvent( windowDimensions, event );

            if ( event.type == SDL_EVENT_QUIT ){
                std::cout << "Exiting SDL application . . . " << std::endl;
                isRunning = false;
            } 

        }

        gameWindow0.clear();

        if ( menuFlip[0] == true ) gameWindow0.setBackgroundColor({204, 57, 123, 255});         //  Set main menu background color to dark pink

        else if ( menuFlip[1] == true ) gameWindow0.setBackgroundColor({116, 66, 200, 255});    //  Set settings menu background color to lavender

        else if ( menuFlip[2] == true ) gameWindow0.setBackgroundColor({255, 29, 206, 255});    //  Set game menu background color to magenta

        if ( levelFlip[0] == true ) gameWindow0.setBackgroundColor({150, 0, 205, 255});         //  Set level 1 background color to some purple

        gameWindow0.render();


        uiManager.render( gameWindow0.getSurface() );

        if ( levelFlip[currentLevel] == true ) environment.render( windowDimensions );

        
        gameWindow0.update();

    }

    SDL_Quit();

    return 0;

}
