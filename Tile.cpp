#include "Tile.h"

#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Collision.h"

SDL_Rect gTileClips [ TILE_NUMBERS ];


Tile::Tile( int x, int y, int tileType )
{
    mBox.x = x;
    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = tileType;

    mTexture = TextureManager::LoadTexture("image/SpriteTile.png");
}

void Tile::render( SDL_Rect& camera )
{
    if( checkCollision( camera, mBox ) )
    {
        destRect.x = mBox.x - camera.x;
        destRect.y = mBox.y - camera.y;
        destRect.w = TILE_WIDTH;
        destRect.h = TILE_HEIGHT;

        TextureManager::Draw(mTexture, &gTileClips[ mType ], destRect)
    }
}

void Tile::CloseTile()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}
