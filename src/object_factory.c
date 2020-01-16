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
    Statek.spr=sfSprite_create();
    Statek.img=sfTexture_createFromFile("./images/statek.png",NULL);
    sfSprite_setPosition(Statek.spr,position);
    sfSprite_setTexture(Statek.spr,Statek.img,sfTrue);
    Statek.Vspeed=gravity;
    Statek.Hspeed=0;
    return Statek;
}

void ship_destroy(player* ship)
{
    sfTexture_destroy(ship->img);
    sfSprite_destroy(ship->spr);
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
	case 4:
	    ROCK->img=sfTexture_createFromFile("./images/Shield.png",NULL);
	    ROCK->type=4;
	    break;
	case 5:
	    ROCK->img=sfTexture_createFromFile("./images/Weapon.png",NULL);
	    ROCK->type=5;
	    break;
	case 6:
	    ROCK->img=sfTexture_createFromFile("./images/RocketFired.png",NULL);
	    sfSprite_setOrigin(ROCK->spr,vec2d(75,75));
	    ROCK->type=6;
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

void shoot(vector* v,player* ship)
{
    if(ship->ammo==0)return;
    ship->ammo=0;
    sfVector2f pos=sfSprite_getPosition(ship->spr);
    pos.y+=90;
    pos.x+=70;
    object* OBJ;
    OBJ=make_object(6,pos,-gamespeed/2,0);
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

void player_draw(sfRenderWindow* window,player* ship,sfSprite* ship_shield,sfSprite* ship_rocket)
{
    sfRenderWindow_drawSprite(window,ship->spr,NULL);
    if(ship->shield>0)
    {
	sfVector2f pos=sfSprite_getPosition(ship->spr);
	pos.x-=3;
	pos.y-=3;
	sfSprite_setPosition(ship_shield,pos);
	sfRenderWindow_drawSprite(window,ship_shield,NULL);
    }
    if(ship->ammo>0)
    {
	sfVector2f pos=sfSprite_getPosition(ship->spr);
	pos.y+=28;
	pos.x+=10;
	sfSprite_setPosition(ship_rocket,pos);
	sfRenderWindow_drawSprite(window,ship_rocket,NULL);
    }
}

void destroy_object(object* ROCK)
{
    sfTexture_destroy(ROCK->img);
    sfSprite_destroy(ROCK->spr);
    free(ROCK);
}

void destroy_sprite(sfSprite* OBJ)
{
    //sfTexture_destroy(sfSprite_getTexture(OBJ));
    sfSprite_destroy(OBJ);
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
	if(sfSprite_getPosition(ROCK->spr).x>900&&ROCK->type==6)
	{
	    destroy_object(ROCK);
	    vector_delete(v,i);
	}
    }
}

void object_purge(vector *v)
{
    object* OBJ;
    for(int i=0;i<v->total;i++)
    {
	OBJ=v->items[i];
	destroy_object(OBJ);
	vector_delete(v,i);
    }
}

void rocket_checker(vector *rockets,vector *objects)
{
    object* ROCKET;
    object* OBJ;
    sfFloatRect rckt_hitbox;
    sfFloatRect obj_hitbox;
    for(int i=0;i<rockets->total;i++)
    {
	ROCKET=rockets->items[i];
	rckt_hitbox=sfSprite_getGlobalBounds(ROCKET->spr);
	for(int j=0;j<objects->total;j++)
	{
	    OBJ=objects->items[j];
	    obj_hitbox=sfSprite_getGlobalBounds(OBJ->spr);
	    if(sfFloatRect_intersects(&rckt_hitbox,&obj_hitbox,NULL))
	    {
		destroy_object(ROCKET);
		destroy_object(OBJ);
		vector_delete(rockets,i);
		vector_delete(objects,j);
	    }
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
    if(sfSprite_getPosition(SHIP->spr).y+ship_hitbox.height<0||sfSprite_getPosition(SHIP->spr).y>800)return 1;
    for(int i=0;i<v->total;i++)
    {
	OBJ=v->items[i];
	obj_hitbox=sfSprite_getGlobalBounds(OBJ->spr);
	if(sfFloatRect_intersects(&ship_hitbox,&obj_hitbox,&intersection))
	{
		if(OBJ->type<4&&intersection.width*intersection.height>ColTolerance)
		{
		    if(SHIP->shield==1)
		    {
			destroy_object(OBJ);
			vector_delete(v,i);
			SHIP->shield=0;
		    }
		    else return 1;
		}
		if(OBJ->type==4)
		{
		    SHIP->shield=1;
		    destroy_object(OBJ);
		    vector_delete(v,i);
		}
		if(OBJ->type==5)
		{
		    SHIP->ammo=1;
		    destroy_object(OBJ);
		    vector_delete(v,i);
		}

	}
    }
    return 0;
}

