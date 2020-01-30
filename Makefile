CC = gcc

CFLAGS= -std=c11 -Wall -Wextra
LIBS = -lcsfml-window -lcsfml-graphics -lcsfml-system

OBJ = src/main.c\
    src/game.c\
    src/game_over.c\
    src/extra.c\
    src/object_factory.c\
    src/highscores.c

main: $(OBJ)
	$(CC) $(OBJ) $(DEPS) $(LIBS) $(CFLAGS) -o SpaceCommander
