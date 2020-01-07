#include <SFML/Graphics.h>
#include <SFML/System.h>

#define GameWidth 800
#define GameHeight 800

void GameLoop(sfRenderWindow*);

sfRenderWindow* window;
sfEvent event;
sfSprite* play;
sfTexture* play_but;

int main()
{

    sfVideoMode mode={GameWidth,GameHeight,32};

    window=sfRenderWindow_create(mode,"Space Commander",sfClose,NULL);
    play=sfSprite_create();

    play_but=sfTexture_createFromFile("statek.png",NULL);
    sfSprite_setTexture(play,play_but,sfTrue);
    while(sfRenderWindow_isOpen(window))
    {
	while (sfRenderWindow_pollEvent(window, &event))
	{
	    if (event.type == sfEvtClosed)sfRenderWindow_close(window);
	    if (event.type == sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    GameLoop(window);
		}
	    }
	}
	sfRenderWindow_drawSprite(window,play,NULL);
	sfRenderWindow_display(window);
    }
}
