#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_over.h"
#include "extra.h"

char* game_over(sfRenderWindow* window,int Score_int,sfFont* font,char* name)
{
    sfRenderWindow_setKeyRepeatEnabled(window,sfTrue);
    
    //inicjalizacja wyswietlania wyniku
    sfText_setFont(Score,sfFont_copy(font));
    sfText_setCharacterSize(Score,250);
    char Score_char[1000];
    sprintf(Score_char,"%d",Score_int);
    sfText_setString(Score,Score_char);
    sfText_setPosition(Score,vec2d(400-sfText_getGlobalBounds(Score).width/2,185));

    //inicjalizacja wprowadzania nazwy
    sfText_setFont(Name,sfFont_copy(font));
    sfText_setCharacterSize(Name,250);
    sfText_setString(Name,name);
    sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400));

    while(sfRenderWindow_isOpen(window))
    {
	while(sfRenderWindow_pollEvent(window,&event))
	{
	    if(event.type==sfEvtClosed)sfRenderWindow_close(window);
	    if(event.type==sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    if(name[0]!=' '&&name[str_length(name)-1]!=' ')
		    {
			save_score(name,Score_int);
			return name;
		    }
		}
		if(event.key.code==sfKeyBackspace)
		{
		    if(str_length(name)>0)
		    {
			str_delete(name);
			sfText_setString(Name,name);
			sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400));
		    }
		}
	    }
	    if(event.type==sfEvtTextEntered&&event.text.unicode!=8)
	    {
		int len=str_length(name);
		if(len<20)
		{
		    char a=event.text.unicode;
		    str_append(name,a);
		    sfText_setString(Name,name);
		    sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400));
		}
	    }
	}
	//ustawianie pozycji nazwy
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_drawSprite(window,GameOverScreen,NULL);
	sfRenderWindow_drawText(window,Score,NULL);
	sfRenderWindow_drawText(window,Name,NULL);
	sfRenderWindow_display(window);
    }
}
