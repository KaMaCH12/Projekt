#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/System/Clock.h>
#include <stdio.h>
#include "game.h"


int GameLoop(sfRenderWindow* window,sfFont* font)
{
    int Score_int;
    char Score_char[1000];

    player ship=ship_new(vec2d(100,400));

    //restart zegara
    sfClock_restart(gametime);
    
    //inicjalizacja wyswietlania wyniku
    sfText_setFont(Score,font);
    sfText_setCharacterSize(Score,120);
    
    //inicjalizacja vectora do przechowywania objektow
    vector objects;
    vector_init(&objects);
    
    vector rockets;
    vector_init(&rockets);
    
    sfRenderWindow_setKeyRepeatEnabled(window,sfFalse);

    while(sfRenderWindow_isOpen(window))
    {
	srand(sfTime_asMilliseconds(sfClock_getElapsedTime(gametime)));

	float ElapsedTime=0;
	sfClock_restart(frame);
	
	//aktualizowanie wyniku
	Score_int=sfTime_asSeconds(sfClock_getElapsedTime(gametime));
	sprintf(Score_char,"%d",Score_int);
	sfText_setString(Score,Score_char);
	sfText_setPosition(Score,vec2d(400-sfText_getGlobalBounds(Score).width/2,-80));

	//generowanie obiektów
	if(rand()%1000<23)asteroid_factory(&objects,sfTime_asMilliseconds(sfClock_getElapsedTime(gametime)));
	//generowanie powerupow
	if(rand()%1000<5)powerup_factory(&objects,sfTime_asMilliseconds(sfClock_getElapsedTime(gametime)));

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
		if(event.key.code==sfKeyDown)
		{
		    shoot(&rockets,&ship);
		}
	    }
	}

	//ruch statku
	sfSprite_move(ship.spr,vec2d(ship.Hspeed,ship.Vspeed));
	sfSprite_setRotation(ship.spr,ship.Vspeed-4);
	if(ship.Vspeed<=0)ship.Vspeed+=gravity;

	//ruch asteroid i powerupow
	object_move(&objects);
	object_move(&rockets);

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
	if(collision_checker(&objects,&ship))
	{
	    //przerwa dla debugu
	    sfRenderWindow_clear(window,sfBlack);
	    sfRenderWindow_drawSprite(window,Background3,NULL);
	    sfRenderWindow_drawSprite(window,Background1,NULL);
	    sfRenderWindow_drawSprite(window,Background4,NULL);
	    sfRenderWindow_drawSprite(window,Background2,NULL);
	    sfVector2f boom_pos=sfSprite_getPosition(ship.spr);
	    sfSprite_setPosition(ship_boom,boom_pos);
	    sfRenderWindow_drawSprite(window,ship_boom,NULL);
	    player_draw(window,&ship,ship_shield,ship_rocket);
	    object_draw(window,&objects);
	    sfRenderWindow_display(window);
	    while(sfTime_asSeconds(sfClock_getElapsedTime(frame))<1);
	    //destrukcja objektow i rakiet
	    ship_destroy(&ship);
	    object_purge(&objects);
	    object_purge(&rockets);
	    free(objects.items);
	    free(rockets.items);
	    //przekazanie wyniku
	    return Score_int;
	}
	rocket_checker(&rockets,&objects);

	//usuwanie asteroid z poza planszy
	object_cleaner(&objects);
	object_cleaner(&rockets);

	//drawing
	    //tlo
	sfRenderWindow_clear(window,sfBlack);
	sfRenderWindow_drawSprite(window,Background3,NULL);
	sfRenderWindow_drawSprite(window,Background1,NULL);
	sfRenderWindow_drawSprite(window,Background4,NULL);
	sfRenderWindow_drawSprite(window,Background2,NULL);
	    //statek
	player_draw(window,&ship,ship_shield,ship_rocket);
	    //objekty
	object_draw(window,&objects);
	object_draw(window,&rockets);
	    //wynik
	sfRenderWindow_drawText(window,Score,NULL);
	    
	while(ElapsedTime<17)ElapsedTime = sfTime_asMilliseconds(sfClock_getElapsedTime(frame));
	sfRenderWindow_display(window);
    }
    return 0;
}
