#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include "main.h"
#include "extra.h"

    //zmienne ogolne
    sfEvent event;
    sfText* Score;
    sfSprite* Background1;
    sfSprite* Background2;
    sfSprite* Background3;

    //highscores.c
    sfSprite* Highscores;
    sfText* Highscore_entries;

    //game.c
    sfSprite* Background4;
    sfSprite* ship_shield;
    sfSprite* ship_rocket;
    sfClock* frame;
    sfClock* gametime;

    //game_over.c
    sfSprite* GameOverScreen;
    sfText* Name;
    sfText* Warning;
    sfClock* WarningTimer;
    sfClock* CursorTimer;

int main()
{
    char* name=NULL;
    sfRenderWindow* window;
    sfSprite* TitleScreen;
    sfFont* dotty;
    int Score_int;

    name=malloc(sizeof(char)*100);

    sfVideoMode mode={GameWidth,GameHeight,32};

    window=sfRenderWindow_create(mode,"Space Commander",sfClose,NULL);
    sfRenderWindow_setKeyRepeatEnabled(window,sfFalse);
    
    //inicjalizacja czcionki
    dotty=sfFont_createFromFile("./fonts/dotty.ttf");
    
    //inicjalzacja title screen
    TitleScreen=sfSprite_create();
    sfSprite_setTexture(TitleScreen,sfTexture_createFromFile("./images/TitleScreen.png",NULL),sfTrue);
    
    //inicjalizacja elementow Highscores
    Highscores=sfSprite_create();
    sfSprite_setTexture(Highscores,sfTexture_createFromFile("./images/Highscores.png",NULL),sfTrue);
    Highscore_entries=sfText_create();
    
    //inicjalizacja elementow Game
    frame=sfClock_create();
    gametime=sfClock_create();
    Score=sfText_create();
    sfText_setFont(Score,dotty);
    ship_shield=sfSprite_create();
    ship_rocket=sfSprite_create();
    sfSprite_setTexture(ship_shield,sfTexture_createFromFile("./images/ShipShield.png",NULL),sfTrue);
    sfSprite_setTexture(ship_rocket,sfTexture_createFromFile("./images/Rocket.png",NULL),sfTrue);

    //inicjalizacja GameOver
    GameOverScreen=sfSprite_create();
    sfSprite_setTexture(GameOverScreen,sfTexture_createFromFile("./images/GameOverScreen.png",NULL),sfTrue); 
    Name=sfText_create();
    Warning=sfText_create();
    sfText_setFont(Warning,dotty);
    sfText_setFont(Name,dotty);
    sfText_setColor(Warning,sfRed);
    WarningTimer=sfClock_create();
    CursorTimer=sfClock_create();

    //inicjalizacja tla
    Background1=sfSprite_create();
    Background2=sfSprite_create();
    Background3=sfSprite_create();
    Background4=sfSprite_create();
    sfSprite_setTexture(Background1,sfTexture_createFromFile("./images/Background1.png",NULL),sfTrue);
    sfSprite_setTexture(Background2,sfTexture_createFromFile("./images/Background2.png",NULL),sfTrue);
    sfSprite_setTexture(Background3,sfTexture_createFromFile("./images/Background3.png",NULL),sfTrue);
    sfSprite_setTexture(Background4,sfTexture_createFromFile("./images/Background4.png",NULL),sfTrue);
    
    while(sfRenderWindow_isOpen(window))
    {
	while (sfRenderWindow_pollEvent(window, &event))
	{
	    if (event.type == sfEvtClosed)
	    {
		free(name);
		sfRenderWindow_close(window);
	    }
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
