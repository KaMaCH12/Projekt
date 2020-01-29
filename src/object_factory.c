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
    sfSprite_setOrigin(Statek.spr,vec2d(40,15));
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
    object* ROCK=malloc(sizeof(object));
    ROCK->spr=sfSprite_create();
    switch(type)
    {
	case 1:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida1.png",NULL);
//	    sfSprite_setOrigin(ROCK->spr,vec2d(76/2,71/2));
	    ROCK->type=1;
	    break;
	case 2:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida2.png",NULL);
//	    sfSprite_setOrigin(ROCK->spr,vec2d(75,50));
	    ROCK->type=2;
	    break;
	case 3:
	    ROCK->img=sfTexture_createFromFile("./images/Asteroida3.png",NULL);
//	    sfSprite_setOrigin(ROCK->spr,vec2d(75,75));
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
    ROCK=make_object(rand()%3+1,vec2d(1000,rand()%700),gamespeed,(rand()%360));
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
    sfSprite_setRotation(ship->spr,ship->Vspeed-4);
    sfRenderWindow_drawSprite(window,ship->spr,NULL);
    if(ship->shield>0)
    {
	sfSprite_setRotation(ship_shield,ship->Vspeed-4);
	sfVector2f pos=sfSprite_getPosition(ship->spr);
	sfSprite_setPosition(ship_shield,pos);
	sfRenderWindow_drawSprite(window,ship_shield,NULL);
    }
    if(ship->ammo>0)
    {
	sfSprite_setRotation(ship_rocket,ship->Vspeed-4);
	sfVector2f pos=sfSprite_getPosition(ship->spr);
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
    for(int i=0;i<v->total;i++)
    {
	ROCK=v->items[i];
	if(sfSprite_getPosition(ROCK->spr).x<-150)
	{
	    vector_delete(v,i);
	    destroy_object(ROCK);
	}
	else if(sfSprite_getPosition(ROCK->spr).x>900&&ROCK->type==6)
	{
	    vector_delete(v,i);
	    destroy_object(ROCK);
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

int pixel_perfect_checker(object*,player*,sfFloatRect);

int collision_checker(vector *v,player* SHIP)
{
    object* OBJ;
    sfFloatRect ship_hitbox;
    sfFloatRect obj_hitbox;
    sfFloatRect intersection;
    ship_hitbox=sfSprite_getGlobalBounds(SHIP->spr);
    if(sfSprite_getPosition(SHIP->spr).y+ship_hitbox.height < 20||sfSprite_getPosition(SHIP->spr).y>830)return 1;
    for(int i=0;i<v->total;i++)
    {
	OBJ=v->items[i];
	obj_hitbox=sfSprite_getGlobalBounds(OBJ->spr);
	if(sfFloatRect_intersects(&ship_hitbox,&obj_hitbox,&intersection))
	{
		if(OBJ->type<4&&pixel_perfect_checker(OBJ,SHIP,intersection)==1)
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

int pixel_perfect_checker(object* OBJ,player* SHIP,sfFloatRect intersection)
{
    int xMax=intersection.left+intersection.width;
    int yMax=intersection.top+intersection.height;
    
    sfImage* imgA=sfTexture_copyToImage(SHIP->img);
    sfImage* imgB=sfTexture_copyToImage(OBJ->img);

    const sfVector2u sizeA=sfImage_getSize(imgA);
    const sfVector2u sizeB=sfImage_getSize(imgB);
    
    const sfUint8* pixA;
    const sfUint8* pixB;
    
    pixA=sfImage_getPixelsPtr(imgA);
    pixB=sfImage_getPixelsPtr(imgB);
    
    sfVector2f vecA,vecB;

    const sfTransform invA=sfSprite_getInverseTransform(SHIP->spr);
    const sfTransform invB=sfSprite_getInverseTransform(OBJ->spr);

    //sprawdzanie czy piksele sie nakladaja
    for(int x=intersection.left;x<xMax;x++)
    {
	for(int y=intersection.top;y<yMax;y++)
	{
	    vecA=sfTransform_transformPoint(&invA,vec2d(x,y));
	    vecB=sfTransform_transformPoint(&invB,vec2d(x,y));
	    int idxA=((int)vecA.x+((int)vecA.y)*sizeA.x)*4+3;
	    int idxB=((int)vecB.x+((int)vecB.y)*sizeB.x)*4+3;
	    if(vecA.x>0&&vecA.y>0&&vecB.x>0&&vecB.y>0&&vecA.x<sizeA.x&&vecA.y<sizeA.y&&vecB.x<sizeB.x&&vecB.y<sizeB.y&&pixA[idxA]>0&&pixB[idxB]>0)
	    {
		sfImage_destroy(imgA);
		sfImage_destroy(imgB);
		return 1;
	    }
	}
    }
    sfImage_destroy(imgA);
    sfImage_destroy(imgB);
    return 0;
}
