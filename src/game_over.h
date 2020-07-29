#include <SFML/Graphics.h>

extern sfEvent event;

extern sfSprite* Background1;
extern sfSprite* Background2;
extern sfSprite* Background3;

extern sfSprite* GameOverScreen;
extern sfText* Name;
extern sfText* Score;
extern sfText* Warning;
extern sfClock* WarningTimer;
extern sfClock* CursorTimer;

sfVector2f vec2d(float,float);

int str_length(char*);
void str_append(char*,char);
void str_delete(char*);
void save_score(char*,int);

