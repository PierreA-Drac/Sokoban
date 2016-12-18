/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient la fonction main, appelant toutes les
 * fonctions nécéssaires aux grandes étapes de gestion du jeu,
 * ainsi que quelques fonctions globales au jeu et à l'éditeur.
 */

#include "../inc/sokoban.h"

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  Fonctions =====================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */

SOKOBAN checkArgs(int argc, char** argv) {
	SOKOBAN S;
	if (argc == 2) {
		S = initFirstLevel_Game(argv);
	}
	else if (argc == 3) {
		S = initLevel_Editor(argv);
	}
	else if (argc == 4) {
		S = initOtherLevel_Game(argv);
	}
	else {
		fprintf(stderr, "Wrong usage : \n./sokoban file[in].xsb"
				"\n./sokoban -n num file[in].xsb"
				"\n./sokoban -c file[out].xsb\n");
		exit(EXIT_FAILURE);
	}
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

CASE_TYPE whatIsCaseType(char c) {
	if (c == '#')
		return WALL;
	else if (c == '$')
		return BOX;
	else if (c == '.')
		return BOX_STORAGE;
	else if (c == '@')
		return CHARAC;
	else if (c == '*')
		return BOX_ON_STORAGE;
	else if (c == '+')
		return CHARAC_ON_STORAGE;
	else if (c == ' ')
		return EMPTY;
	else
		return -1;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

CASE** mallocMap(int w, int h) {
	int i;
	CASE** map = NULL;
	map = malloc(h * sizeof(CASE*));	/* 1ère dimension : hauteur */
	if (!map) {
		fprintf(stderr, "Memory allocation error for a map\n");
		exit(EXIT_FAILURE);
	}
	for (i=0; i<h; i++) {
		map[i] = malloc(w * sizeof(CASE));	/* 2ème dimension :
							 * largeur */
		if (!map[i]) {
			fprintf(stderr, "Memory allocation error for a map\n");
			exit(EXIT_FAILURE);
		}
	}
	return map;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

CASE** freeMap(CASE** map, int w, int h) {
	int i;
	for (i=0; i<h; i++)
		free(map[i]);
	free(map);
	return NULL;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

int isResolvable(LEVEL L) {
	int i, j;
	int nbBox = 0, nbBoxStorage = 0, nbCharac = 0;
	for (j=0; j<L.h; j++) {
		for (i=0; i<L.w; i++) {
			if ((L.map[j][i].type == BOX) || 
			    (L.map[j][i].type == BOX_ON_STORAGE))
				nbBox++;
			if ((L.map[j][i].type == BOX_STORAGE) ||
			    (L.map[j][i].type == CHARAC_ON_STORAGE) ||
			    (L.map[j][i].type == BOX_ON_STORAGE))
				nbBoxStorage++;
			if ((L.map[j][i].type == CHARAC) ||
			    (L.map[j][i].type == CHARAC_ON_STORAGE))
				nbCharac++;
		}
	}
	if ((nbBox != nbBoxStorage) || (nbCharac != 1))
		return FALSE;
	else
		return TRUE;
}

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  MAIN ==========================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */

int main (int argc, char** argv) {
	SOKOBAN S;
	ACTION A;

	/* Pré-initialisation du Sokoban et du mode */
	S = checkArgs(argc, argv);
	A.type = NONE; 

	/* Boucle du jeu */
	while (S.mode == PLAY && A.type != QUIT) {
		/* Initialisation du Sokoban et de l'affichage */
		S = initSokoban_Game(S);
		initDisplay(S);

		while (S.lev.win != TRUE && A.type != QUIT) {
			displaySokoban(S);
			A = waitAction(S.but, S.But_H_Pix, S.But_W_Pix);
			S.lev = editSokoban_Game(S.lev, A);
		}

		if (A.type == PREV)
			S = prevLevel(S);
		else
			S = nextLevel(S);
		quitDisplay();
	}

	/* Boucle de l'éditeur */
	while (S.mode == EDITOR && A.type != QUIT) {
		/* Initialisation du Sokoban et de l'affichage */
		S = initSokoban_Editor(S);
		initDisplay(S);

		while (A.type != QUIT) {
			displaySokoban(S);
			A = waitAction(S.but, S.But_H_Pix, S.But_W_Pix);
			S.lev = editSokoban_Editor(S.lev, A);
		}
	}

        /* End */
	freeMap(S.lev.map, S.lev.w, S.lev.h);
        return 0;
}
