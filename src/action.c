/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions qui gère la récupération et les
 * applications des différentes actions du jeu.
 */

#include <uvsqgraphics.h>
#include "../inc/action.h"

#include "../inc/global.h"
#include "../inc/historic.h"

/**
 * 1. Fonctions d'interface ...................................................:
 */

/**
 * 1.1 Détermination de l'action ..............................................:
 */

ACTION waitAction(BUTTON B[], int ButtonHeight, int ButtonWidth, MODE M) {
	ACTION A;
	int type, arrow;
	char key;
	type = wait_key_arrow_clic_v2(&key, &arrow, &A.p);
	if 	(type == EST_FLECHE)
		A = getArrowAction(arrow);
	else if (type == EST_TOUCHE)
		A = getKeyAction(key, M);
	else if (type == EST_CLIC)
		A = getMouseAction(A, B, ButtonHeight, ButtonWidth, M);
	else {
		A.type = NONE;
		A.p.x = -1; A.p.y = -1;
	}
	return A;
}

/**
 * 1.2 Génération aléatoire ...................................................:
 */

ACTION genActionAlea() {
	ACTION A;
	A.type = rand_a_b(CHARAC_TOP, CHARAC_RIGHT+1);
	return A;
}

/**
 * 1.3 Modification par l'action ..............................................:
 */

/**
 * 1.3.1 Déplacement du personnage par action de l'utilisateur ................:
 */

LEVEL handlingMovement(LEVEL L, ACTION A) {
	POINT characBackup = L.charac;
	HISTOELEM* E;
	CASE *src = &L.map[L.charac.y][L.charac.x];
	CASE *dest = NULL, *dest_box = NULL;
	/* src      : pointeur sur la case d'où vient le personnage */
	/* dest     : pointeur sur la case où va le personnage */
	/* dest_box : pointeur sur la case après celle où va le personnage pour
	 * gérer le cas des caisses */

	/* Initialisation des pointeurs sur les cases à traitées */
	L.charac = getEditCases(A.type, L, &dest, &dest_box);

	/* Test si le personnage peut se déplacer */
	if (isCollision(dest, dest_box)) {
		L.charac = characBackup;
		return L;
	}

	/* Déplacement du personnage et MAJ de la pile Undo */
	E = createHistoElem();
	E->A = A.type;
	E->ptr2 = moveCharac(src, dest, dest_box);
	if (E->ptr2)
		E->ptr1 = dest;
	else
		E->ptr1 = NULL;
	L.H.histoUndo = pushHistoElem(L.H.histoUndo, E);
	/* Vide la pile du Redo */
	L.H.histoRedo = freeStack(L.H.histoRedo);

	L.infos.nbHit++;
	return L;
}

/**
 * 1.3.2 Déplacement du personnage par Undo ...................................:
 */

LEVEL undo(LEVEL L) {
	/* Si histoUndo vide, rien à faire */
	if (!L.H.histoUndo.head)
		return L;

	HISTOELEM* E = createHistoElem();
	L.H.histoUndo = popHistoElem(L.H.histoUndo, E);
	CASE* src_charac = NULL;
	CASE* dest_charac = NULL;

	/* Initialisation des pointeurs pour traité le déplacement du personnage */
 	L.charac = undo_getEditCases(E->A, L, &src_charac, &dest_charac);

	/* Déplacement du personnage et éventuellement d'une caisse */
	undo_moveCharac(E, src_charac, dest_charac);

	/* MAJ du nombre de coups & de la pile du Redo */
	L.infos.nbHit--;
	L.H.histoRedo = pushHistoElem(L.H.histoRedo, E);

	return L;
}

/**
 * 1.3.3 Déplacement du personnage par Redo ...................................:
 */

LEVEL redo(LEVEL L) {
	/* Si histoRedo vide, rien à faire */
	if (!L.H.histoRedo.head)
		return L;

	HISTOELEM* E = createHistoElem();
	L.H.histoRedo = popHistoElem(L.H.histoRedo, E);
	CASE *src = &L.map[L.charac.y][L.charac.x];
	CASE *dest = NULL, *dest_box = NULL;

	/* Initialisation des pointeurs sur les cases à traitées */
	L.charac = getEditCases(E->A, L, &dest, &dest_box);

	/* Déplacement du personnage et MAJ de la pile Undo */
	moveCharac(src, dest, dest_box);

	/* MAJ du nombre de coups & de la pile du Undo */
	L.infos.nbHit++;
	L.H.histoUndo = pushHistoElem(L.H.histoUndo, E);

	return L;
}

/**
 * 1.4 Ré-initialisation du niveau ............................................:
 */

LEVEL reInitGame(LEVEL L) {
	while (L.H.histoUndo.head)
		L = undo(L);
	return L;
}

