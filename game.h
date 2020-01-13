#include "extra.h"


//zarzadzanie graczem
player ship_new(sfVector2f);

//zarządzanie asteroidami
void asteroid_factory(vector*,int);
void object_move(vector*);
void object_draw(sfRenderWindow*,vector*);
void object_cleaner(vector*);

//kolizje
int collision_checker(vector*,player*);
