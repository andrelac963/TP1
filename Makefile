#---------------------------------------------------------------------
# Arquivo		: Makefile
# Conteúdo	: Compilar o programa
# Autor			: André Luiz Alves Costa (andrelac963@gmail.com)
# Histórico	: 2023-05-09 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo e executa exemplo
#					: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/expressionsolver.o
HDRS = $(INC)/expressionsolver.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

all:  $(EXE)
	$(EXE) inputs/entdouble.s1.n5.i.in

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) -pg $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/expressionsolver.o: $(HDRS) $(SRC)/expressionsolver.cpp
	$(CC) -pg $(CFLAGS) -o $(OBJ)/expressionsolver.o $(SRC)/expressionsolver.cpp

clean:
	rm -f $(EXE) $(OBJS) gmon.out
