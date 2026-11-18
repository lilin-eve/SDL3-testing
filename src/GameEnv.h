#pragma once
#include <SDL3/SDL.h>

#include "PlayerSprite.h"
#include "Level_1.h"
#include "LevelEvents.h"
#include "MenuEvents.h"

#include <string>
#include <vector>

class GameEnv {
    public:
    GameEnv( SDL_Renderer* renderer, const std::string& localPath )
    : renderer{renderer},
    localPath{localPath} {}

    void render( std::vector<int> windowDimensions ){

        using namespace LevelEvents;
        using namespace MenuEvents;

        if ( confirmRenderMenu == true ){
            std::cout << "Error! Level & menu open at the same time." << std::endl;
            std::cout << "sent from GameEnv::render()." << std::endl;
            SDL_Event appShutdown{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appShutdown);
        }

        //  Load level 1
        if ( levelFlip[0] == true ){
            level1.render( windowDimensions );
        }
        //  Load level 2
        else if ( levelFlip[1] == true ){

        }
        //  Load level 3
        else if ( levelFlip[2] == true ){

        }

        //  tomokoSprite.render( windowDimensions, renderer );

    }

    void handleEvent( std::vector<int> windowDimensions, SDL_Event& event ){

        using namespace LevelEvents;
        using namespace MenuEvents;

        if ( confirmRenderMenu == true ){
            std::cout << "Error! Level & menu open at the same time." << std::endl;
            std::cout << "sent from GameEnv::handleEvent()." << std::endl;
            SDL_Event appShutdown{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appShutdown);
        }

        if ( levelFlip[0] == true ){
            level1.handleEvent( windowDimensions, event );
        }
        else if ( levelFlip[1] == true ){

        }

        //  tomokoSprite.handleEvent( windowDimensions, event );

    }

    private:
    SDL_Renderer* renderer;

    std::string localPath;

    //  PlayerSprite tomokoSprite{ renderer, localPath + "tomoko-pixel.png" };

    Level_1 level1{ renderer, localPath };

    //  GameMenuButton menuButton{{ 25.0f, 25.0f, 50.0f, 50.0f }};

};
