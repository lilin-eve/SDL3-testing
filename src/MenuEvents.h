#pragma once 
#include <SDL3/SDL.h>
#include <array>

namespace MenuEvents {

    //  menu verification items
    //  ensures only one menu open at a time
    inline bool confirmRenderMenu{false};
    inline bool renderMenu{false};
    inline size_t lastMenuOpen{};
    inline int confirmMax1{0};

    //  menus, main menu is open by default
    //  Flip[0] is whether Main Menu is open, default true
    //  Flip[1] is whether main menu settings is open, default false
    //  Flip[2] is whether game menu is open, default false
    inline std::array<bool, 4> menuFlip{ true, false, false, false };


    //  Flip[0] is whether Main Menu is open, default true
    const inline Uint32 OPEN_MAIN_MENU{ SDL_RegisterEvents(1) };
    const inline Uint32 CLOSE_MAIN_MENU{ SDL_RegisterEvents(1) };

    //  Flip[1] is whether main menu Settings is open, default false 
    const inline Uint32 OPEN_SETTINGS{ SDL_RegisterEvents(1) };
    const inline Uint32 CLOSE_SETTINGS{ SDL_RegisterEvents(1) };

    //  Flip[2] is whether game menu is open, default false 
    const inline Uint32 OPEN_GAME_MENU{ SDL_RegisterEvents(1) };
    const inline Uint32 CLOSE_GAME_MENU{ SDL_RegisterEvents(1) };

    //  Flip[3] is whether to shutdown app, default false
    const inline Uint32 DO_NOTHING{ SDL_RegisterEvents(1) };

    
}
