#include "extra.h"

sfText* Score;
sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;
sfSprite* Background4;
sfSprite* ship_shield;
sfSprite* ship_rocket;
sfClock* frame;
sfClock* gametime;


//zarzadzanie graczem
player ship_new(sfVector2f);
void ship_destroy(player*);
void player_draw(sfRenderWindow*,player*,sfSprite*,sfSprite*);
void shoot(vector*,player*);

//zarządzanie asteroidami
void asteroid_factory(vector*,int);
void powerup_factory(vector*,int);
void object_move(vector*);
void object_draw(sfRenderWindow*,vector*);
void object_cleaner(vector*);

//kolizje
int collision_checker(vector*,player*);
void rocket_checker(vector*,vector*);
