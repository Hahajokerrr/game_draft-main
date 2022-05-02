#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Game.h"

class Tile
{
    public:
		Tile( int x, int y, int tileType );

		void render( SDL_Rect& camera );

		int getType();

		SDL_Rect getBox();

		void CloseTile();

    private:
		SDL_Rect mBox, destRect;
		SDL_Texture* mTexture;

		int mType;
};

#endif // TILE_H_INCLUDED
