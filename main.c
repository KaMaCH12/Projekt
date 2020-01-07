#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/System/Clock.h>

int main()
{
    sfEvent event;
    sfClock* Clock;
    sfVideoMode mode={800,800,32};
    sfRenderWindow* window;
    sfTexture* ship;
    sfSprite* sprite;
    sfVector2f pos;
    pos.x=300;
    pos.y=400;

    sfVector2f skok;
    skok.x=0;
    skok.y=0;
    sfVector2f gravity;

    gravity.x=0;
    gravity.y=10;

    Clock =sfClock_create();

    window=sfRenderWindow_create(mode,"Czill utopia",sfClose,NULL);
    ship=sfTexture_createFromFile("statek.png",NULL);
    sprite=sfSprite_create();
    sfSprite_setPosition(sprite,pos);
    sfSprite_setTexture(sprite,ship,sfTrue);
    sfRenderWindow_setKeyRepeatEnabled(window,sfFalse);

    while(sfRenderWindow_isOpen(window))
    {
	float ElapsedTime=0;
	sfClock_restart(Clock);
	while (sfRenderWindow_pollEvent(window, &event))
	{
	    if (event.type == sfEvtClosed)sfRenderWindow_close(window);
	    if (event.type == sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    skok.y=-100;
		}
	    }
	}
	if(skok.y<=-10)skok.y+=10;
	sfSprite_move(sprite,skok);
	sfSprite_move(sprite,gravity);
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,sprite,NULL);
	while(ElapsedTime<17)ElapsedTime = sfTime_asMilliseconds(sfClock_getElapsedTime(Clock));
	sfRenderWindow_display(window);
    }
}
