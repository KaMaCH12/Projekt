#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include "extra.h"

player ship_new(sfVector2f position)
{
    player Statek;
    sfTexture* img;
    Statek.spr=sfSprite_create();
    img=sfTexture_createFromFile("./images/statek.png",NULL);
    sfSprite_setPosition(Statek.spr,position);
    sfSprite_setTexture(Statek.spr,img,sfTrue);
    Statek.Vspeed=gravity;
    Statek.Hspeed=0;
    return Statek;
}

asteroid* make_asteroid(int type,sfVector2f position,int speed,int rotation)
{
    asteroid* ROCK=malloc(sizeof(struct asteroid));
    sfTexture* img;
    ROCK->spr=sfSprite_create();
    switch(type)
    {
	case 1:
	    img=sfTexture_createFromFile("./images/Asteroida1.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(76/2,71/2));
	    break;
	case 2:
	    img=sfTexture_createFromFile("./images/Asteroida2.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,50));
	    break;
	case 3:
	    img=sfTexture_createFromFile("./images/Asteroida3.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,75));
	    break;
    }
    ROCK->Rspeed=rotation;
    sfSprite_setPosition(ROCK->spr,position);
    sfSprite_setTexture(ROCK->spr,img,sfTrue);
    ROCK->Vspeed=0;
    ROCK->Hspeed=speed;
    return ROCK;
}

void asteroid_factory(vector* v)
{
    asteroid* ROCK;
    ROCK=make_asteroid(1,vec2d(0,0),gamespeed,0);
    vector_add(v,ROCK);
}

asteroid* destroy_asteroid(asteroid* ROCK)
{
    free(ROCK->spr);
    free(ROCK);
    return NULL;
}
