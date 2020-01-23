#include <SFML/Graphics.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_over.h"
#include "extra.h"

char* game_over(sfRenderWindow* window,int Score_int,sfFont* font,char* name)
{
    sfRenderWindow_setKeyRepeatEnabled(window,sfTrue);
    
    //inicjalizacja wyswietlania wyniku
    sfText_setCharacterSize(Score,250);
    char Score_char[1000];
    sprintf(Score_char,"%d",Score_int);
    sfText_setString(Score,Score_char);
    sfText_setPosition(Score,vec2d(400-sfText_getGlobalBounds(Score).width/2,185));

    //inicjalizacja wprowadzania nazwy
    sfText_setCharacterSize(Name,250);
    if(name!=NULL)sfText_setString(Name,name);
    sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400));

    //inicjalizacja warninga
    sfText_setCharacterSize(Warning,100);
    sfText_setString(Warning,"invalid character");
    sfText_setPosition(Warning,vec2d(400-sfText_getGlobalBounds(Warning).width/2,650));

    while(sfRenderWindow_isOpen(window))
    {
	int len=str_length(name);
	int disp_warning;
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
		char a=event.text.unicode;
		//sprawdzanie czy jest to dozwolony znak
		if(!isalpha((int)a)&&!isdigit((int)a)&&(int)a!=95)
		{
		    disp_warning=1;
		    sfClock_restart(WarningTimer);
		    break;
		}
		//jezeli dlugosc nazwy jest mniejsza niz 20 znakow dodaj znak
		if(len<20)
		{
		    str_append(name,a);
		    sfText_setString(Name,name);
		    sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400));
		}
	    }
	}
	//sprawdzanie jak dlugo wyswietla sie warning
	if(disp_warning&&sfTime_asSeconds(sfClock_getElapsedTime(WarningTimer))>1)
	{
	    disp_warning=0;
	}
	//ustawianie rozmiaru nazwy
	if(len<10)
	{
	    sfText_setCharacterSize(Name,250);
	    sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400));
	}
	else
	{
	    sfText_setCharacterSize(Name,250-6*len);
	    sfText_setPosition(Name,vec2d(400-sfText_getGlobalBounds(Name).width/2,400+6*len));
	}
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_drawSprite(window,GameOverScreen,NULL);
	sfRenderWindow_drawText(window,Score,NULL);
	sfRenderWindow_drawText(window,Name,NULL);
	if(disp_warning)sfRenderWindow_drawText(window,Warning,NULL);
	sfRenderWindow_display(window);
    }
}
