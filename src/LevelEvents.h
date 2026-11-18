#pragma once
#include <SDL3/SDL.h>
#include <array>

namespace LevelEvents {

    //  Level verification items
    //  ensures only one level open at a time
    inline bool confirmRenderLevel{false};
    inline bool renderLevel{false};
    inline size_t currentLevel{};
    inline int confirmMax1{0};    

    //  all levels false by default
    inline std::array<bool, 4> levelFlip{ false, false, false, false };

    //  levelFlip[0] is whether level 1 is open, default false 
    const inline Uint32 PLAY_LEVEL1{ SDL_RegisterEvents(1) };
    const inline Uint32 CLOSE_LEVEL1{ SDL_RegisterEvents(1) };

    //  other LevelFlips not refs yet

}
