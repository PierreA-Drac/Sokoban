/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions globales au fonctionnement du programme.
 */

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include "../inc/global.h"

#include "../inc/game.h"
#include "../inc/editor.h"

/**
 * 1. Fonctions d'interface ...................................................:
 */

/**
 * 1.1 Gestion des arguments ..................................................:
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
 * 1.2 Contrôles et tests  ....................................................:
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

/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */

int isSaveable(LEVEL L) {
	int i, j, count = 0;
	for (j=0; j<L.h; j++) {
		for (i=0; i<L.w; i++) {
			if (L.map[j][i].type == BOX)
				count++;
		}
	}
	if (!count)
		return FALSE;
	return TRUE;
}

/* -------------------------------------------------------------------------- */

LEVEL initChecking(LEVEL L) {
	int i, j;
	for (j=0; j<L.h; j++) {
		for (i=0; i<L.w; i++) {
			L.map[j][i].checked = FALSE;
		}
	}
	return L;
}

/* -------------------------------------------------------------------------- */

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
 * 1.3 Gestion de la mémoire ..................................................:
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

/* -------------------------------------------------------------------------- */

CASE** freeMap(CASE** map, int w, int h) {
	int i;
	for (i=0; i<h; i++)
		free(map[i]);
	free(map);
	return NULL;
}

/**
 * 1.4 Gestion de l'aléatoire ..................................................:
 */

int rand_a_b(int a, int b) {
	return ((rand()%(b-a)) + a);
}
