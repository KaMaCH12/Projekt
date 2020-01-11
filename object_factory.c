#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    sfSprite_setRotation(ROCK->spr,rotation);
    sfSprite_setPosition(ROCK->spr,position);
    sfSprite_setTexture(ROCK->spr,img,sfTrue);
    ROCK->Vspeed=0;
    ROCK->Hspeed=speed;
    return ROCK;
}

void asteroid_factory(vector* v,int seed)
{
    srand(seed);
    asteroid* ROCK;
    ROCK=make_asteroid(rand()%3+1,vec2d(900,rand()%800),gamespeed,(rand()%360));
    vector_add(v,ROCK);
}

void asteroid_move(vector* v)
{
    asteroid* ROCK;
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	sfSprite_move(ROCK->spr,vec2d(-ROCK->Hspeed,ROCK->Vspeed));
	//sfSprite_rotate(ROCK->spr,ROCK->Rspeed);
    }
}

void asteroid_draw(sfRenderWindow* window,vector* v)
{
    asteroid* ROCK;
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	sfRenderWindow_drawSprite(window,ROCK->spr,NULL);
    }
}

void destroy_asteroid(asteroid* ROCK)
{
    free(ROCK->spr);
    free(ROCK);
}

void asteroid_cleaner(vector *v)
{
    asteroid* ROCK;
    sfVector2f position;
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	if(sfSprite_getPosition(ROCK->spr).x<-100)
	{
	    destroy_asteroid(ROCK);
	    vector_delete(v,i);
	}
    }
    
}

