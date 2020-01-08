#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/System/Clock.h>
#include <stdio.h>
#include "assets.h"

#define JumpForce 50

int gravity=5,gamespeed=10;

void GameLoop(sfRenderWindow* window)
{
    sfSprite* Background1;
    sfSprite* Background2;
    sfSprite* Background3;
    sfEvent event;
    sfClock* frame;
    
    player ship=ship_new(200.0,400.0,10);
    frame=sfClock_create();
    
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();

    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    
    while(sfRenderWindow_isOpen(window))
    {
	float ElapsedTime=0;
	sfClock_restart(frame);
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,ship.spr,NULL);
	

	//eventy
	while(sfRenderWindow_pollEvent(window, &event))
	{
	    if(event.type==sfEvtClosed)sfRenderWindow_close(window);
	    if(event.type==sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    ship.Vspeed-=JumpForce;
		}
	    }
	}

	//ruch statku
	sfSprite_move(ship.spr,vec2d(ship.Hspeed,ship.Vspeed));
	if(ship.Vspeed<=0)ship.Vspeed+=gravity;

	//ruch asteroid i powerupow

	//ruch tla
	sfSprite_move(Background1,vec2d(-gamespeed*2,0));
	sfSprite_move(Background2,vec2d(-gamespeed,0));
	sfSprite_move(Background3,vec2d(-gamespeed/4,0));
	if(sfSprite_getPosition(Background1).x<=-2400)
	    sfSprite_setPosition(Background1,vec2d(0.0,0.0));
	if(sfSprite_getPosition(Background2).x<=-2400)
	    sfSprite_setPosition(Background2,vec2d(0.0,0.0));
	if(sfSprite_getPosition(Background3).x<=-2400)
	    sfSprite_setPosition(Background3,vec2d(0.0,0.0));

	//kolizje

	//drawing
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_drawSprite(window,ship.spr,NULL);

	while(ElapsedTime<17)ElapsedTime = sfTime_asMilliseconds(sfClock_getElapsedTime(frame));
	sfRenderWindow_display(window);
    }
}
