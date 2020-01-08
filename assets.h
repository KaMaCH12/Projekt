#include <stdlib.h>
#include <SFML/Graphics.h>
#include "extra.h"

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

player ship_new(float x,float y,int gravity)
{
    player Statek;
    sfTexture* img;
    Statek.spr=sfSprite_create();
    img=sfTexture_createFromFile("./images/statek.png",NULL);
    sfSprite_setPosition(Statek.spr,vec2d(x,y));
    sfSprite_setTexture(Statek.spr,img,sfTrue);
    Statek.Vspeed=gravity;
    Statek.Hspeed=0;
    return Statek;
}

asteroid* asteroid_new(int type,float x,float y,int speed)
{
    asteroid* Skala=malloc(sizeof(struct asteroid));
    sfTexture* img;
    Skala->spr=sfSprite_create();
    switch(type)
    {
	case 1:
	    img=sfTexture_createFromFile("./images/Asteroida1.png",NULL);
	    break;
	case 2:
	    img=sfTexture_createFromFile("./images/Asteroida2.png",NULL);
	    break;
	case 3:
	    img=sfTexture_createFromFile("./images/Asteroida3.png",NULL);
	    break;
    }
    sfSprite_setPosition(Skala->spr,vec2d(x,y));
    sfSprite_setTexture(Skala->spr,img,sfTrue);
    Skala->Vspeed=0;
    Skala->Hspeed=speed;
    return Skala;
}

void asteroid_destroy(asteroid* skala)
{
    sfSprite_destroy(skala->spr);
    free(skala);
    skala=NULL;
}

