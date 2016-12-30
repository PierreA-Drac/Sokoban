/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient la fonction main, appelant toutes les
 * fonctions nécéssaires aux grandes étapes de gestion du jeu.
 */

#include <uvsqgraphics.h>
#include "../inc/sokoban.h"

#include "../inc/global.h"
#include "../inc/historic.h"
#include "../inc/action.h"
#include "../inc/display.h"
#include "../inc/game.h"
#include "../inc/editor.h"

/**
 * 1. Fonctions du MAIN .......................................................:
 */

SOKOBAN preInitStarting(SOKOBAN S, int argc, char** argv) {
	S = checkArgs(argc, argv);
	S.lev.quit = FALSE;
	srand(time(NULL));
	return S;
}

/* -------------------------------------------------------------------------- */

SOKOBAN initSokoban(SOKOBAN S) {
	if (S.mode.m_type == PLAY)
		S = initSokoban_Game(S);
	else if (S.mode.m_type == EDITOR)
		S = initSokoban_Editor(S);
	initDisplay(S);
	return S;
}

/* -------------------------------------------------------------------------- */

SOKOBAN handlingGame(SOKOBAN S, ACTION* A) {
	A->type = NONE;
	while (S.lev.win != TRUE && S.lev.quit != TRUE) {
		displaySokoban(S);
		*A = waitAction(S.but, S.But_H_Pix, S.But_W_Pix, S.mode);
		S.lev = editSokoban_Game(S.lev, *A);
		S.lev.win = isWin(S.lev);
                if (A->type != PREV || A->type != NEXT)
                    break;
	}
	return S;
}

/* -------------------------------------------------------------------------- */

SOKOBAN handlingWin(SOKOBAN S) {
	if (S.lev.win == TRUE) {
		displaySokoban(S);
		displayMessage("Le niveau est terminer !");
		S.lev = nextLevel(S.lev);
	}
	return S;
}

/* -------------------------------------------------------------------------- */

SOKOBAN handlingEditor(SOKOBAN S, ACTION* A) {
	while (S.lev.quit != TRUE) {
		displaySokoban(S);
		*A = waitAction(S.but, S.But_H_Pix, S.But_W_Pix, S.mode);
		S = editSokoban_Editor(S, *A);
	}
	return S;
}

/* -------------------------------------------------------------------------- */

SOKOBAN quitSokoban(SOKOBAN S) {
	quitDisplay();
	S.lev.map = freeMap(S.lev.map, S.lev.w, S.lev.h);
	S.lev.H.histoUndo = freeStack(S.lev.H.histoUndo);
	S.lev.H.histoRedo = freeStack(S.lev.H.histoRedo);
	return S;
}

/**
 * 2. MAIN ....................................................................:
 */

int main (int argc, char** argv) {
	SOKOBAN S;
	ACTION A;

	/* Pré-initialisation du Sokoban, du mode, de l'action et de rand */
	S = preInitStarting(S, argc, argv);

	while (S.lev.quit != TRUE) {
		/* Initialisation du Sokoban et de l'affichage */
		S = initSokoban(S);
		/* Gestion du jeu */
		if (S.mode.m_type == PLAY ) {
			/* Gestion du niveau */
			S = handlingGame(S, &A);
			/* Gestion du dernier écran avant de passer au niveau suivant */
			S = handlingWin(S);
		}
		/* Gestion de l'édition */
		else if (S.mode.m_type == EDITOR) {
			S = handlingEditor(S, &A);
		}
		/* Libération de la mémoire */
		S = quitSokoban(S);
	}
        return 0;
}
