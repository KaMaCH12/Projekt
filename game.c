#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "game.h"


void game(sfRenderWindow* window)
{
    /*
    sfVideoMode mode={800,800,32};
    sfRenderWindow* window;

    window=sfRenderWindow_create(mode,"Space Commander",sfClose,NULL);
    sfRenderWindow_setKeyRepeatEnabled(window,sfFalse);
    */
    GameLoop(window);
}
