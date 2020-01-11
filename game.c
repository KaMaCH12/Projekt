#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/System/Clock.h>
#include <stdio.h>
#include "extra.h"


void GameLoop(sfRenderWindow* window)
{
    int Score_int;
    char Score_char[1000];
    sfText* Score;
    sfSprite* Background1;
    sfSprite* Background2;
    sfSprite* Background3;
    sfEvent event;
    sfClock* frame;
    sfClock* gametime;

    player ship=ship_new(vec2d(200,400));
    frame=sfClock_create();
    gametime=sfClock_create();

    sfClock_restart(gametime);
   

    //inicjalizacja tła
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();
    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    
    //inicjalizacja wyswietlania wyniku
    Score=sfText_create();
    sfText_setFont(Score,sfFont_createFromFile("./fonts/dotty.ttf"));
    sfText_setCharacterSize(Score,120);
    sfText_move(Score,vec2d(370,-80));
    
    //inicjalizacja vectora do przechowywania asteroid
    vector asteroids;
    vector_init(&asteroids);

    while(sfRenderWindow_isOpen(window))
    {
	float ElapsedTime=0;
	sfClock_restart(frame);
	
	//aktualizowanie wyniku
	Score_int=sfTime_asSeconds(sfClock_getElapsedTime(gametime));
	sprintf(Score_char,"%d",Score_int);
	sfText_setString(Score,Score_char);

	//generowanie obiektów
	if(sfTime_asMilliseconds(sfClock_getElapsedTime(gametime))%25==0)asteroid_factory(&asteroids,sfTime_asMilliseconds(sfClock_getElapsedTime(gametime)));

	//eventy
	while(sfRenderWindow_pollEvent(window, &event))
	{
	    if(event.type==sfEvtClosed)sfRenderWindow_close(window);
	    if(event.type==sfEvtKeyPressed)
	    {
		if(event.key.code==sfKeyUp)
		{
		    ship.Vspeed-=JumpForce;
		}
	    }
	}

	//ruch statku
	sfSprite_move(ship.spr,vec2d(ship.Hspeed,ship.Vspeed));
	if(ship.Vspeed<=0)ship.Vspeed+=gravity;

	//ruch asteroid i powerupow
	asteroid_move(&asteroids);

	//ruch tla
	sfSprite_move(Background1,vec2d(-gamespeed*2,0));
	sfSprite_move(Background2,vec2d(-gamespeed,0));
	sfSprite_move(Background3,vec2d(-gamespeed/4,0));
	if(sfSprite_getPosition(Background1).x<=-2400)
	    sfSprite_setPosition(Background1,vec2d(0,0));
	if(sfSprite_getPosition(Background2).x<=-2400)
	    sfSprite_setPosition(Background2,vec2d(0,0));
	if(sfSprite_getPosition(Background3).x<=-2400)
	    sfSprite_setPosition(Background3,vec2d(0,0));

	//kolizje

	//usuwanie asteroid z poza planszy
	asteroid_cleaner(&asteroids);

	//drawing
	    //tlo
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	    //statek
	sfRenderWindow_drawSprite(window,ship.spr,NULL);
	    //asteroidy
	asteroid_draw(window,&asteroids);
	    //wynik
	sfRenderWindow_drawText(window,Score,NULL);
	    

	//debug
	printf("%d\n",asteroids.total);


	while(ElapsedTime<17)ElapsedTime = sfTime_asMilliseconds(sfClock_getElapsedTime(frame));
	sfRenderWindow_display(window);
    }
}
