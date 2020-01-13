#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extra.h"

player ship_new(sfVector2f position)
{
    player Statek;
    Statek.ammo=0;
    Statek.shield=0;
    sfTexture* img;
    Statek.spr=sfSprite_create();
    img=sfTexture_createFromFile("./images/statek.png",NULL);
    sfSprite_setPosition(Statek.spr,position);
    sfSprite_setTexture(Statek.spr,img,sfTrue);
    Statek.Vspeed=gravity;
    Statek.Hspeed=0;
    return Statek;
}

object* make_object(int type,sfVector2f position,int speed,int rotation)
{
    object* ROCK=malloc(sizeof(struct object));
    ROCK->spr=sfSprite_create();
    switch(type)
    {
	case 1:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida1.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(76/2,71/2));
	    ROCK->type=1;
	    break;
	case 2:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida2.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,50));
	    ROCK->type=2;
	    break;
	case 3:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida3.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,75));
	    ROCK->type=3;
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
    object* ROCK;
    ROCK=make_object(rand()%3+1,vec2d(900,rand()%800),gamespeed,(rand()%360));
    vector_add(v,ROCK);
}

void powerup_factory(vector* v,int seed)
{
    srand(seed);
    object* OBJ;
    OBJ=make_object(rand()%2+4,vec2d(900,rand()%800),gamespeed,0);
    vector_add(v,OBJ);
}

void object_move(vector* v)
{
    object* ROCK;
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	sfSprite_move(ROCK->spr,vec2d(-ROCK->Hspeed,ROCK->Vspeed));
	//sfSprite_rotate(ROCK->spr,ROCK->Rspeed);
    }
}

void object_draw(sfRenderWindow* window,vector* v)
{
    object* ROCK;
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	sfRenderWindow_drawSprite(window,ROCK->spr,NULL);
    }
}

void destroy_object(object* ROCK)
{
    sfTexture_destroy(ROCK->img);
    sfSprite_destroy(ROCK->spr);
    free(ROCK);
}

void object_cleaner(vector *v)
{
    object* ROCK;
    sfVector2f position;
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	if(sfSprite_getPosition(ROCK->spr).x<-100)
	{
	    destroy_object(ROCK);
	    vector_delete(v,i);
	}
    }
}

int collision_checker(vector *v,player* SHIP)
{
    object* OBJ;
    sfFloatRect ship_hitbox;
    sfFloatRect obj_hitbox;
    sfFloatRect intersection;
    ship_hitbox=sfSprite_getGlobalBounds(SHIP->spr);
    for(int i=0;i<v->total;i++)
    {
	OBJ=v->items[i];
	obj_hitbox=sfSprite_getGlobalBounds(OBJ->spr);
	if(sfFloatRect_intersects(&ship_hitbox,&obj_hitbox,&intersection))
	{
		if(OBJ->type<4&&intersection.width*intersection.height>ColTolerance)return 1;
	}
    }
    return 0;
}

