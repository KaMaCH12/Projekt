#include "extra.h"


//zarzadzanie graczem
player ship_new(sfVector2f);

//zarządzanie asteroidami
void asteroid_factory(vector*,int);
void asteroid_move(vector*);
void asteroid_draw(sfRenderWindow*,vector*);
void asteroid_cleaner(vector*);

//kolizje
int collision_checker(vector*,player*);
