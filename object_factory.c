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
    ROCK->spr=sfSprite_create();
    switch(type)
    {
	case 1:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida1.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(76/2,71/2));
	    break;
	case 2:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida2.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,50));
	    break;
	case 3:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida3.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,75));
	    break;
    }
    ROCK->Rspeed=rotation;
    sfSprite_setRotation(ROCK->spr,rotation);
    sfSprite_setPosition(ROCK->spr,position);
    sfSprite_setTexture(ROCK->spr,ROCK->img,sfTrue);
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
    sfTexture_destroy(ROCK->img);
    sfSprite_destroy(ROCK->spr);
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

int collision_checker(vector *v,player* SHIP)
{
    asteroid* ROCK;
    sfFloatRect ship_hitbox;
    sfFloatRect rock_hitbox;
    sfFloatRect intersection;
    ship_hitbox=sfSprite_getGlobalBounds(SHIP->spr);
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	rock_hitbox=sfSprite_getGlobalBounds(ROCK->spr);
	if(sfFloatRect_intersects(&ship_hitbox,&rock_hitbox,&intersection))return 1;
    }
    return 0;
}

