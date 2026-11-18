#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <ctime>
#include "ErrorHandling.h"
#include "Wall.h"
#include "iostream"

class PlayerSprite {
    public:
    PlayerSprite( SDL_Renderer* gameRenderer, const std::string& file )
    : playerSprite{ IMG_LoadTexture( gameRenderer, file.c_str() ) }
    {
        if ( !playerSprite || !SDL_GetTextureSize( playerSprite, &spriteW, &spriteH ) ){
            #ifdef ERROR_LOGGING
            checkSDLError( "Loading image texture file ' " + file + " '" );
            #endif
            SDL_Event appQuit{ .type = SDL_EVENT_QUIT };
            SDL_PushEvent(&appQuit);
        }
    }

    void render( std::vector<int> windowDimensions, SDL_Renderer* gameRenderer ){

        //  detectPlayerCollision( object[0], object[1], object[2], object[3] );

        if ( getY() < windowDimensions[1] - getHeight() ) gravity();

        if ( getY() + getHeight() > windowDimensions[1] ) outOfGround();

        SDL_FRect playerRect{ getX(), getY(), getWidth(), getHeight() };

        SDL_SetRenderDrawColor( gameRenderer, 18, 18, 26, 255 );

        SDL_RenderTexture( gameRenderer, playerSprite, nullptr, &playerRect );

        #ifdef ERROR_LOGGING
        checkSDLError( "rendering Player sprite" );
        #endif

    }

    void handleEvent( std::vector<int> windowDimensions, SDL_Event& event ){

        float lastFrameTime{static_cast<float>(clock())};
        float currentTime{static_cast<float>(clock())};
        float deltaTime{ ( currentTime - lastFrameTime ) / 1000.0f };

        float speed{2000.0f};
        float deltaMovement{ speed * deltaTime };

        if ( event.type == SDL_EVENT_KEY_DOWN ){
            if ( event.key.key == SDLK_UP || event.key.key == SDLK_W ) {
                if ( check(windowDimensions, event.key) ){
                    updateY(-deltaMovement);
                    std::cout << "Up." << std::endl;
                }
                else std::cout << "Top border hit." << std::endl;
            }
            else if ( event.key.key == SDLK_DOWN || event.key.key == SDLK_S ){
                if ( check(windowDimensions, event.key) ){
                    updateY(deltaMovement);
                    std::cout << "Down." << std::endl;
                }
                else std::cout << "Bottom border hit." << std::endl;
            } 
            else if ( event.key.key == SDLK_LEFT || event.key.key == SDLK_A ){
                if ( check(windowDimensions, event.key) ){
                    updateX(-deltaMovement);
                    std::cout << "Left." << std::endl;
                }
                else std::cout << "Left border hit." << std::endl;
            } 
            else if ( event.key.key == SDLK_RIGHT || event.key.key == SDLK_D ){
                if ( check(windowDimensions, event.key) ){
                    updateX(deltaMovement);
                    std::cout << "Right." << std::endl;
                }
                else std::cout << "Right border hit." << std::endl;
            }

            if ( event.key.key == SDLK_SPACE ){
                jump();
            } 


        }


        else if ( event.type == SDL_EVENT_MOUSE_MOTION ){
            bool wasMouseHovering{isMouseHovering};

            isMouseHovering = isWithinRect( event.motion.x, event.motion.y );
            
            if ( !wasMouseHovering && isMouseHovering ) std::cout << "Mouse is hovering." << std::endl;

            else if ( wasMouseHovering && !isMouseHovering ) std::cout << "Mouse left icon." << std::endl;

        }
        else if ( event.type == SDL_EVENT_WINDOW_MOUSE_LEAVE ){
            isMouseHovering = false;
        }

    }

    bool check( const std::vector<int>& windowDimensions, SDL_KeyboardEvent& key ){

        bool checkEdges{false};

        if ( key.key == SDLK_LEFT || key.key == SDLK_A ){
            if ( getX() == 1 ) return false;
            else return true;
        } 

        else if ( key.key == SDLK_RIGHT || key.key == SDLK_D ){
            if ( getX() + getWidth() == windowDimensions[0] ) return false;
            else return true;
        } 

        else if ( key.key == SDLK_DOWN || key.key == SDLK_S ){
            if ( getY() + getHeight() == windowDimensions[1] ) return false;
            else return true;
        } 

        else if ( key.key == SDLK_UP || key.key == SDLK_W ){
            if ( getY() == 1 ) return false;
            else return true;
        } 

        return checkEdges;

    }

    void outOfGround(){
        spriteY -= 15.0f;
    }

    void jump(){
        spriteY += 1.0f;
        spriteY -= 75.0f;
    }

