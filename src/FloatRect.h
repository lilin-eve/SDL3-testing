#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class FloatRect {
    public:
    FloatRect( const SDL_FRect& floatRect )
    : floatRect{floatRect} {}

    virtual ~FloatRect() = default;

    virtual void render( SDL_Renderer* renderer ) const {

        auto [ r, g, b, a ]{ isMouseHovering ? hoverColor : normColor };

        //  const auto* Fmt{ SDL_GetPixelFormatDetails(windowSurface->format) };

        SDL_SetRenderDrawColor( renderer, r, g, b, a );

        SDL_RenderFillRect( renderer, &floatRect );

    }

    virtual void onMouseEnter(){
        std::cout << "Mouse cursor over float rectangle." << std::endl;
    }

    virtual void onMouseExit(){
        std::cout << "Mouse cursor left float rectangle." << std::endl;
    }
    
    virtual void onLeftClick(){
        std::cout << "Rectangle clicked." << std::endl; 
    }

    void handleMouse( SDL_Event& mouse ){

        if ( mouse.type == SDL_EVENT_MOUSE_MOTION ){
            bool wasMouseHovering{isMouseHovering};

            isMouseHovering = isWithinRect( mouse.motion.x, mouse.motion.y );
            
            if ( !wasMouseHovering && isMouseHovering ) onMouseEnter();

            else if ( wasMouseHovering && !isMouseHovering ) onMouseExit();

        }
        else if ( mouse.type == SDL_EVENT_MOUSE_BUTTON_DOWN ){
            if ( isMouseHovering && mouse.button.button == SDL_BUTTON_LEFT ) onLeftClick();
        }
        else if ( mouse.type == SDL_EVENT_WINDOW_MOUSE_LEAVE ){
            if ( isMouseHovering ) onMouseExit();
            isMouseHovering = false;
        }
        
    }

    void setNormColor( const SDL_Color& newColor ){
        normColor = newColor;
    }

    SDL_Color getNormColor() const {
        return normColor;
    }

    void setHoverColor( const SDL_Color& newColor ){
        hoverColor = newColor;
    }

    SDL_Color getHoverColor() const {
        return hoverColor;
    }

    private:
    SDL_FRect floatRect;

    SDL_Color normColor{ 255, 125, 0, 255 };
    SDL_Color hoverColor{ 128, 128, 0, 255 };

    bool isMouseHovering{false};

    bool isWithinRect( const float& x, const float& y ){

        if ( x < floatRect.x ) return false;

        else if ( x > floatRect.x + floatRect.w ) return false;

        else if ( y < floatRect.y ) return false;

        else if ( y > floatRect.y + floatRect.h ) return false;

        else return true;

    }

};
