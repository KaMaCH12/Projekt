#include "extra.h"

extern sfText* Score;
extern sfSprite* Background1;
extern sfSprite* Background2;
extern sfSprite* Background3;
extern sfSprite* Background4;
extern sfSprite* ship_shield;
extern sfSprite* ship_boom;
extern sfSprite* ship_rocket;
extern sfClock* frame;
extern sfClock* gametime;


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
