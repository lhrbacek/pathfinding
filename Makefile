CC = g++
CFLAGS = -Wall

all: main.o pathfinding.o algorithms.o
	$(CC) $(CFLAGS) main.o pathfinding.o algorithms.o -o pathfinding -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp

pathfinding.o: pathfinding.cpp

algorithms.o: algorithms.cpp

.PHONY: clean

clean:
	rm pathfinding main.o pathfinding.o algorithms.o