# Nom ..........: AYOUB
# Prénom .......: Pierre
# N° étudiant ..: 21501002

####			####
##	 Variables	  ##
####			####

CC = gcc
CFLAGS = -g3 -Wall `sdl-config --cflags`
LDFLAGS = -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

EXEC = sokoban
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/
SRC = $(shell find $(SRC_PATH)*.c)
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

ARGS = -n 8 level/sasquatch1.xsb

####			####
##	 Fonctions	  ##
####			####

##	 Lancement	  ##

test : compil 
	$(info Lancement de $(EXEC) :)
	./$(EXEC) $(ARGS)

##	 Compilation	  ##

compil : $(OBJ)
	$(info Édition des liens dans $(EXEC) :)
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_PATH)%.h $(INC_PATH)consts.h $(INC_PATH)structs.h
	$(info Compilation de $< :)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_PATH)sokoban.o : $(INC_PATH)game.h $(INC_PATH)display.h $(INC_PATH)editor.h 
$(OBJ_PATH)game.o    : $(INC_PATH)sokoban.h $(INC_PATH)display.h

##	  Nettoyage	  ##

clean :
	$(info Suppression de $(EXEC) et de $(OBJ) :)
	rm -f $(EXEC)
	rm -f $(OBJ)

##	  Debugger	  ##

gdb : compil
	$(info Debbugage avec $@ :)
	gdb --args ./$(EXEC) $(ARGS)

valgrind : compil
	$(info Debbugage avec $@ :)
	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes ./$(EXEC) $(ARGS)
