#pragma once
#include <SDL3/SDL.h>

#include "Wall.h"

#include "PlayerSprite.h"

#include "ErrorHandling.h"

class Level_1 {
    public:
    Level_1( SDL_Renderer* renderer, const std::string& localPath )
    : renderer{renderer},
    localPath{localPath} {}

    void render( const std::vector<int> windowDimensions ){

        firstWall.render( windowDimensions, renderer );

        secondWall.render( windowDimensions, renderer );

        thirdWall.render( windowDimensions, renderer );

        //  fourthWall.render( windowDimensions, renderer );

        //  fifthWall.render( windowDimensions, renderer );
        //  std::array<float, 4> firstWallDimensions{ firstWall.getWallX(), firstWall.getWallY(), firstWall.getWallW(), firstWall.getWallH() };

        detectPlayerCollision( firstWall.getWallX(), firstWall.getWallY(), firstWall.getWallW(), firstWall.getWallH() );

        detectPlayerCollision( secondWall.getWallX(), secondWall.getWallY(), secondWall.getWallW(), secondWall.getWallH() );

        detectPlayerCollision( thirdWall.getWallX(), thirdWall.getWallY(), thirdWall.getWallW(), thirdWall.getWallH() );

        //  detectPlayerCollision( fourthWall.getWallX(), fourthWall.getWallY(), fourthWall.getWallW(), fourthWall.getWallH() );

        //  detectPlayerCollision( fifthWall.getWallX(), fifthWall.getWallY(), fifthWall.getWallW(), fifthWall.getWallH() );

        tomokoSprite.render( windowDimensions, renderer );

    }

    void handleEvent( const std::vector<int> windowDimensions, SDL_Event& event ){

        firstWall.handleEvent( event );

        secondWall.handleEvent( event );

        thirdWall.handleEvent( event );

        //  fourthWall.handleEvent( event );

        //  fifthWall.handleEvent( event );

        tomokoSprite.handleEvent( windowDimensions, event );

    }

    private:
    SDL_Renderer* renderer;

    std::string localPath;

    PlayerSprite tomokoSprite{ renderer, localPath + "tomoko-pixel.png" };

                //( x-value, y-value, width, height )
    Wall firstWall{{ 100.0f, 425.0f, 175.0f, 75.0f }};

                //( x-value, y-value, width, height )
    Wall secondWall{{ 310.0f, 350.0f, 175.0f, 150.0f }};

                //( x-value, y-value, width, height )
    Wall thirdWall{{ 500.0f, 275.0f, 175.0f, 225.0f }};

                //( x-value, y-value, width, height )
    //  Wall fourthWall{{ 275.0f, 125.0f, 250.0f, 75.0f }};

                //( x-value, y-value, width, height )
    //  Wall fifthWall{{ 350.0f, 150.0f, 250.0f, 50.0f }};

    void detectPlayerCollision(const float& objectX, const float& objectY, const float& objectW, const float& objectH ){

        //  const float ;
        //  const float ;
        //  const float ;
        //  const float ;

        if ( tomokoSprite.getX() + tomokoSprite.getWidth() > objectX && tomokoSprite.getX() + tomokoSprite.getWidth() < objectX + objectW ){

            if  ( tomokoSprite.getY() > objectY && tomokoSprite.getY() < objectY + objectH ){

                tomokoSprite.updateY(-15.0f);
                
                //  if ( tomokoSprite.getY() + ( tomokoSprite.getHeight() / 2 ) <= objectY + ( objectH / 2 ) ) 

                //  else if ( tomokoSprite.getY() + ( tomokoSprite.getHeight() / 2 ) > objectY + ( objectH / 2 ) ) tomokoSprite.updateY(15.0f);
                

                if ( tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if (  tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);


            } 
            else if ( tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getY() + tomokoSprite.getHeight() < objectY + objectH ){

                tomokoSprite.updateY(-15.0f);
                

                if ( tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if (  tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);

            }

        }
        else if ( tomokoSprite.getX() > objectX && tomokoSprite.getX() < objectX + objectW ){

            if  ( tomokoSprite.getY() > objectY && tomokoSprite.getY() < objectY + objectH ){

                tomokoSprite.updateY(-15.0f);
                

                if ( tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if (  tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);


            } 
            else if ( tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getY() + tomokoSprite.getHeight() < objectY + objectH ){

                tomokoSprite.updateY(-15.0f);
                

                if ( tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) > objectX + ( objectW / 2 ) ) tomokoSprite.updateX(2.5f);

                else if (  tomokoSprite.getY() + tomokoSprite.getHeight() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);

                else if ( tomokoSprite.getY() > objectY && tomokoSprite.getX() + ( tomokoSprite.getWidth() / 2 ) < objectX + ( objectW / 2 ) ) tomokoSprite.updateX(-2.5f);


            }

        }

    }

};
