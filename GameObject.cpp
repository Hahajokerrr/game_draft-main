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

    angle = 0;
    angletan = 0;

    startTime = 0;
    jumpTime = 0;

    frame = 0;

    status = standing;
    onGround = true;

    inputType.left = 0;
    inputType.right = 0;
    inputType.space = 0;
    inputType.jumpleft = 2;
    inputType.jumpright = 2;

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

void GameObject::CollideVertical(SDL_Rect &col, SDL_Rect Tile[][25], int Mapping[][25])
{

    for(int row = 0; row < 50; row++)
        {
            for(int column = 0; column < 25; column++)
            {
                if( Mapping[row][column] != 3 && checkCollision2(col, Tile[row][column]) )
                {
                    if(yvel > 0)
                    {
                        ypos = Tile[row][column].y - KING_HEIGHT;
                        yvel = 0;
                        onGround = true;
                        status = standing;
                    }
                    else if(yvel < 0)
                    {
                        ypos = Tile[row][column].y + KING_HEIGHT;
                        yvel = 0;
                    }
                    col.y = ypos;
                }
            }
        }
}
void GameObject::CollideHorizontal(SDL_Rect &col, SDL_Rect Tile[][25], int Mapping[][25])
{
    for(int row = 0; row < 50; row++)
        {
            for(int column = 0; column < 25; column++)
            {
                if( Mapping[row][column] != 3 && checkCollision2(col, Tile[row][column]) )
                {
                    if(xvel > 0)
                    {
                        if(onGround == true)
                        {
                            xpos = Tile[row][column].x - KING_WIDTH;
                            xvel = 0;
                        }
                        else if(onGround == false)
                        {
                            xpos = Tile[row][column].x - KING_WIDTH;
                            xvel = -xvel;
                            if(xvel > -1) xvel = -1;
                        }
                    }
                    else if(xvel < 0)
                    {
                        if(onGround == true)
                        {
                            xpos = Tile[row][column].x + TILE_WIDTH;
                            xvel = 0;
                        }
                        else if(onGround == false)
                        {
                            xpos = Tile[row][column].x + TILE_WIDTH;
                            xvel = -xvel;
                            if(xvel < 1) xvel = 1;
                        }
                    }
                    col.x = xpos;
                }
            }
        }
}


void GameObject::RunLeft()
{
    status = running;
    xvel -= xspeed;
    if(xvel < -maxxspeed) xvel = -maxxspeed;
}

void GameObject::RunRight()
{
    status = running;
    xvel += xspeed;
    if(xvel > maxxspeed) xvel = maxxspeed;
}

void GameObject::PrepareJump()
{
    startTime = SDL_GetTicks();
    status = charging;

}

void GameObject::Jump()
{
    jumpTime = SDL_GetTicks() - startTime;
    status = jumping;
    yvel = -(jumpTime * 0.02);
    if(yvel > -10) yvel = -10;
    if(yvel < -20) yvel = -20;

    onGround = false;

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
    if(onGround == true )
    {
        if(inputType.right == 1) RunRight();
        if(inputType.left == 1) RunLeft();
        if(inputType.right == 2) StopRunRight();
        if(inputType.left == 2) StopRunLeft();
    }

    yvel += gravity;
    if(yvel > MAX_FALL_SPEED) yvel = MAX_FALL_SPEED;


    ypos += yvel;
    collider.y = ypos;

    CollideVertical(collider, Tile, Mapping);

    xpos += xvel;
    collider.x = xpos;

    CollideHorizontal(collider, Tile, Mapping);

    Camera.y = ( ypos + KING_HEIGHT/2) - SCREEN_HEIGHT / 2;
    if( Camera.y < 0 )
    {
        Camera.y = 0;
    }
    if( Camera.y > LEVEL_HEIGHT - Camera.h )
    {
        Camera.y = LEVEL_HEIGHT - Camera.h;
    }
    destRect.x = xpos;
    destRect.y = ypos - Camera.y;

    frame++;
    if(frame%5 == 0) cout << status << endl;
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
