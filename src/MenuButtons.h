#pragma once 
#include <SDL3/SDL.h>
#include <iostream>
#include "FloatRect.h"
#include "MenuEvents.h"

//  Below are buttons on main menu
//  only renders if Flip[0](main menu) is true and all other Flip are false
//  
class Play1Button : public FloatRect {
    public:
    Play1Button( const SDL_FRect& floatRect )
    : FloatRect{floatRect}
    {
        setNormColor({255, 0, 0, 255});     //  Set button normal color pure red
        setHoverColor({0, 0, 255, 255});    //  Set button hover color pure blue
    }

    void handleEvent( SDL_Event& event ){

        FloatRect::handleMouse( event );

        using namespace MenuEvents;
        using namespace LevelEvents;
        if ( event.type == PLAY_LEVEL1 ) {
            std::cout << "Playing level 1 . . . " << std::endl;
            levelFlip[0] = true;
            currentLevel = 0;
        }
        else if ( event.type == CLOSE_LEVEL1 ) {
            std::cout << "Closing level 1 . . . " << std::endl;
            levelFlip[0] = false;
        }

    }

    void onLeftClick() override {

        std::cout << "Play level 1 button clicked." << std::endl;

        using namespace LevelEvents;
        using namespace MenuEvents;
        SDL_Event playEvent{ .type = levelFlip[0] ? CLOSE_LEVEL1 : PLAY_LEVEL1 };   //  Flip[0] is default false, so PLAY_LEVEL will be pushed first upon left click

        //  if play_level1 event is about to be pushed, set all menus to false, all menus will not render, & set only level 1 in levelFlip to true, only level 1 will render
        if ( playEvent.type == PLAY_LEVEL1 ){
            for ( size_t i = 0; i < menuFlip.size(); i++ ){
                menuFlip[i] = false;
                confirmRenderMenu = false;
            }
            for ( size_t i = 0; i < levelFlip.size(); i++ ){
                if ( i == 0 ){
                    levelFlip[i] = true;
                }
                else {
                    levelFlip[i] = false;
                }
            }
        }

        SDL_PushEvent(&playEvent);

    }

};
//  
class SettingsMenuButton : public FloatRect {
    public:
    SettingsMenuButton( const SDL_FRect& floatRect )
    : FloatRect{floatRect}
    {
        setNormColor({255, 165, 0, 255});   //  Set button color dark orange
    }

    void handleEvent( SDL_Event& event ){

        if ( event.type == SDL_EVENT_KEY_DOWN ){
            if ( event.key.key == SDL_SCANCODE_ESCAPE ){
                std::cout << "Escape key pressed." << std::endl;

                using namespace MenuEvents;
                SDL_Event settingsEvent{ .type = menuFlip[1] ? CLOSE_SETTINGS : OPEN_SETTINGS };    //  Flip[1] is default false, so OPEN_SETTINGS will be pushed first upon left click

                //  if OPEN_SETTINGS event is about to be pushed, set all other menus in menuFlip to false
                if ( settingsEvent.type == OPEN_SETTINGS ){

                    confirmRenderMenu = false;
                    renderMenu = false;
                    lastMenuOpen = 0;
                    confirmMax1 = 0;

                    //  runs through menus in menuFlip, if one is true, lastMenuOpen is assigned its item num for reference upon exit from settings menu, because settings menu can be called by both main menu & game menu
                    //  also checks for errors, only 1 menu should be open, if confirmMax1 is greater than 1, app pushes SDL_QUIT_EVENT
                    for (size_t i = 0; i < menuFlip.size(); i++ ){
                        renderMenu = menuFlip[i];
                        if ( renderMenu == true ){
                            lastMenuOpen = i;
                            confirmRenderMenu = true;
                            confirmMax1++;
                        }
                    }

                    //  closes all menus except for settings menu which is flipped to true
                    for ( size_t i = 0; i < menuFlip.size(); i++ ){
                        if ( i == 1 ){
                            menuFlip[i] = true;
                        }
                        else {
                            menuFlip[i] = false;
                        }
                    }
                }

                SDL_PushEvent( &settingsEvent );

            }

        } 

        FloatRect::handleMouse( event );

        using namespace MenuEvents;
        //  when exiting settings menu, references MenuEvents::lastMenuOpen for which which menu to return to/render after settings menu closes/is false
        if ( event.type == CLOSE_SETTINGS ){
            std::cout << "Closing settings menu . . . " << std::endl;
            menuFlip[1] = false;
            menuFlip[lastMenuOpen] = true;
        } 
        else if ( event.type == OPEN_SETTINGS ){
            std::cout << "Opening settings menu . . . " << std::endl;
            menuFlip[1] = true;
        } 

    }

    void onLeftClick() override {

        std::cout << "Settings button clicked." << std::endl;

        using namespace MenuEvents;
        SDL_Event settingsEvent{ .type = menuFlip[1] ? CLOSE_SETTINGS : OPEN_SETTINGS };    //  Flip[1] is default false, so OPEN_SETTINGS will be pushed first upon left click

        //  if OPEN_SETTINGS event is about to be pushed, set all other menus in menuFlip to false
        if ( settingsEvent.type == OPEN_SETTINGS ){

            confirmRenderMenu = false;
            renderMenu = false;
            lastMenuOpen = 0;
            confirmMax1 = 0;

            //  runs through menus in menuFlip, if one is true, lastMenuOpen is assigned its item num for reference upon exit from settings menu, because settings menu can be called by both main menu & game menu
            //  also checks for errors, only 1 menu should be open, if confirmMax1 is greater than 1, app pushes SDL_QUIT_EVENT
            for (size_t i = 0; i < menuFlip.size(); i++ ){
                renderMenu = menuFlip[i];
                if ( renderMenu == true ){
                    lastMenuOpen = i;
                    confirmRenderMenu = true;
                    confirmMax1++;
                }
            }

            //  closes all menus except for settings menu which is flipped to true
            for ( size_t i = 0; i < menuFlip.size(); i++ ){
                if ( i == 1 ){
                    menuFlip[i] = true;
                }
                else {
                    menuFlip[i] = false;
                }
            }
        }

        SDL_PushEvent( &settingsEvent );

    }

};
//  
// end
//
// below are buttons rendered on game environment or game menu
// game menu buttons only render when Flip[1](level 1) is true, & Flip[3](game menu) is true
//  
//  GameMenuButton rendered on game environment
//  renders if Flip[0](main menu) is false, & Flip[1](level 1) is true
//
class GameMenuButton : public FloatRect {
    public:
    GameMenuButton( const SDL_FRect& floatRect )
    : FloatRect{floatRect}
    {
        setNormColor({255, 165, 0, 255});
    }

