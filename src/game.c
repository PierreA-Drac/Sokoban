/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions nécéssaire à la gestion des données 
 * durant une partie, et à la lecture dans le fichier .xsb.
 */

#include "../inc/game.h"

/**
 * # Initialisation du Sokoban ................................................:
 */

SOKOBAN preInitFirstLevel_Game(char** argv) {
	SOKOBAN S;
	if (strstr(argv[1], ".xsb") != NULL) {
		S.mode.m_type = PLAY;
		S.lev.infos.numLevel = 0;
		S.lev.infos.filename = argv[1];
		/* La validité du fichier sera vérifier plus tard. */
		return S;
	}
	else {
		fprintf(stderr, "Error: %s is not a .xsb\n", argv[1]);
		exit(EXIT_FAILURE);
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN preInitOtherLevel_Game(char** argv) {
	SOKOBAN S;
	if (!strcmp(argv[1], "-n")) {
		if (strstr(argv[3], ".xsb") != NULL) {
			S.mode.m_type = PLAY;
			S.lev.infos.numLevel = atoi(argv[2]);
			/* Le numéro du niveau sera vérifier plus tard. Si
			   l'utilisateur rentre une chaîne de caractère,
			   le niveau sera égal à 0. */
			S.lev.infos.filename = argv[3];
			return S;
		}
		else {
			fprintf(stderr, "Error: %s is not a .xsb\n", argv[3]);
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr, "Wrong usage: ./sokoban -n num file[in].xsb\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN initSokoban_Game(SOKOBAN S) {
	S.lev.win = FALSE;
	S.lev.quit = FALSE;
	S.lev.infos.nbHit = 0;
	S.lev.H = createHisto();
	S = initLevel(S);
	S = initButtons(S);
	S.lev = initChecking(S.lev);
	if (!isResolvable(S.lev) ||
	    !isClose(S.lev, findCharac(S.lev.map, S.lev.w, S.lev.h))) {
		fprintf(stderr, "Error: Level n°%d is not resovable "
				"or incorrect\n", S.lev.infos.numLevel);
		exit(EXIT_FAILURE);
	}
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN initLevel(SOKOBAN S) {
	FILE* F = fopen(S.lev.infos.filename, "r");
	if (!F) {
		fprintf(stderr, "Error: File %s doesn't exist\n", S.lev.infos.filename);
		exit(EXIT_FAILURE);
	}

	/* Place le pointeur de lecture du fichier juste avant la map du 
	 * niveau par effet de bord */
	if (!setLevelPosition(F, S.lev.infos.numLevel)) {
		fprintf(stderr, "Error: Level n°%d not found in %s\n", 
			S.lev.infos.numLevel, S.lev.infos.filename);
		exit(EXIT_FAILURE);
	}
	S.lev = createLevel(F, S.lev);	
	S.Lev_H_Pix = S.lev.h * CASE_SIZE;
	S.Lev_W_Pix = S.lev.w * CASE_SIZE;
	
	fclose(F);
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

int setLevelPosition(FILE* F, int numLevel) {
	char str[BUFFER_SIZE];
	char n[BUFFER_SIZE];
	/* Conversion du numéro du level pour strstr */
	sprintf(n, "%d", numLevel); 
	/* Tant qu'on atteint pas la fin du fichier et qu'on ne trouve pas le
	 * numéro du niveau dans la ligne lue, on continue de lire */
	while (fgets(str, BUFFER_SIZE, F) != NULL) {
		if (*str == ';' && strstr(str, n) != NULL) {
			return TRUE;
			/* Le pointeur de lecture se trouve sur la ligne après
			 * celle contenant le numéro du niveau */
		}
	}
	return FALSE;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL createLevel(FILE* F, LEVEL L) {
	fpos_t pos;		/* Contient la position de lecture du fichier */
	fgetpos(F, &pos);	/* Sauvegarde la position avant le niveau */
	L = calcLevelSize(F, L);
	fsetpos(F, &pos);	/* Replace la postion avant le niveau */
	L.map = readMap(F, L.w, L.h);
	calcPosMap(L.map, L.w, L.h);
	L.charac = findCharac(L.map, L.w, L.h);
	return L;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL calcLevelSize(FILE* F, LEVEL L) {
	char c,	cprev;
	int next = TRUE;
	int htmp = 0, 	wtmp = 0;
	L.h = 0;	L.w = 0;
	/* Tant que le prochain caractère est un retour chariot ... */
	while (*(F->_IO_read_ptr) == '\r' || *(F->_IO_read_ptr) == '\n')
		c = fgetc(F);
	/* Précaution : \n et \r pour si le fichier est encodé
	 * sous un format DOS ou UNIX */
	/* Parcours tout le schéma du niveau pour déterminer ses dimensions */
	do {
		cprev = c;
		c = fgetc(F);
		/* Si deux retours chariot à la suite, ou fin du fichier ... */
		if ((cprev == '\n' && c == '\r') || (cprev == '\n' && c == '\n')
			  || c == EOF)
			next = FALSE;
		/* Si caractère du niveau ... */
		else if (c != '\r' && c != '\n')
			wtmp++;		/* Compteur largeur */
		/* Si fin de ligne ... */
		else if (c == '\r' || c == '\n') {
			htmp++;		/* Compteur hauteur */
			if (wtmp > L.w) /* Met à jour la largeur max lu */
				L.w = wtmp;
			wtmp = 0;
			if (c == '\r') 	/* DOS : lit le dernier \n */
				c = fgetc(F);
		}
	} while (next == TRUE);
	L.h = htmp;
	return L;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

CASE** readMap(FILE* F, int w, int h) {
	int i, j;
	CASE** map = NULL;
	char c;
	char str[BUFFER_SIZE];
	
	/* Tant que le prochain caractère est un retour chariot ... */
	while (*(F->_IO_read_ptr) == '\r' || *(F->_IO_read_ptr) == '\n')
		c = fgetc(F);
	map = mallocMap(w, h);

	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			/* Si la ligne du fichier n'est pas fini ... */
			if (*(F->_IO_read_ptr) != '\r' 
			 && *(F->_IO_read_ptr) != '\n') {
				c = fgetc(F);
				map[j][i].type = whatIsCaseType(c);
				if (map[j][i].type == -1) {
					fprintf(stderr, "Error: Unrecognized "
						"element in the level schema\n");
					exit(EXIT_FAILURE);
				}
			}
			/* Si la ligne est finie de lire ... */
			else if (*(F->_IO_read_ptr) == '\r' 
			 || *(F->_IO_read_ptr) == '\n') {
				map[j][i].type = EMPTY;
			}
		}
		/* Passe à la ligne suivante */
		fgets(str, BUFFER_SIZE, F);
	}
	return map;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void calcPosMap(CASE** map, int w, int h) {
	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			map[j][i].tl.x = i*CASE_SIZE;
			map[j][i].tl.y = h*CASE_SIZE - j*CASE_SIZE;
			map[j][i].tr.x = map[j][i].tl.x + CASE_SIZE;
			map[j][i].tr.y = map[j][i].tl.y;
			map[j][i].bl.x = map[j][i].tl.x;
			map[j][i].bl.y = map[j][i].tl.y - CASE_SIZE;
			map[j][i].br.y = map[j][i].bl.y;
			map[j][i].br.x = map[j][i].tr.x;
		}
	}
}

/**
 * # Édition du Sokoban .......................................................:
 */

LEVEL editSokoban_Game(LEVEL L, ACTION A) {
	if (A.type <= CHARAC_RIGHT && A.type >= CHARAC_TOP)
		L = handlingMovement(L, A);
	else if (A.type == INIT)
		L = reInitGame(L);
	else if (A.type >= QUIT && A.type <= NEXT) {
		if (A.type == NEXT)
			L = nextLevel(L);
		else if (A.type == PREV)
			L = prevLevel(L);
		L.quit = TRUE;
	}
	else if (A.type == UNDO)
		L = undo(L);
	else if (A.type == REDO)
		L = redo(L);
	return L;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL nextLevel(LEVEL L) {
	L.infos.numLevel++;
	return L;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL prevLevel(LEVEL L) {
	L.infos.numLevel--;
	return L;
}

/**
 * # Contrôle .................................................................:
 */

int isWin(LEVEL L) {
	int i, j;
	int nbBox = 0;
	for (j=0; j<L.h; j++) {
		for (i=0; i<L.w; i++) {
			if (L.map[j][i].type == BOX)
				nbBox++;
		}
	}
	if (nbBox == 0)
		return TRUE;
	else
		return FALSE;
}
