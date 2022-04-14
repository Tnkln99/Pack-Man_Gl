BIN=bin/packman 

MAIN=main.cpp
CC=g++
CFLAGS=-Wall
SCR = $(wildcard scr/*.cpp)
OBJ = $(SCR:.cpp=.o)

obj/%.o : scr/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

bin/packman : $(OBJ) obj/glad.o
	$(CC) $(CFLAGS) -o $@ $+ -lglfw -ldl

mv: 
	mv scr/*.o ./obj








