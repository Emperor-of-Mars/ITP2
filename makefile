# Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
# Created: 01.05.2014
# Last change: 01.05.2014 20:16
# Purpose: Makefile

CC=g++
CFLAGS=-g -Wall -std=c++11 -O -Wl,-rpath=./lib/ -L=./lib/
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
NAME=Bullethell

Debug: bullethell
Release: bullethell dist
all: bullethell

bullethell: allobj.o
	${CC} ${CFLAGS} -o $(NAME) obj/*.o ${LIBS}
	mv $(NAME) bin/$(NAME)

allobj.o: *.cpp
	${CC} ${CFLAGS} -c *.cpp ${LIBS}
	mv *.o obj/

clean:
	rm -f obj/*.o bin/${NAME}

dist:
	mkdir Bullethell_Game
	cp -r *.cpp *.h makefile Bullethell.cbp bin Bullethell_Game
	tar -cvzf Bullethell.tgz Bullethell_Game
	rm -r ./Bullethell_Game

distclean:
	rm -f obj/*.o bin/${NAME}
	rm -r ./Bullethell.tgz