/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions de gestion des données dans l'éditeur,
 * et à l'écriture du niveau dans un fichier .xsb.
 */

#include "../inc/editor.h"

/**
 * # Initialisation de l'éditeur ..............................................:
 */

SOKOBAN preInitLevel_Editor(char** argv) {
	SOKOBAN S;
	if (!strcmp(argv[1], "-c")) {
		if (strstr(argv[2], ".xsb") != NULL) {
			S.mode.m_type = EDITOR;
			S.mode.m_step = BUILDING;
			S.lev.infos.numLevel = 0;
			S.lev.infos.filename = argv[2];
			return S;
		}
		else {
			fprintf(stderr, "%s is not a .xsb\n", argv[2]);
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr, "Wrong usage : ./sokoban -c file[out].xsb\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN initSokoban_Editor(SOKOBAN S) {
	S.lev.win = FALSE;
	S.lev.quit = FALSE;
	S.lev.infos.nbHit = 0;
	S.lev.H = createHisto();
	S = initLevel_Editor(S);
	S = initButtons(S);
	return S;
}

/*
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN initLevel_Editor(SOKOBAN S) {
	int i, j;
	/* MAJ de la hauteur et de la largeur de la map */
	S.lev.h = HEIGHT_MAP_EDITOR;
	S.lev.w = WIDTH_MAP_EDITOR;

	/* Allocation mémoire & initialsiation à 0 de la map */
	S.lev.map = mallocMap(S.lev.w, S.lev.h);
	for (j=0; j<S.lev.h; j++) {
		for (i=0; i<S.lev.w; i++) {
			S.lev.map[j][i].type = EMPTY;
		}
	}
	/* Calcul des coordonnées des cases */
	calcPosMap(S.lev.map, S.lev.w, S.lev.h);

	/* MAJ de la taille de la map en pixel */
	S.Lev_H_Pix = S.lev.h * CASE_SIZE;
	S.Lev_W_Pix = S.lev.w * CASE_SIZE;
	return S;
}

/**
 * # Édition de la map ........................................................:
 */

SOKOBAN editSokoban_Editor(SOKOBAN S, ACTION A) {
	/* Pas besoin de tester l'étape d'édition, déjà testé dans la 
	 * récupération des actions */
	/* Si on en est à l'étape de constrction du niveau */
	if 	(A.type == CHANGE_CASE)
		changeCaseType_Editor(S.lev.map, S.lev.h-1 - A.p.y/CASE_SIZE, 
				      A.p.x/CASE_SIZE);
	else if (A.type == PLAY_BACK) {
		S.lev = initChecking(S.lev);
		if (!isResolvable(S.lev) ||
		    !isClose(S.lev, findCharac(S.lev.map, S.lev.w, S.lev.h))) {
			displayMessage("Le niveau n'est pas encore correct !");
			return S;
		}
		else {
			S.mode.m_step = PLAY_EDIT;
			S.lev.charac = findCharac(S.lev.map, S.lev.w, S.lev.h);
			S = initButtons(S);
		}
	}
	/* Si on en est à l'étape de jouer à l'envers */
	else if (A.type <= CHARAC_RIGHT && A.type >= CHARAC_TOP)
		S.lev = handlingMovement(S.lev, A);
	else if (A.type == INIT)
		S.lev = reInitGame(S.lev);
	else if (A.type == UNDO)
		S.lev = undo(S.lev);
	else if (A.type == REDO)
		S.lev = redo(S.lev);
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void changeCaseType_Editor(CASE** map, int h, int w) {
	if 	(map[h][w].type == EMPTY)
		map[h][w].type = WALL;	
	else if (map[h][w].type == WALL)
		map[h][w].type = BOX_ON_STORAGE;
	else if (map[h][w].type == BOX_ON_STORAGE)
		map[h][w].type = CHARAC;
	else
		map[h][w].type = EMPTY;
}
