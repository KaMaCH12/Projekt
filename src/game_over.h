#include <SFML/Graphics.h>

sfEvent event;

sfSprite* Background1;
sfSprite* Background2;
sfSprite* Background3;

sfSprite* GameOverScreen;
sfText* Name;
sfText* Score;
sfText* Warning;
sfClock* WarningTimer;
sfClock* CursorTimer;

sfVector2f vec2d(float,float);

int str_length(char*);
void str_append(char*,char);
void str_delete(char*);
void save_score(char*,int);