    void gravity(){
        spriteY += 15.0f;
    }

    void updateY( const float& updateY ){
        spriteY += updateY;
    }

    float getY() const {
        return spriteY;
    }

    void setY( const float& setY ){
        spriteY = setY;
    }

    void updateX( const float& updateX ){
        spriteX += updateX;
    }

    float getX() const {
        return spriteX;
    }

    void setX( const float& setX ){
        spriteX = setX;
    }

    void setWidth( const float& newImageWidth ){
        spriteW = newImageWidth;
    }

    float getWidth() const {
        return spriteH;
    }

    void setHeight( const float& newImageHeight ){
        spriteH = newImageHeight;
    }

    float getHeight() const {
        return spriteW;
    }

    ~PlayerSprite() {
        if ( playerSprite ){
            SDL_DestroyTexture( playerSprite );
        }
    }

    private:
    SDL_Texture* playerSprite;

    float spriteW{}, spriteH{};

    float spriteX{50.0f}, spriteY{50.0f};

    bool isWithinRect( const float& x, const float& y ){

        if ( x < getX() ) return false;

        else if ( x > getX() + getWidth() ) return false;

        else if ( y < getY() ) return false;

        else if ( y > getY() + getHeight() ) return false;

        else return true;

    }

    /*
    void detectPlayerCollision( const float& objectX, const float& objectY, const float& objectW, const float& objectH ){

        if ( getX() + getWidth() > objectX || getX() > objectX ){
            if ( getX() + getWidth() < objectX + objectW || getX() < objectX + objectW ) {

                if  ( getY() + getHeight() > objectY || getY() > objectY ){
                    updateY(-15.0f);

                    if ( getY() + getHeight() > objectY && getX() + ( getWidth() / 2 ) > objectX + ( objectW / 2 ) ) updateX(15.0f);

                    else if ( getY() > objectY && getX() + ( getWidth() / 2 ) > objectX + ( objectW / 2 ) ) updateX(15.0f);

                    else if (  getY() + getHeight() > objectY && getX() + ( getWidth() / 2 ) < objectX + ( objectW / 2 ) ) updateX(-15.0f);

                    else if ( getY() > objectY && getX() + ( getWidth() / 2 ) < objectX + ( objectW / 2 ) ) updateX(-15.0f);

                } 

            }

            
            if ( getY() + getHeight() >= objectY ){

            }

            std::cout << "Stuck in detect Player collision." << std::endl;

            if ( getY() <= objectY + ( objectH / 2 ) ) updateY(-1.0f);

            //  else if ( getY() + ( getHeight() / 2 ) > objectY + ( objectH / 2 ) ) updateY(1.0f);

            if ( getX() + ( getWidth() / 2 ) > objectX + ( objectW / 2 ) ) updateX(1.0f);

            else if ( getX() + ( getWidth() / 2 ) < objectX + ( objectW / 2 ) ) updateX(-1.0f);
            

        }

        
        if ( getX() <= objectX + objectW && getY() + getHeight() >= objectY ){

            if ( getY() <= objectY + ( objectH / 2 ) ) updateY(-1.0f);

            //  else if ( getY() + ( getHeight() / 2 ) > objectY + ( objectH / 2 ) ) updateY(1.0f);

            if ( getX() + ( getWidth() / 2 ) > objectX + ( objectW / 2 ) ) updateX(1.0f);

            else if ( getX() + ( getWidth() / 2 ) < objectX + ( objectW / 2 ) ) updateX(-1.0f);

        }
        

        //  while ( )

        
        while ( getX() + getWidth() >= objectX && getX() <= objectX + objectW ) {

            if ( getX() + ( getWidth() / 2 ) > objectX + ( objectW / 2 ) ) updateX(1.0f);

            else if ( getX() + ( getWidth() / 2 ) < objectX + ( objectW / 2 ) ) updateX(-1.0f);

        }
       

        
        while ( getX() + ( getWidth() / 2 ) >= objectX && getX() + ( getWidth() / 2 ) <= objectX + objectW && getY() >= objectY + objectH && getY() + getHeight() <= objectY ){

            if ( getY() < objectY + ( objectH / 2 ) ) updateY( -1.0f );

            else if ( getY() > objectY + ( objectH / 2 ) ) updateY( 1.0f );

            if ( getX() + ( getWidth() / 2 ) > objectX + ( objectW / 2 ) ) updateX( 1.0f );

            else if ( getX() + ( getWidth() / 2 ) < objectX + ( objectW / 2 ) ) updateX( -1.0f );

        }
        


    }
    */

    bool isMouseHovering{false};

};
