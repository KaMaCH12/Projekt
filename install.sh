#!/bin/bash

cd src
gcc extra.c game.c game_over.c highscores.c main.c object_factory.c -lcsfml-window -lcsfml-graphics -lcsfml-system -o ./../SpaceCommander
cd ..

