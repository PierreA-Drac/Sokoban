# Nom ..........: AYOUB
# Prénom .......: Pierre
# N° étudiant ..: 21501002

# Variables ...................................................................:

## Compilateur ................................................................:

CC = gcc
CFLAGS = -g3 -Wall `sdl-config --cflags`
LDFLAGS = -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

## Structure du projet ........................................................:

EXEC = sokoban
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/
REPORT_PATH = report/
SRC = $(shell find $(SRC_PATH)*.c)
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

## Autres .....................................................................:

ARGS = -n 8 level/sasquatch1.xsb

# Cibles ......................................................................:

.PHONY : clean report

## Lancement ..................................................................:

test : compil 
	$(info Lancement de $(EXEC) :)
	./$(EXEC) $(ARGS)

## Compilation ................................................................:

compil : $(EXEC)

$(EXEC) : $(OBJ)
	$(info Édition des liens dans $(EXEC) :)
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_PATH)%.h $(INC_PATH)consts.h $(INC_PATH)structs.h
	$(info Compilation de $< :)
	$(CC) -c $< -o $@ $(CFLAGS)

## Dépendances supplémentaires ................................................:

$(OBJ_PATH)sokoban.o : $(INC_PATH)global.h $(INC_PATH)historic.h $(INC_PATH)action.h $(INC_PATH)display.h $(INC_PATH)game.h $(INC_PATH)editor.h 
$(OBJ_PATH)editor.o  : $(INC_PATH)global.h $(INC_PATH)historic.h $(INC_PATH)action.h $(INC_PATH)display.h $(INC_PATH)game.h
$(OBJ_PATH)game.o    : $(INC_PATH)global.h $(INC_PATH)historic.h $(INC_PATH)action.h $(INC_PATH)display.h
$(OBJ_PATH)action.o  : $(INC_PATH)global.h $(INC_PATH)historic.h 
$(OBJ_PATH)global.o  : $(INC_PATH)game.h $(INC_PATH)editor.h 

## Nettoyage ..................................................................:

clean :
	$(info Suppression de $(EXEC) et de $(OBJ) :)
	rm -f $(EXEC)
	rm -f $(OBJ)
	rm -f .fuse_hidden*
	make clean --directory="$(REPORT_PATH)"

## Debugger ...................................................................:

gdb : compil
	$(info Debbugage avec $@ :)
	gdb --args ./$(EXEC) $(ARGS)

valgrind : compil
	$(info Debbugage avec $@ :)
	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-possibly-lost=yes --show-reachable=yes --track-origins=yes --suppressions=SDL.supp ./$(EXEC) $(ARGS)

## Rapport ....................................................................:

report :
	make --directory="$(REPORT_PATH)"
