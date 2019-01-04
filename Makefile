






CC=g++
CFLAGS=-g -std=c++17 -Wall -pedantic
TEMPDIR=temp/
BIN=Echeyde_Launch
LIBS=-lGL -lGLU -lGLEW -lSDL2 -lSDL2_image -lassimp -lpthread -lSOIL 
INCLUDES=-I/usr/include/SDL2 -I/usr/include/glm -I/usr/include/GL -I ./headers -I/usr/include/gli
SRC=$(wildcard sources/*.cpp)
OBJ=$(SRC:%.cpp=%.o) 

all: $(OBJ)
	$(CC) $^ -o $(BIN)   $(LIBS)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $@ -c $< 

clean:
	rm -f *.o
	rm -f sources/*.o
	rm $(BIN) 


