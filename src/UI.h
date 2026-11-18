#pragma once
#include <SDL3/SDL.h>
#include <iostream>

#include "MenuButtons.h"

#include "WindowRenderer.h"

#include "MainMenu.h"
#include "SettingsMenu.h"
#include "GameMenu.h"

#include "MenuEvents.h"
#include "LevelEvents.h"

class UI {
    public:
    UI( SDL_Renderer* renderer )
    : renderer{renderer} {}

    void render( SDL_Surface* windowSurface ) {

        //  if in level, only render game menu button
        if ( LevelEvents::confirmRenderLevel == true && LevelEvents::confirmMax1 == 1 ){
            gameMenuButton.render( renderer );
        }

        //  if not in level, check which menu is open
        else if ( MenuEvents::confirmRenderMenu == true && MenuEvents::confirmMax1 == 1 ){
            
            //  whether main menu is rendered, default true
            if ( MenuEvents::menuFlip[0] == true ){
                mainMenu.render( renderer );
            }
            //  whether settings menu is rendered, default false
            else if ( MenuEvents::menuFlip[1] == true ){
                settingsMenu.render( renderer );
            }
            //  whether game menu is rendered, default false
            else if ( MenuEvents::menuFlip[2] == true ){
                gameMenu.render( renderer );
            }

        }
        //  if invalid feedback, i.e. more than one menu or level is open, quit SDL app
        else if ( LevelEvents::confirmRenderLevel == true && LevelEvents::confirmMax1 != 1 || MenuEvents::confirmRenderMenu == true && MenuEvents::confirmMax1 != 1 ){
            std::cout << "Error! More than one level or menu is open, or code is faulty." << std::endl;
            std::cout << "Sent from UI::render()." << std::endl;
            SDL_Event appShutdown{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appShutdown);
        }
        else if ( LevelEvents::confirmRenderLevel == true && MenuEvents::confirmRenderMenu == true ){
            std::cout << "Error! Menu & level open at the same time, or code is faulty." << std::endl;
            std::cout << "Sent from UI::render()." << std::endl;
            SDL_Event appShutdown{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appShutdown);
        }

    }

    void handleEvent( SDL_Event& event ){

        using namespace LevelEvents;

        //  if in level & level count is 1, only render gameMenuButton UI
        if ( confirmRenderLevel == true && confirmMax1 == 1 ){
            gameMenuButton.handleEvent( event );
        }

        //  if in menu & menu count is 1, query which menu
        else if ( MenuEvents::confirmRenderMenu == true && MenuEvents::confirmMax1 == 1 ){

            //  whether main menu is rendered, default true
            if ( MenuEvents::menuFlip[0] == true  ){
                mainMenu.handleEvent( event );
            }
            //  whether settings menu is rendered, default false
            else if ( MenuEvents::menuFlip[1] == true ){
                settingsMenu.handleEvent( event );
            }
            //  whether game menu is rendered, default false
            else if ( MenuEvents::menuFlip[2] == true ){
                gameMenu.handleEvent( event );
            }

        }

        //  if more than 1 level or menu is open, push SDL_EVENT_QUIT
        else if ( confirmRenderLevel == true && confirmMax1 != 1 || MenuEvents::confirmRenderMenu == true && MenuEvents::confirmMax1 != 1 ){
            std::cout << "Error! More than one level or menu is open, or code is faulty." << std::endl;
            std::cout << "sent from UI::handleEvent()." << std::endl;
            SDL_Event appShutdown{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appShutdown);
        }

        //  if in menu & level is open, push SDL_EVENT_QUIT 
        else if ( confirmRenderLevel == true && MenuEvents::confirmRenderMenu == true ){
            std::cout << "Error! Menu & level open at the same time, or code is faulty." << std::endl;
            std::cout << "Sent from UI::handleEvent()." << std::endl;
            SDL_Event appShutdown{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appShutdown);
        }

    }

    private:
    SDL_Renderer* renderer{nullptr};

    MainMenu mainMenu{{ 25.0f, 25.0f, 700.0f, 250.0f }};

    SettingsMenu settingsMenu{{ 25.0f, 25.0f, 700.0f, 400.0f }};

    GameMenu gameMenu{{ 200.0f, 50.0f, 650.0f, 450.0f }};
    GameMenuButton gameMenuButton{{50.0f, 50.0f, 50.0f, 50.0f}};

    //  std::string localPath{};
    //  PlayerSprite tomokoSprite{ renderer, localPath + "tomoko-pixel.png" };

};
