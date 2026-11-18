#pragma once
#include <SDL3/SDL.h>
#include "PlayerSprite.h"

class Wall {
    public:
    Wall( const SDL_FRect& floatRect )
    : wall{floatRect} {}

    void render( const std::vector<int> windowDimensions, SDL_Renderer* renderer ){
        auto [ r, g, b, a ]{ isPlayerTouching ? touchColor : normColor };

        //  const auto* Fmt{ SDL_GetPixelFormatDetails(windowSurface->format) };

        SDL_SetRenderDrawColor( renderer, r, g, b, a );

        SDL_RenderFillRect( renderer, &wall );

        //  detectPlayerCollision( windowDimensions[0], windowDimensions[1], player );

    }

    void handleEvent( const SDL_Event& event ){

    }

    float getWallX() const {
        return wall.x;
    }

    float getWallY() const {
        return wall.y;
    }

    float getWallW() const {
        return wall.w;
    }

    float getWallH() const {
        return wall.h;
    }

    bool isPlayerTouching{false};

    private:
    SDL_FRect wall;

    SDL_Color normColor{ 255, 125, 0, 255 };
    SDL_Color touchColor{ 128, 128, 0, 255 };


};  
