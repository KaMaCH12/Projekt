#include <SFML/Graphics.h>
#include "highscores.h"

sfEvent event;
sfText* Highscore_entries;
char Highscore_string[1000];
char String_left[500];
char String_right[500];

sfSprite* Highscores;
sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;

void highscores(sfRenderWindow* window,sfFont* font)
{
    //inicjalizacja planszy highscores
    Highscores=sfSprite_create();
    sfSprite_setTexture(Highscores,sfTexture_createFromFile("./images/Highscores.png",NULL),sfTrue);
    
    //inicjalizacja tla
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();
    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);

    //inicjalizacja wyswietania poszczegolnych wynikow
    read_score(Highscore_string);
    Highscore_entries=sfText_create();
    sfText_setFont(Highscore_entries,sfFont_copy(font));
    sfText_setCharacterSize(Highscore_entries,60);
    sfText_setString(Highscore_entries,Highscore_string);
    sfText_setPosition(Highscore_entries,vec2d(400-sfText_getGlobalBounds(Highscore_entries).width/2,300));

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
	sfRenderWindow_drawText(window,Highscore_entries,NULL);
	sfRenderWindow_display(window);
    }
    
}