/**
 * 2. Fonctions locales .......................................................:
 */

ACTION getArrowAction(int arrow) {
	ACTION A;
	if 	(arrow == FLECHE_GAUCHE)
		A.type = CHARAC_LEFT;
	else if (arrow == FLECHE_DROITE)
		A.type = CHARAC_RIGHT;
	else if (arrow == FLECHE_HAUT)
		A.type = CHARAC_TOP;
	else if (arrow == FLECHE_BAS)
		A.type = CHARAC_BOTTOM;
	A.p.x = -1; 	A.p.y = -1;
	return A;
}

/* -------------------------------------------------------------------------- */

ACTION getKeyAction(char key, MODE M) {
	ACTION A;
	if 	(key == 'q' || key == 'Q')
		A.type = QUIT;
	else if (M.m_type == PLAY) {
		if 	(key == 'u' || key == 'U')
			A.type = UNDO;
		else if (key == 'r' || key == 'R')
			A.type = REDO;
		else if (key == 'i' || key == 'I')
			A.type = INIT;
		else if (key == 'p' || key == 'P')
			A.type = PREV;
		else if (key == 'n' || key == 'N')
			A.type = NEXT;
	}
	else if (M.m_type == EDITOR && M.m_step == BUILDING) {
		if (key == 'p' || key == 'P')
			A.type = PLAY_BACK;
	}
	else if (M.m_type == EDITOR && M.m_step == PLAY_EDIT) {
		if 	(key == 'u' || key == 'U')
			A.type = UNDO;
		else if (key == 'r' || key == 'R')
			A.type = REDO;
		else if (key == 'i' || key == 'I')
			A.type = INIT;
		else if (key == 'a' || key == 'A')
			A.type = ALEA;
		else if (key == 's' || key == 'S')
			A.type = SAVE;
	}
	else
		A.type = NONE;
	A.p.x = -1; 	A.p.y = -1;
	return A;
}

/* -------------------------------------------------------------------------- */

ACTION getMouseAction(ACTION A, BUTTON B[], int ButtonHeight, 
					    int ButtonWidth, MODE M) {
	int NbButtons;
	/* Différenciation mode jeu vs éditeur */
	if (M.m_type == PLAY || (M.m_type == EDITOR && 
				 M.m_step == PLAY_EDIT))
		NbButtons = NB_BUTTON;
	else
		NbButtons = NB_BUTTON_EDITOR_BUILDING;
	/* Si c'est un bouton */
	if (A.p.y > (HEIGHT - ButtonHeight))
		A.type = B[A.p.x / (ButtonWidth/NbButtons)].A;
	/* Si c'est une case (action active que pour l'éditeur en mode 
	 * construction */
	else if (A.p.y < (HEIGHT - NB_BUT_H*ButtonHeight - 
		 NB_SEPARATOR_V*H_SEPARATOR_V) &&
		 M.m_type == EDITOR && M.m_step == BUILDING)
		A.type = CHANGE_CASE;
	else
		A.type = NONE;
	return A;
}

/* -------------------------------------------------------------------------- */

int wait_key_arrow_clic_v2(char *touche, int *fleche, POINT *P) { 
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
		if ((event.type == SDL_KEYUP) && 
		    (event.key.keysym.sym == SDLK_ESCAPE)) 
			exit(0);
		if ((event.type == SDL_KEYUP) && 
		    (event.key.keysym.sym == SDLK_LEFT))  { 
			*fleche = FLECHE_GAUCHE; 
			return EST_FLECHE; 
		}
		if ((event.type == SDL_KEYUP) && 
		    (event.key.keysym.sym == SDLK_RIGHT)) { 
			*fleche = FLECHE_DROITE; 
			return EST_FLECHE; 
		}
		if ((event.type == SDL_KEYUP) && 
		    (event.key.keysym.sym == SDLK_UP)) { 
			*fleche = FLECHE_HAUTE;  
			return EST_FLECHE; 
		}
		if ((event.type == SDL_KEYUP) &&
		    (event.key.keysym.sym == SDLK_DOWN)) { 
			*fleche = FLECHE_BAS;    
			return EST_FLECHE; 
		}
		if ((event.type == SDL_KEYUP) && ('a' <= event.key.keysym.sym)
		    && (event.key.keysym.sym <= 'z')) { 
			*touche = event.key.keysym.sym - 'a' + 'A'; 
			return EST_TOUCHE; 
		}
		if ((event.type == SDL_MOUSEBUTTONDOWN) && 
		    (event.button.button == SDL_BUTTON_LEFT)) {
			P->x = event.button.x; 
			P->y = HEIGHT-event.button.y; 
			return EST_CLIC;
		}
	}
	return EST_RIEN;
}

/* -------------------------------------------------------------------------- */

