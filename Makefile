CCC=g++
CFLAGS=-Wall -I/urs/local/include
CFLAGS=
#LDFLAGS= -lGL -lGLEW -lGLU -lglut  -lm  -llapack -lblas
LDFLAGS= -lGL -lGLU -lglut  -lm

SRC=face.cpp  halfEdge.cpp   mesh.cpp  objfile.cpp  vertex.cpp main.cpp 
DEBUBFLAG=-g

OBJ= $(SRC:.cpp=.o)
BIN=./
EXEC=main

all: $(EXEC)

main: $(OBJ)
		$(CCC) -g -o $(BIN)$@ $^ $(LDFLAGS)

%.o: %.cpp
		$(CCC) -g -o $@ -c $< $(CFLAGS)


clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(BIN)$(EXEC)

