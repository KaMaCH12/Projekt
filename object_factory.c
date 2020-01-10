#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include "extra.h"

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

asteroid* make_asteroid(int type,sfVector2f position,int speed)
{
    asteroid* ROCK=malloc(sizeof(struct asteroid));
    sfTexture* img;
    ROCK->spr=sfSprite_create();
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
    sfSprite_setPosition(ROCK->spr,position);
    sfSprite_setTexture(ROCK->spr,img,sfTrue);
    ROCK->Vspeed=0;
    ROCK->Hspeed=speed;
    return ROCK;
}
