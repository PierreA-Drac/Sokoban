/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions qui gère la récupération des différentes
 * actions du jeu.
 */

#include "../inc/action.h"

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  Fonctions =====================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */

ACTION waitAction(BUTTON B[], int ButtonHeight, int ButtonWidth) {
	ACTION A;
	int type, arrow;
	char key;
	type = wait_key_arrow_clic_v2(&key, &arrow, &A.p);
	if (type == EST_FLECHE)
		A = getArrowAction(arrow);
	else if (type == EST_TOUCHE)
		A = getKeyAction(key);
	else if (type == EST_CLIC)
		A = getMouseAction(A, B, ButtonHeight, ButtonWidth);
	else {
		A.type = NONE;
		A.p.x = -1; A.p.y = -1;
	}
	return A;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

ACTION getArrowAction(int arrow) {
	ACTION A;
	if (arrow == FLECHE_GAUCHE)
		A.type = CHARAC_LEFT;
	else if (arrow == FLECHE_DROITE)
		A.type = CHARAC_RIGHT;
	else if (arrow == FLECHE_HAUT)
		A.type = CHARAC_TOP;
	else if (arrow == FLECHE_BAS)
		A.type = CHARAC_BOTTOM;
	A.p.x = -1; A.p.y = -1;
	return A;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

ACTION getKeyAction(char key) {
	ACTION A;
	if (key == 'u' || key == 'U')
		A.type = UNDO;
	else if (key == 'r' || key == 'R')
		A.type = REDO;
	else if (key == 'i' || key == 'I')
		A.type = INIT;
	else if (key == 'q' || key == 'Q')
		A.type = QUIT;
	else if (key == 'p' || key == 'P')
		A.type = PREV;
	else if (key == 'n' || key == 'N')
		A.type = NEXT;
	else if (key == 's' || key == 'S')
		A.type = SAVE;
	else if (key == 'a' || key == 'A')
		A.type = ALEA;
	A.p.x = -1; A.p.y = -1;
	return A;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

ACTION getMouseAction(ACTION A, BUTTON B[], int ButtonHeight, int ButtonWidth) {
	/* Si c'est un bouton */
	if (A.p.y > (HEIGHT - ButtonHeight)) {
		A.type = B[A.p.x / (ButtonWidth/NB_BUTTON)].A;
	}
	/* Si c'est une case */
	else {
		A.type = CHANGE_CASE;	/* Action active que pour l'éditeur */
	}
	return A;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

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

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL handlingMovement(LEVEL L, ACTION A) {
	POINT characBackup = L.charac;
	CASE *src = &L.map[L.charac.y][L.charac.x];
	CASE *dest = NULL, *dest_box = NULL;
	/* src      : pointeur sur la case d'où vient le personnage */
	/* dest     : pointeur sur la case où va le personnage */
	/* dest_box : pointeur sur la case après celle où va le personnage pour
	 * gérer le cas des caisses */

	/* Initialisation des ponteurs sur les cases à traitées */
	L.charac = getEditCases(A, L, &dest, &dest_box);

	/* Test si le personnage peut se déplacer */
	if (isCollision(dest, dest_box)) {
		L.charac = characBackup;
		return L;
	}

	/* Déplacement du personnage */
	moveCharac(src, dest, dest_box);

	L.infos.nbHit++;
	return L;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

POINT getEditCases(ACTION A, LEVEL L, CASE** dest, CASE** dest_box) {
	if 	(A.type == CHARAC_TOP)    {
		*dest  = &L.map[L.charac.y-1][L.charac.x];
		*dest_box = &L.map[L.charac.y-2][L.charac.x];
		L.charac.y--;
	}
	else if (A.type == CHARAC_BOTTOM) {
		*dest  = &L.map[L.charac.y+1][L.charac.x];
		*dest_box = &L.map[L.charac.y+2][L.charac.x];
		L.charac.y++;
	}
	else if (A.type == CHARAC_LEFT)   {
		*dest  = &L.map[L.charac.y][L.charac.x-1];
		*dest_box = &L.map[L.charac.y][L.charac.x-2];
		L.charac.x--;
	}
	else if (A.type == CHARAC_RIGHT)  {
		*dest  = &L.map[L.charac.y][L.charac.x+1];
		*dest_box = &L.map[L.charac.y][L.charac.x+2];
		L.charac.x++;
	}
	return L.charac;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

int isCollision(CASE* dest, CASE* dest_box) {
	/* Si le personnage rencontre un mur */
	if (dest->type == WALL) {
		return TRUE;
	}
	/* Si le personnage rencontre une caisse coincée par un mur ou une 
	 * autre caisse */
	else if (dest->type == BOX || dest->type == BOX_ON_STORAGE) {
		if (dest_box->type == WALL || dest_box->type == BOX
		    || dest_box->type == BOX_ON_STORAGE) {
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void moveCharac(CASE* src, CASE* dest, CASE* dest_box) {
	/* Gère la case du personnage */
	if (src->type == CHARAC)
		src->type = EMPTY;
	else if (src->type == CHARAC_ON_STORAGE)
		src->type = BOX_STORAGE;

	/* Gère la case de destination du personnage */
	if (dest->type == EMPTY)
		dest->type = CHARAC;
	else if (dest->type == BOX_STORAGE)
		dest->type = CHARAC_ON_STORAGE;

	/* Gère le cas où le personnage pousse une caisse */
	else if (dest->type == BOX || dest->type == BOX_ON_STORAGE) {
		/* Case de destination du personnage */
		if (dest->type == BOX)
			dest->type = CHARAC;
		else if (dest->type == BOX_ON_STORAGE)
			dest->type = CHARAC_ON_STORAGE;
		/* Case de destination de la caisse */
		if (dest_box->type == EMPTY)
			dest_box->type = BOX;
		else if (dest_box->type == BOX_STORAGE)
			dest_box->type = BOX_ON_STORAGE;
	}
}