    void handleEvent( SDL_Event& event ){

        FloatRect::handleMouse( event );

        using namespace MenuEvents;
        using namespace LevelEvents;
        //  when in-game menu is closed & level is resumed, its item num in LevelEvents::levelFlip is referenced from verification value currentLevel
        if ( event.type == CLOSE_GAME_MENU ){
            std::cout << "Closing in-game menu . . . " << std::endl;
            menuFlip[2] = false;
            levelFlip[currentLevel] = true;
        }
        else if ( event.type == OPEN_GAME_MENU ){
            std::cout << "Opening in-game menu . . . " << std::endl;
            std::cout << "Game now paused." << std::endl;
            menuFlip[2] = true;
        }

    }

    void onLeftClick() override {

        std::cout << "Game-menu button clicked." << std::endl;

        SDL_Event gameMenuEvent{ .type = MenuEvents::menuFlip[2] ? MenuEvents::CLOSE_GAME_MENU : MenuEvents::OPEN_GAME_MENU };

        if ( gameMenuEvent.type == MenuEvents::OPEN_GAME_MENU ){
            using namespace LevelEvents;

            //  resets verification values for LevelEvents::levelFlip
            confirmRenderLevel = false;
            renderLevel = false;
            currentLevel = 0;
            confirmMax1 = 0;

            //  runs through levels in levelFlip, if one is true, currentLevel is assigned its item num for reference upon exit from game menu
            //  also checks for errors, only 1 level should be open, if confirmMax1 is greater than 1, app pushes SDL_QUIT_EVENT
            for (size_t i = 0; i < levelFlip.size(); i++ ){
                renderLevel = levelFlip[i];
                if ( renderLevel == true ){
                    currentLevel = i;
                    confirmRenderLevel = true;
                    confirmMax1++;
                }
            }

            using namespace MenuEvents;
            //  sets all levels to false
            for ( size_t i = 0; i < levelFlip.size(); i++ ){
                levelFlip[i] = false;
            }
            //  sets 3rd item in menuFlip, the in-game menu, to true
            for ( size_t i = 0; i < menuFlip.size(); i++ ){
                if ( i == 2 ){
                    menuFlip[i] = true;
                }
                else {
                    menuFlip[i] = false;
                }
            }
        }
    }
};
//
//  rendered on game menu
//
class MainMenuButton : public FloatRect {
    public:
    MainMenuButton( const SDL_FRect& floatRect )
    : FloatRect{floatRect}
    {
        setNormColor({0, 255, 0, 255});     //  Set button normal color to pure green
        setHoverColor({115, 0, 150, 255});  //  Set button hover color to purple
    }

    void handleEvent( SDL_Event& event ){

        FloatRect::handleMouse( event );

        using namespace MenuEvents;
        if ( event.type == SDL_EVENT_QUIT ) menuFlip[0] = true;

        else if ( event.type == DO_NOTHING ) menuFlip[0] = false;

    }

    void onLeftClick() override {

        using namespace MenuEvents;
        SDL_Event mainMenuEvent{ .type = menuFlip[0] ? CLOSE_MAIN_MENU : OPEN_MAIN_MENU }; //  Only push APP_SHUTDOWN if Flip[2] is false, Flip[2] is default false, only true after push APP_SHUTDOWN

        if ( mainMenuEvent.type == OPEN_MAIN_MENU ){
            for ( size_t i = 0; i < menuFlip.size(); i++ ){
                if ( i == 0 ){
                    menuFlip[i] = true;
                }
                else {
                    menuFlip[i] = false;
                }
            }
        }

        SDL_PushEvent(&mainMenuEvent);

    }

};
//
//  QuitAppButton displayed last in button list on main menu & game menu
//
class QuitAppButton : public FloatRect {
    public:
    QuitAppButton( const SDL_FRect& floatRect )
    : FloatRect{floatRect}
    {
        setNormColor({0, 255, 0, 255});     //  Set button normal color to pure green
        setHoverColor({115, 0, 150, 255});  //  Set button hover color to purple
    }

    void handleEvent( SDL_Event& event ){

        FloatRect::handleMouse( event );

        using namespace MenuEvents;
        if ( event.type == SDL_EVENT_QUIT ) menuFlip[3] = true;

        else if ( event.type == DO_NOTHING ) menuFlip[3] = false;

    }

    void onLeftClick() override {

        using namespace MenuEvents;
        SDL_Event quitEvent{ .type = menuFlip[3] ? DO_NOTHING : SDL_EVENT_QUIT }; //  Only push APP_SHUTDOWN if Flip[2] is false, Flip[2] is default false, only true after push APP_SHUTDOWN

        SDL_PushEvent(&quitEvent);

    }


};
//  
//end
//
