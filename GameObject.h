#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Game.h"
#include <math.h>

#define gravity 0.8
#define MAX_FALL_SPEED 20

using namespace std;

enum condition { standing, running, charging, jumping, falling, };
typedef struct Input
{
    int left;
    int right;
    int space;
    int jumpleft;
    int jumpright;
};


class GameObject
{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    friend void Game::handleEvents();

    SDL_Rect GetCollider() { return collider; }

    void Update(SDL_Rect Tile[][25], int Mapping[][25]);

    void RunLeft();
    void RunRight();
    void RunUp();
    void RunDown();
    void PrepareJump();
    void Jump();
    void StopRunRight();
    void StopRunLeft();
    void StopRunUp();
    void StopRunDown();

    void Render();
    void ObjectClose();

    void CollideVertical(SDL_Rect &col, SDL_Rect Tile[][25], int Mapping[][25]);
    void CollideHorizontal(SDL_Rect &col, SDL_Rect Tile[][25], int Mapping[][25]);
    bool checkCollision2( SDL_Rect a, SDL_Rect b );

    void CalculateAngle();

    int Getxspeed(){ return xspeed; }
    int Getxvel() { return xvel; }
    int Getyvel() { return yvel; }


    static const int xspeed = 1;
    static const int yspeed = 1;

    static const int maxxspeed = 8;
    static const int maxyspeed = 8;


    static const int KING_WIDTH = 32;
    static const int KING_HEIGHT = 32;

    SDL_Rect Camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};



private:

    double xpos;
    double ypos;

    double xvel;
    double yvel;

    double angle;
    double angletan;

    int frame;

    Uint32 startTime;
    int jumpTime;

    SDL_Texture* objTexture = NULL;
    SDL_Rect srcRect, destRect, collider;

    condition status;
    Input inputType;
    bool onGround;
};
#endif // GAMEOBJECT_H_INCLUDED
