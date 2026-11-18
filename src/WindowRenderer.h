#pragma once
#include <SDL3/SDL.h>
//  #include <iostream>
#include "ErrorHandling.h"

class WindowRenderer {
    public:
    WindowRenderer() {
        //  Create window
        SDLWindow =  SDL_CreateWindow( "tomoko SDL3~mode :3", getWidth(), getHeight(), 0 );
        #ifdef ERROR_LOGGING
        checkSDLError( "Creating Window" );
        #endif
        SDLRenderer = SDL_CreateRenderer( SDLWindow, nullptr );
        #ifdef ERROR_LOGGING
        checkSDLError( "Creating Renderer" );
        #endif
    }

    int getWidth() const {
        return 750;
    }

    int getHeight() const {
        return 500;
    }

    void clear(){

        SDL_RenderClear(SDLRenderer);

    }

    void render(){

        //  const auto* Fmt{ SDL_GetPixelFormatDetails( getSurface()->format ) };

        auto [ r, g, b, a ]{ backgroundColor };

        SDL_SetRenderDrawColor( SDLRenderer, r, g, b, a );

        SDL_RenderFillRect( SDLRenderer, nullptr );

    }

    void update(){
        SDL_RenderPresent(SDLRenderer);    
    }

    SDL_Renderer* getRenderer() const {
        return SDLRenderer;
    }

    SDL_Window* getWindow() const {
        return SDLWindow;
    }

    void setBackgroundColor( const SDL_Color& newColor ){
        backgroundColor = newColor;
    }

    SDL_Color getBackgroundColor() const {
        return backgroundColor;
    }

    SDL_Surface* getSurface() const {
        return SDL_GetWindowSurface(SDLWindow);
    }

    WindowRenderer(const WindowRenderer&) = delete;
    WindowRenderer& operator=(const WindowRenderer&) = delete;

    ~WindowRenderer() {
        if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)){
            SDL_DestroyWindow(SDLWindow);
            SDL_DestroyRenderer(SDLRenderer);
        }
    }

    private:
    SDL_Window* SDLWindow{nullptr};
    SDL_Renderer* SDLRenderer{nullptr};

    SDL_Color backgroundColor{ 0, 0, 255, 200 };


};
