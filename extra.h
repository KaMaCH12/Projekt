#include <SFML/System.h>
#include <SFML/Graphics.h>

typedef struct Ship
{
    sfSprite* spr;
    sfVector2f pos;
    float Vspeed;
    float Hspeed;
}player;

typedef struct asteroid
{
    sfSprite* spr;
    sfVector2f pos;
    float Vspeed;
    float Hspeed;
}asteroid;

sfVector2f vec2d(float x,float y)
{
    sfVector2f vec;
    vec.x=x;
    vec.y=y;
    return vec;
}
