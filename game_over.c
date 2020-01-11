#include <SFML/Graphics.h>

sfEvent event;
sfSprite* GameOverScreen;

sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;

void game_over(sfRenderWindow* window,int Score_int)
{
    GameOverScreen=sfSprite_create();

    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();

    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    
    sfSprite_setTexture(GameOverScreen,sfTexture_createFromFile("./images/GameOverScreen.png"));

    while(sfRenderWindow_isOpen(window))
    {
	while(sfRenderWindow_pollEvent(window,&event))
	{
	    if(event.type==sfEvtClosed)sfRenderWindow_close(window);
	    if(event.type==sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    return;
		}
	    }
	}
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_display(window);
    }
}
