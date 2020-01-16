#include <SFML/Graphics.h>
#include "highscores.h"

void highscores(sfRenderWindow* window,sfFont* font)
{
    char Highscore_string[1000];
    
    //przygotowanie wyswietania poszczegolnych wynikow
    read_score(Highscore_string);
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
