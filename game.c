#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "game.h"

#define GameWidth 800
#define GameHeight 800

int main()
{
    sfVideoMode mode={GameWidth,GameHeight,32};
    sfRenderWindow* window;

    window=sfRenderWindow_create(mode,"Space Commander",sfClose,NULL);
    sfRenderWindow_setKeyRepeatEnabled(window,sfFalse);
    
    GameLoop(window);
}
