/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions de gestion des données dans l'éditeur.
 */

#include "../inc/editor.h"

/**
 * # Initialisation de l'éditeur ..............................................:
 */

SOKOBAN initLevel_Editor(char** argv) {
	SOKOBAN S;
	if (!strcmp(argv[1], "-c")) {
		if (strstr(argv[2], ".xsb") != NULL) {
			S.mode = EDITOR;
			S.lev.infos.numLevel = 1;
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
	return S;
}

/**
 * # Édition de l'éditeur .....................................................:
 */

LEVEL editSokoban_Editor(LEVEL L, ACTION A) {
	return L;
}
