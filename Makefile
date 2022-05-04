BIN=bin/packman 

MAIN=main.cpp
CC=g++
CFLAGS=-Wall -g -std=c++11
SCR = $(wildcard scr/*.cpp)
OBJ = $(SCR:.cpp=.o)

obj/%.o : scr/%.cpp
	$(CC) $(CFLAGS) -o $(BIN) $@ -c $<

bin/packman : $(OBJ) obj/glad.o
	$(CC) $(CFLAGS) -o $@ $+ -lglfw -ldl

mv: 
	mv scr/*.o ./obj
