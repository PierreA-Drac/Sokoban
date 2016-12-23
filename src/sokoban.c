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
 * # Fonctions ................................................................:
 */

/**
 * ## Gestion des arguments ...................................................:
 */

SOKOBAN checkArgs(int argc, char** argv) {
	SOKOBAN S;
	if 	(argc == 2) {
		S = preInitFirstLevel_Game(argv);
	}
	else if (argc == 3) {
		S = preInitLevel_Editor(argv);
	}
	else if (argc == 4) {
		S = preInitOtherLevel_Game(argv);
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
 * ## Contrôles et tests  .....................................................:
 */

CASE_TYPE whatIsCaseType(char c) {
	if 	(c == '#')
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

int isResolvable(LEVEL L) {
	int i, j;
	int nbBox = 0, nbBoxStorage = 0, nbCharac = 0;
	/* Vérification des éléments de la map */
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
	if ((nbBox != nbBoxStorage) || (nbCharac != 1) || (nbBox == 0))
		return FALSE;
	else
		return TRUE;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

int isClose(LEVEL L, POINT P) {
	/* Initialisation des indices des cases adjacentes */
	POINT P_bottom, P_top, P_right, P_left;
	P_bottom.x = P.x;	P_bottom.y = P.y + 1;
	P_top.x    = P.x;	P_top.y	   = P.y - 1;
	P_right.x  = P.x + 1;	P_right.y  = P.y;
	P_left.x   = P.x - 1;	P_left.y   = P.y;
	/* Si on arrive sur un mur, on renvoie TRUE */
	if (L.map[P.y][P.x].type == WALL)
		return TRUE;
	else {
		/* Tant que l'on ne détecte pas le bord de l'écran,
		 * res est à TRUE */
		int res = TRUE;
		/* On passe la case testée comme étant déjà checkée */
		L.map[P.y][P.x].checked = TRUE;
		/* Si l'on est supérieur à y=0 (donc en dessous du haut
		 * de l'écran), ET que res est toujours à TRUE, on peut tester
		 * la case supérieure */
		if (P.y > 0 && res == TRUE) {
			/* Si la case suppérieur n'a pas déjà été testée,
			 * sinon on boucle infiniement, on peut la tester */
			if (L.map[P_top.y][P_top.x].checked == FALSE)
				res = isClose(L, P_top);
		}
		/* Sinon, cela veut dire que l'on à atteint le bord du haut
		 * de l'écran. On peut donc sortir de la map, alors on retourne
		 * FALSE. Un seul retour de FALSE et touts les appels
		 * récursifs vont s'arrêter de tester les autres case et
		 * retourner FALSE */
		else
			return FALSE;
		/* Et ainsi de suite pour les autres cas ... */
		if (P.y < L.h-1 && res == TRUE) {
			if (L.map[P_bottom.y][P_bottom.x].checked == FALSE)
				res = isClose(L, P_bottom);
		}
		else
			return FALSE;
		if (P.x > 0 && res == TRUE) {
		       if (L.map[P_right.y][P_right.x].checked == FALSE)
				res = isClose(L, P_right);
		}
		else
			return FALSE;
		if (P.x < L.w-1 && res == TRUE) {
			if (L.map[P_left.y][P_left.x].checked == FALSE)
				res = isClose(L, P_left);
		}
		else
			return FALSE;
		return res;
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

POINT findCharac(CASE** map, int w, int h) {
	int i, j;
	POINT charac;
	charac.x = -1; charac.y = -1;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++) {
			if (map[j][i].type == CHARAC ||
			    map[j][i].type == CHARAC_ON_STORAGE) {
				charac.x = i;
				charac.y = j;
			}
		}
	}
	return charac;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL initChecking(LEVEL L) {
	int i, j;
	for (j=0; j<L.h; j++) {
		for (i=0; i<L.w; i++) {
			L.map[j][i].checked = FALSE;
		}
	}
	return L;
}

/**
 * ## Gestion de la mémoire ...................................................:
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
 * # MAIN .....................................................................:
 */

int main (int argc, char** argv) {
	SOKOBAN S;
	ACTION A;

	/* Pré-initialisation du Sokoban et du mode */
	S = checkArgs(argc, argv);
	A.type = NONE; 

	/* Boucle du jeu */
	while (S.mode.m_type == PLAY && A.type != QUIT) {
		/* Initialisation du Sokoban et de l'affichage */
		S = initSokoban_Game(S);
		initDisplay(S);

		/* Gestion du niveau */
		while (S.lev.win != TRUE && S.lev.quit != TRUE) {
			displaySokoban(S);
			A = waitAction(S.but, S.But_H_Pix, S.But_W_Pix, S.mode);
			S.lev = editSokoban_Game(S.lev, A);
			S.lev.win = isWin(S.lev);
		}

		/* Gestion du dernier écran avant de passer au niveau suivant */
		if (S.lev.win == TRUE) {
			displaySokoban(S);
			displayMessage("Le niveau est terminer !");
			S.lev = nextLevel(S.lev);
		}
		quitDisplay();
	}

	/* Boucle de l'éditeur */
	while (S.mode.m_type == EDITOR && A.type != QUIT) {
		/* Initialisation du Sokoban et de l'affichage */
		S = initSokoban_Editor(S);
		initDisplay(S);

		/* Gestion de l'édition */
		while (A.type != QUIT) {
			displaySokoban(S);
			A = waitAction(S.but, S.But_H_Pix, S.But_W_Pix, S.mode);
			S = editSokoban_Editor(S, A);
		}
	}

	/* Libération de la mémoire et sortie du programme */
	S.lev.map = freeMap(S.lev.map, S.lev.w, S.lev.h);
	S.lev.H.histoUndo = freeStack(S.lev.H.histoUndo);
	S.lev.H.histoRedo = freeStack(S.lev.H.histoRedo);
        return 0;
}