POINT getEditCases(ACTION_TYPE A, LEVEL L, CASE** dest, CASE** dest_box) {
	if 	(A == CHARAC_TOP)    {
		*dest = &L.map[L.charac.y-1][L.charac.x];
		if (L.charac.y > 1)
			*dest_box = &L.map[L.charac.y-2][L.charac.x];
		L.charac.y--;
	}
	else if (A == CHARAC_BOTTOM) {
		*dest = &L.map[L.charac.y+1][L.charac.x];
		if (L.charac.y < L.h-2)
			*dest_box = &L.map[L.charac.y+2][L.charac.x];
		L.charac.y++;
	}
	else if (A == CHARAC_LEFT)   {
		*dest = &L.map[L.charac.y][L.charac.x-1];
		if (L.charac.x > 1)
			*dest_box = &L.map[L.charac.y][L.charac.x-2];
		L.charac.x--;
	}
	else if (A == CHARAC_RIGHT)  {
		*dest = &L.map[L.charac.y][L.charac.x+1];
		if (L.charac.x < L.w-2)
			*dest_box = &L.map[L.charac.y][L.charac.x+2];
		L.charac.x++;
	}
	return L.charac;
}

/* -------------------------------------------------------------------------- */

int isCollision(CASE* dest, CASE* dest_box) {
	/* Si le personnage rencontre un mur */
	if (dest->type == WALL) {
		return TRUE;
	}
	/* Si on arrive ici, c'est que le personnage n'est pas aux extrémitées
	 * du plateau, et donc dest_box sera forcémment non-nul */
	/* Si le personnage rencontre une caisse coincée par un mur ou une 
	 * autre caisse */
	else if (dest->type == BOX || dest->type == BOX_ON_STORAGE) {
		if (dest_box->type == WALL || dest_box->type == BOX ||
		    dest_box->type == BOX_ON_STORAGE) {
			return TRUE;
		}
	}
	return FALSE;
}

/* -------------------------------------------------------------------------- */

CASE* moveCharac(CASE* src, CASE* dest, CASE* dest_box) {
	/* Gère la case du personnage */
	if 	(src->type == CHARAC)
		src->type = EMPTY;
	else if (src->type == CHARAC_ON_STORAGE)
		src->type = BOX_STORAGE;

	/* Gère la case de destination du personnage */
	if 	(dest->type == EMPTY)
		dest->type = CHARAC;
	else if (dest->type == BOX_STORAGE)
		dest->type = CHARAC_ON_STORAGE;

	/* Gère le cas où le personnage pousse une caisse */
	else if (dest->type == BOX || dest->type == BOX_ON_STORAGE) {
		/* Case de destination du personnage */
		if 	(dest->type == BOX)
			dest->type = CHARAC;
		else if (dest->type == BOX_ON_STORAGE)
			dest->type = CHARAC_ON_STORAGE;
		/* Case de destination de la caisse */
		if 	(dest_box->type == EMPTY)
			dest_box->type = BOX;
		else if (dest_box->type == BOX_STORAGE)
			dest_box->type = BOX_ON_STORAGE;
		return dest_box;
	}
	return NULL;
}

/* -------------------------------------------------------------------------- */

POINT undo_getEditCases(ACTION_TYPE A, LEVEL L, CASE** src, CASE** dest) {
	*src = &L.map[L.charac.y][L.charac.x];
	if 	(A == CHARAC_TOP)
		L.charac.y++;
	else if (A == CHARAC_BOTTOM)
		L.charac.y--;
	else if (A == CHARAC_LEFT)
		L.charac.x++;
	else if (A == CHARAC_RIGHT)
		L.charac.x--;
	*dest = &L.map[L.charac.y][L.charac.x];
	return L.charac;
 }

/* -------------------------------------------------------------------------- */

void undo_moveCharac(HISTOELEM* E, CASE* src, CASE* dest) {
	/* Gère la source du personnage */
	if 	(src->type == CHARAC)
		src->type = EMPTY;
	else if (src->type == CHARAC_ON_STORAGE)
		src->type = BOX_STORAGE;

	/* Gère la destination du personnage */
	if 	(dest->type == EMPTY)
		dest->type = CHARAC;
	else if (dest->type == BOX_STORAGE)
		dest->type = CHARAC_ON_STORAGE;

	/* Gère le déplacement de la caisse */
	if (E->ptr1 && E->ptr2) {
		if 	(E->ptr1->type == EMPTY)
			E->ptr1->type = BOX;
		else if (E->ptr1->type == BOX_STORAGE)
			E->ptr1->type = BOX_ON_STORAGE;
		if 	(E->ptr2->type == BOX)
			E->ptr2->type = EMPTY;
		else if (E->ptr2->type == BOX_ON_STORAGE)
			E->ptr2->type = BOX_STORAGE;
	}
}
