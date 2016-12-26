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
			S.lev.infos.filename = argv[2];
			S.lev.infos.numLevel = getNumLevel(S.lev.infos.filename);
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
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

int getNumLevel(char* filename) {
	int numLevel = 0;
	char str[BUFFER_SIZE];
	FILE* F = fopen(filename, "r");
	/* Si le fichier n'exite pas, on retourne le numéro 1 */
	if (!F)
		return 1;
	/* Sinon, on lit tout les numéros de niveau et on retourne
	 * le dernier numéro + 1 */
	while (fgets(str, BUFFER_SIZE, F) != NULL) {
		if (*str == ';')
			sscanf(str, "; %d", &numLevel);
	}
	fclose(F);
	return numLevel+1;
}

/**
 * # Édition de la map ........................................................:
 */

SOKOBAN editSokoban_Editor(SOKOBAN S, ACTION A) {
	if (A.type == QUIT)
		S.lev.quit = TRUE;
	/* Si on en est à l'étape de constrction du niveau */
	else if (S.mode.m_step == BUILDING)
		S = editSokoban_EditorBuild(S, A);
	/* Si on en est à l'étape de jouer à l'envers */
	else if (S.mode.m_step == PLAY_EDIT)
		S = editSokoban_EditorPlay(S, A);
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN editSokoban_EditorBuild(SOKOBAN S, ACTION A) {
	if 	(A.type == CHANGE_CASE)
		changeCaseType_Editor(S.lev.map, S.lev.h-1 - A.p.y/CASE_SIZE, 
				      A.p.x/CASE_SIZE);
	else if (A.type == PLAY_BACK) {
		S.lev = initChecking(S.lev);
		if (isResolvable(S.lev) && 
		    isClose(S.lev, findCharac(S.lev.map, S.lev.w, S.lev.h))) {
			S.mode.m_step = PLAY_EDIT;
			S.lev.charac = findCharac(S.lev.map, S.lev.w, S.lev.h);
			S = initButtons(S);
		}
		else
			displayMessage("Le niveau n'est pas encore correct !");
	}
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN editSokoban_EditorPlay(SOKOBAN S, ACTION A) {
	if 	(A.type <= CHARAC_RIGHT && A.type >= CHARAC_TOP)
		S.lev = handlingMovement(S.lev, A);
	else if (A.type == INIT)
		S.lev = reInitGame(S.lev);
	else if (A.type == UNDO)
		S.lev = undo(S.lev);
	else if (A.type == REDO)
		S.lev = redo(S.lev);
	else if (A.type == ALEA)
		S = alea(S);
	else if (A.type == SAVE) {
		if (isSaveable(S.lev)) {
			if (save(S)) {
				displayMessage("Le niveau a ete enregistre !");
				S.lev.quit = TRUE;
			}
			else
				displayMessage("Le niveau n'a pas pu etre"
						"enregistrer !");
		}
		else
			displayMessage("Aucune caisse n'a ete deplacee !");
	}
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

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN alea(SOKOBAN S) {
	int i, nbHit;
	ACTION A;
	for (i=0; i<NB_ALEA; i++) {
		nbHit = S.lev.infos.nbHit;
		A = genActionAlea();
		S.lev = editSokoban_Game(S.lev, A);
		/* Permet que si l'action aléatoire bouge vers un mur ou deux
		 * caisses (et donc le personnage ne bouge pas), on
		 * recommence */
		if (nbHit == S.lev.infos.nbHit)
			i--;
		displaySokoban(S);
		SDL_Delay(50);
	}
	return S;
}

/**
 * # Écriture du Sokoban ......................................................:
 */

int save(SOKOBAN S) {
	int w_start=0, h_start=0, w_end=0, h_end=0;
	FILE* F = fopen(S.lev.infos.filename, "a");
	if (!F) {
		fprintf(stderr, "Error: Can't create/write file %s \n",
			S.lev.infos.filename);
		return FALSE;
	}
	/* Fonction permettant d'avoir les dimensions du niveau sans les lignes
	 * vides et les fins de lignes vides */
	calcRealLevelSize(S.lev, &w_start, &w_end, &h_start, &h_end);
	/* Fonctions écrivant réellement le niveau */
	writeLevelNum(F, S.lev.infos.numLevel);
	writeLevelSchema(F, S.lev.map, w_start, w_end, h_start, h_end);
	fclose(F);
	return TRUE;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void calcRealLevelSize(LEVEL L, int* w_start, int* w_end,
				int* h_start, int* h_end) {
	int i, j, next;
	/* Cette fonction va parcourir le niveau d'abord en partant du haut,
	 * puis du bas, puis de la gauche, puis de la droite afin de trouver les
	 * dimensions réelles du niveaux en exluant les lignes vides et les fins
	 * de ligne vide */
	for (j=0, next=TRUE; j<L.h && next; j++) {
		for (i=0; i<L.w && next; i++) {
			if (L.map[j][i].type == WALL) {
				*h_start = j;
				next = FALSE;
			}
		}
	}
	for (j=L.h-1, next=TRUE; j>=0 && next; j--) {
		for (i=0; i<L.w && next; i++) {
			if (L.map[j][i].type == WALL) {
				*h_end = j;
				next = FALSE;
			}
		}
	}
	for (i=0, next=TRUE; i<L.w && next; i++) {
		for (j=0; j<L.h && next; j++) {
			if (L.map[j][i].type == WALL) {
				*w_start = i;
				next = FALSE;
			}
		}
	}
	for (i=L.w-1, next=TRUE; i>=0 && next; i--) {
		for (j=0; j<L.h && next; j++) {
			if (L.map[j][i].type == WALL) {
				*w_end = i;
				next = FALSE;
			}
		}
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void writeLevelNum(FILE* F, int n) {
	fprintf(F, "\r\n; %d\r\n", n);
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void writeLevelSchema(FILE* F, CASE** map, int w_start, int w_end,
					   int h_start, int h_end) {
	int i, j;
	fprintf(F, "\r\n");
	for (j=h_start; j<=h_end; j++) {
		for (i=w_start; i<=w_end; i++) {
			fprintf(F, "%c", whatIsChar(map[j][i].type));
		}
		fprintf(F, "\r\n");
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

char whatIsChar(CASE_TYPE type) {
	if 	(type == EMPTY)
		return ' ';
	else if (type == WALL)
		return '#';
	else if (type == BOX)
		return '$';
	else if (type == BOX_STORAGE)
	       	return '.';
	else if (type == BOX_ON_STORAGE)
		return '*';
	else if (type == CHARAC)
		return '@';
	else /* if (type == CHARAC_ON_STORAGE) */
		return '+';
}
