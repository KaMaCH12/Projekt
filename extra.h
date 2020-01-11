#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

#define JumpForce 40
#define gravity 4 
#define gamespeed 10


typedef struct Ship
{
    sfSprite* spr;
    sfVector2f pos;
    float Vspeed;
    float Hspeed;
}player;

typedef struct asteroid
{
    sfSprite* spr;
    sfVector2f pos;
    float Vspeed;
    float Hspeed;
    float Rspeed;
}asteroid;

typedef struct vector
{
    asteroid **items;
    int capacity;
    int total;
}vector;

//implementacja vectora w C
void vector_init(vector*);
static void vector_resize(vector*,int);
void vector_add(vector*,asteroid*);
asteroid* vector_get(vector*,int index);
void vector_delete(vector*,int);

//pomocnicze
sfVector2f vec2d(float,float);

//zarzadzanie graczem
player ship_new(sfVector2f);

//zarządzanie asteroidami
void asteroid_factory(vector*,int);
void asteroid_move(vector*);
void asteroid_draw(sfRenderWindow*,vector*);
void asteroid_cleaner(vector*);
/*
void vector_init(vector *v);

static void vector_resize(vector *v,int capacity);

void vector_add(vector *v,asteroid *item);

asteroid* vector_get(vector *v,int index);

void vector_delete(vector *v, int index);

sfVector2f vec2d(float x,float y);
*/
