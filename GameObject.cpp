#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Collision.h"
#include "Map"

bool GameObject::checkCollision2( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    /*if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }*/

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB ) return false;
    return true;
}



GameObject::GameObject(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;

    xvel = 0;
    yvel = 0;

    startTime = 0;
    jumpTime = 0;

    status = standing;
    onGround = true;

    srcRect.h = KING_HEIGHT;
    srcRect.w = KING_WIDTH;
    srcRect.x = 4;
    srcRect.y = 9;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = xpos;
    destRect.y = ypos;

    collider.h = KING_HEIGHT;
    collider.w = KING_WIDTH;
    collider.x = xpos;
    collider.y = ypos;
}

bool GameObject::Collide(SDL_Rect &x, SDL_Rect Tile[][25], int Mapping[][25])
{
    for(int row = 0; row < 50; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            if( Mapping[row][column] != 3 && checkCollision2(x, Tile[row][column]) ) return true;
        }
    }
    return false;
}



void GameObject::RunLeft()
{
    status = running;
    xvel -= xspeed;
}

void GameObject::RunRight()
{
    status = running;
    xvel += xspeed;
}

void GameObject::PrepareJump()
{
    startTime = SDL_GetTicks();
}

void GameObject::Jump()
{
    jumpTime = SDL_GetTicks() - startTime;
    yvel = -(jumpTime * 0.02);
    if(yvel > -10) yvel = -10;
    if(yvel < -25) yvel = -25;
    startTime = 0;
    jumpTime = 0;
}

void GameObject::StopRunRight()
{
    xvel = 0;
    status = standing;
}

void GameObject::StopRunLeft()
{
    xvel = 0;
    status = standing;
}

void GameObject::Update(SDL_Rect Tile[][25], int Mapping[][25])
{
    yvel += gravity;
    if(yvel > MAX_FALL_SPEED) yvel = MAX_FALL_SPEED;
    if(status == running || status == standing)
    {
        xpos += xvel;
        collider.x = xpos;

        /*if( ( xpos < 0 ) || ( xpos + KING_WIDTH > LEVEL_WIDTH ) || Collide(collider, Tile, Mapping) )
        {
            xpos -= xvel;
            collider.x = xpos;
        }*/

        for(int row = 0; row < 50; row++)
        {
            for(int column = 0; column < 25; column++)
            {
                if( Mapping[row][column] != 3 && checkCollision2(collider, Tile[row][column]) )
                {
                    if(xvel > 0)
                    {
                        xpos = Tile[row][column].x - KING_WIDTH;
                        xvel = 0;
                    }
                    else if(xvel < 0)
                    {
                        xpos = Tile[row][column].x + TILE_WIDTH;
                        xvel = 0;
                    }
                    collider.x = xpos;
                }
            }
        }

        ypos += yvel;
        collider.y = ypos;

        for(int row = 0; row < 50; row++)
        {
            for(int column = 0; column < 25; column++)
            {
                if( Mapping[row][column] != 3 && checkCollision2(collider, Tile[row][column]) )
                {
                    if(yvel > 0)
                    {
                        ypos = Tile[row][column].y - KING_HEIGHT;
                        yvel = 0;
                        onGround = true;
                    }
                    else if(yvel < 0)
                    {
                        ypos = Tile[row][column].y + KING_HEIGHT;
                        yvel = 0;
                    }
                    collider.y = ypos;
                }
            }
        }

        /*if( ( ypos < 0 ) || ( ypos + KING_HEIGHT > LEVEL_HEIGHT ) || Collide(collider, Tile, Mapping) )
        {
            ypos -= yvel;
            collider.y = ypos;
        }*/

        Camera.y = ( ypos + KING_HEIGHT/2) - SCREEN_HEIGHT / 2;
        if( Camera.y < 0 )
        {
            Camera.y = 0;
        }
        if( Camera.y > LEVEL_HEIGHT - Camera.h )
        {
            Camera.y = LEVEL_HEIGHT - Camera.h;
        }
    }
    destRect.x = xpos;
    destRect.y = ypos - Camera.y;
}


/*void GameObject::Update(SDL_Rect Tile[][25], int Mapping[][25])
{
    //yvel += gravity;
    if(yvel >= MAX_FALL_SPEED) yvel = MAX_FALL_SPEED;
    CheckMap(Tile, Mapping);
    destRect.x = xpos;
    Camera.y = ( ypos + KING_HEIGHT/2) - SCREEN_HEIGHT / 2;
    if( Camera.y < 0 )
    {
        Camera.y = 0;
    }
    if( Camera.y > LEVEL_HEIGHT - Camera.h )
    {
        Camera.y = LEVEL_HEIGHT - Camera.h;
    }
    destRect.y = ypos - Camera.y;
}
*/
void GameObject::CheckMap(SDL_Rect Tile[][25], int Mapping[][25])
{
    /*int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    x1 = (xpos + xvel)/TILE_WIDTH;
    x2 = (xpos + xvel + KING_WIDTH - 1)/TILE_WIDTH;

    y1 = ypos/TILE_HEIGHT;
    y2 = (ypos + KING_HEIGHT -1)/TILE_HEIGHT;

    if(x1 >= 0 && x2 <= 24 && y1 >= 0 && y2 <= 49)
    {
        if(xvel > 0)
        {
            if(Mapping[y1][x2] != 3 && Mapping[y2][x2] !=3)
            {
                xpos = x2*TILE_WIDTH;
                xpos -= (KING_WIDTH +1);
                xvel = 0;
            }
        }
        else if(xvel < 0)
        {
            if(Mapping[y1][x1] != 3 && Mapping[y2][x1] !=3)
            {
                xpos = (x1 + 1)*TILE_WIDTH;
                xvel = 0;
            }
        }
    }

    x1 = (xpos)/TILE_WIDTH;
    x2 = (xpos + KING_WIDTH)/TILE_WIDTH;

    y1 = (ypos + yvel)/TILE_HEIGHT;
    y2 = (ypos + yvel + KING_HEIGHT -1)/TILE_HEIGHT;

    if(x1 >= 0 && x2 <= 24 && y1 >= 0 && y2 <= 49)
    {
        if(yvel > 0)
        {
            if(Mapping[y2][x1] != 3 && Mapping[y2][x2] !=3)
            {
                ypos = y2*TILE_HEIGHT;
                ypos -= (KING_HEIGHT);
                yvel = 0;
                onGround = true;
            }
        }
        else if(yvel < 0 )
        {
            if(Mapping[y1][x1] != 3 && Mapping[y1][x2] !=3)
            {
                ypos = (y1 + 1)*TILE_HEIGHT;
                yvel = 0;
            }
        }
    }

    xpos += xvel;
    ypos += yvel;
    //if (xpos < 0) xpos = 0;
   // else if(xpos + KING_WIDTH > SCREEN_WIDTH) xpos = SCREEN_WIDTH - KING_WIDTH;
   // if (ypos < 0) ypos = 0;
   // else if(ypos + KING_HEIGHT > LEVEL_HEIGHT) ypos = LEVEL_HEIGHT - KING_HEIGHT;
   */


}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::ObjectClose()
{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}
