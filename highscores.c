#include <SFML/Graphics.h>

sfEvent event;

sfSprite* Highscores;
sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;

void highscores(sfRenderWindow* window,sfFont* dotty)
{
    Highscores=sfSprite_create();
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();

    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    sfSprite_setTexture(Highscores,sfTexture_createFromFile("./images/Highscores.png",NULL),sfTrue);
    while(sfRenderWindow_isOpen(window))
    {
	while (sfRenderWindow_pollEvent(window, &event))
	{
	    if (event.type == sfEvtClosed)sfRenderWindow_close(window);
	    if (event.type == sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    return;
		}
		if(event.key.code==sfKeyDown)
		{
		    return;
		}
	    }
	}
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_drawSprite(window,Highscores,NULL);
	sfRenderWindow_display(window);
    }
    
}
