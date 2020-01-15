#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include "main.h"


char* name;
sfRenderWindow* window;
sfEvent event;
sfSprite* TitleScreen;
sfFont* dotty;

sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;

int Score_int;

int main()
{
    name=malloc(sizeof(char)*100);
    dotty=sfFont_createFromFile("./fonts/dotty.ttf");

    sfVideoMode mode={GameWidth,GameHeight,32};

    window=sfRenderWindow_create(mode,"Space Commander",sfClose,NULL);
    sfRenderWindow_setKeyRepeatEnabled(window,sfFalse);

    TitleScreen=sfSprite_create();
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();

    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    sfSprite_setTexture(TitleScreen,sfTexture_createFromFile("./images/TitleScreen.png",NULL),sfTrue);
    while(sfRenderWindow_isOpen(window))
    {
	while (sfRenderWindow_pollEvent(window, &event))
	{
	    if (event.type == sfEvtClosed)sfRenderWindow_close(window);
	    if (event.type == sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    Score_int=GameLoop(window,dotty);
    		    name=game_over(window,Score_int,dotty,name);
		}
		if(event.key.code==sfKeyDown)
		{
		    highscores(window,dotty);
		}
	    }
	}
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_drawSprite(window,TitleScreen,NULL);
	sfRenderWindow_display(window);
    }
}