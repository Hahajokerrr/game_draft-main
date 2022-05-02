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

    if( bottomA <= topB )
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
    }

    return true;
}

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;

    xvel = 0;
    yvel = 0;

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
    xvel -= xspeed;
}

void GameObject::RunRight()
{
    xvel += xspeed;
}

void GameObject::Jump()
{
    yvel -= yspeed;
}

void GameObject::Stop()
{
    xvel = 0;
    yvel = 0;
}

void GameObject::Update(SDL_Rect Tile[][25], int Mapping[][25])
{
    xpos += xvel;
    collider.x = xpos;

    if( ( xpos < 0 ) || ( xpos + KING_WIDTH > LEVEL_WIDTH ) || Collide(collider, Tile, Mapping) )
    {
        xpos -= xvel;
        collider.x = xpos;
    }

    destRect.x = xpos;

    ypos += yvel;
    collider.y = ypos;

    if( ( ypos < 0 ) || ( ypos + KING_HEIGHT > LEVEL_HEIGHT ) || Collide(collider, Tile, Mapping) )
    {
        ypos -= yvel;
        collider.y = ypos;
    }

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

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::ObjectClose()
{
    SDL_DestroyTexture(objTexture);
    objTexture = NULL;
}
