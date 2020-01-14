#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_over.h"

sfEvent event;
sfSprite* GameOverScreen;

sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;


sfText* Score;
sfText* Name;

char* game_over(sfRenderWindow* window,int Score_int,sfFont* font,char* name)
{
    sfRenderWindow_setKeyRepeatEnabled(window,sfTrue);
    GameOverScreen=sfSprite_create();

    //inicjalizacja tła
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();
    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    
    sfSprite_setTexture(GameOverScreen,sfTexture_createFromFile("./images/GameOverScreen.png",NULL),sfTrue);

    //inicjalizacja wyswietlania wyniku
    Score=sfText_create();
    sfText_setFont(Score,sfFont_copy(font));
    sfText_setCharacterSize(Score,250);
    char Score_char[1000];
    sprintf(Score_char,"%d",Score_int);
    sfText_setString(Score,Score_char);
    sfText_setPosition(Score,vec2d(400-sfText_getGlobalBounds(Score).width/2,185));

    //inicjalizacja wprowadzania nazwy
    Name=sfText_create();
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
		    save_score(name,Score_int);
		    return name;
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
	printf("%s \n",name);
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
