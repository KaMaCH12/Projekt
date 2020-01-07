#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/System/Clock.h>
#include "assets.h"

int gravity=10;

void GameLoop(sfRenderWindow* window)
{
    sfEvent event;
    sfClock* clock;
    
    player ship=ship_new(400.0,400.0,10);
    clock=sfClock_create();
    
    while(sfRenderWindow_isOpen(window))
    {
	float ElapsedTime=0;
	sfClock_restart(clock);
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
		    ship.Vspeed-=100;
		}
	    }
	}

	//ruch
	sfSprite_move(ship.spr,vec2d(ship.Hspeed,ship.Vspeed));
	if(ship.Vspeed<=0)ship.Vspeed+=gravity;

	//drawing
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,ship.spr,NULL);

	while(ElapsedTime<17)ElapsedTime = sfTime_asMilliseconds(sfClock_getElapsedTime(clock));
	sfRenderWindow_display(window);
    }
}
