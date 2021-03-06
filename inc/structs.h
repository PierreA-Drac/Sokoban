/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient toutes les structures utilisées dans le jeu.
 */

#ifndef __STRUCTS_H
#define __STRUCTS_H

#include "consts.h"

/**
 * 1. Déclarations ............................................................:
 */

/**
 * 1.1 Structure action .......................................................:
 */

typedef struct action ACTION;

/**
 * 1.2 Structures de l'historique .............................................:
 */

typedef struct histoElem HISTOELEM;
typedef struct stack STACK;
typedef struct historic HISTORIC;

/**
 * 1.3 Structures pour former un niveau .......................................:
 */

typedef struct level_infos LEVEL_INFOS;
typedef struct level_case CASE;
typedef struct level LEVEL;

/**
 * 1.4 Structure boutons ......................................................:
 */

typedef struct button BUTTON;

/**
 * 1.5 Structure d'un mode ....................................................:
 */

typedef struct mode MODE;

/**
 * 1.6 Structure d'une fenêtre Sokoban ........................................:
 */

typedef struct sokoban SOKOBAN;

/**
 * 2. Définitions .............................................................:
 */

/**
 * 2.1 Structure action .......................................................:
 */

/** ACTION
 * =============================================================================
 * Correspond à une action de l'utilisateur.
 * =============================================================================
 * POINT p	    : Coordonnées de l'action (si clic).
 * ACTION_TYPE type : Type de l'action effectué.
 */

struct action {
	POINT p;
	ACTION_TYPE type;
};

/**
 * 2.2 Structures de l'historique .............................................:
 */

/** HISTOELEM
 * =============================================================================
 * Structure d'un élément de l'historique. Il s'agit d'un élément d'une liste
 * chaînée avec des informations propre à l'historique.
 * =============================================================================
 * ACTION_TYPE A	  : Type d'action effectué sur cet élément de
 *			    l'historique.
 * CASE *ptr1, *ptr2	  : Deux pointeurs vers des cases à traitées (hormis
 * 			    la case du personnage).
 * struct histoElem* suiv : Pointeur vers l'élément suivant.
 */

struct histoElem {
	ACTION_TYPE A;
	CASE *ptr1, *ptr2;
	struct histoElem* suiv;
};

/* -------------------------------------------------------------------------- */

/** STACK
 * =============================================================================
 * Structure d'une pile.
 * =============================================================================
 * struct histoElem* head : Pointeur sur le premier élément de la pile.
 */

struct stack {
	struct histoElem* head;
};

/* -------------------------------------------------------------------------- */

/** HISTORIC
 * =============================================================================
 * Structure d'un historique utilisé pour un niveau.
 * =============================================================================
 * STACK histoUndo : Pile où il faut piocher pour faire un Undo.
 * STACK histoRedo : Pile où il faut piocher pour faire un Redo.
 */

struct historic {
	STACK histoUndo;
	STACK histoRedo;
};

/**
 * 2.3 Structures pour former un niveau .......................................:
 */

/** LEVEL_INFOS
 * =============================================================================
 * Contient les informations relative au niveau actuel à afficher.
 * =============================================================================
 * int nbHit      : Nombre de coups joués.
 * int numLevel	  : Numéro du niveau.
 * char* filename : Nom du fichier qui contient le niveau.
 */

struct level_infos {
	int nbHit;
	int numLevel;
	char* filename;
};

/* -------------------------------------------------------------------------- */

/** CASE
 * =============================================================================
 * Contient les information relative à une case du niveau.
 * =============================================================================
 * POINT tl, tr, bl, br  : Point des différents côtés de la case.
 * 			   tl = Top Left = Haut gauche, etc.
 * CASE_TYPE type 	 : Type de la case.
 * int checked		 : Indique si la case à déjà été vérifiée ou non.
 */

struct level_case {
	POINT tl, tr, bl, br;
	CASE_TYPE type;
	int checked;
};

/* -------------------------------------------------------------------------- */

/** LEVEL
 * =============================================================================
 * Contient toutes les données concernant un niveau.
 * =============================================================================
 * CASE** map	       : Tableau à double dimension contenant les cases
 * 			 de la map.
 * POINT charac        : Point contenant les indices (!= coordonnées) de la case
 * 			 du personnage (évite de devoir parcourir toute la map 
 * 			 pour le  trouver).
 * int h, w 	       : Nombre de ligne (h : hauteur) et nombre de 
 * 			 colonne (w : largeur) du niveau.
 * int win, quit       : Constantes booléennes indiquant si le niveau est gagné,
 * 			 et si on doit le quitter.
 * LEVEL_INFOS infos   : Contient les informations relative au niveau.
 * HISTORIC H	       : Historique du niveau.
 */

struct level {
	CASE** map;
	POINT charac;
	int h, w;
	int win, quit;
	LEVEL_INFOS infos;
	HISTORIC H;
};

/**
 * 2.4 Structure boutons ......................................................:
 */

/** BUTTON
 * =============================================================================
 * Contient toutes les données concernant un boutton.
 * =============================================================================
 * POINT tl, tr, bl, br : Points des côtés du boutton.
 * ACTION_TYPE A	: Action si le boutton est activé.
 * char* name		: Nom du boutton à afficher.
 */

typedef struct button {
	POINT tl, tr, bl, br;
	ACTION_TYPE A;
	char* name;
} BUTTON;

/**
 * 2.5 Structure d'un mode ....................................................:
 */

/** MODE
 * =============================================================================
 * Structure qui contient toutes les informations sur le mode du programme
 * dans lequel on se trouve.
 * =============================================================================
 *  MODE_TYPE mtype	    : Indique le mode du programme (jeu ou éditeur).
 *  MODE_EDITOR_STEP m_step : Indique l'étape d'édition de niveau dans laquel
 *  			      on se trouve (création ou jeu à l'envers).
 */

struct mode {
	MODE_TYPE m_type;
	MODE_EDITOR_STEP m_step;
};

/**
 * 2.6 Structure d'une fenêtre Sokoban ........................................:
 */

/** SOKOBAN
 * =============================================================================
 * Contient toutes les données concernant les éléments à afficher dans notre
 * fenêtre.
 * =============================================================================
 * MODE mode  		      : Contient le mode du sokoban.
 *
 * LEVEL lev  		      : Niveau de jeu à afficher.
 * BUTTON but 		      : Tableau contenant les boutons à afficher.
 * int Lev_H_Pix, Lev_W_Pix   : Hauteur et largeur en pixel du niveau.
 * float But_H_Pix, But_W_Pix : Hauteur et largeur en pixel des boutons.
 * 				(float car on à besoin de précision sur les
 * 				pixels pendant une division.)
 * 				Ces hauteurs et largeurs seront aussi utilisées
 * 				pour afficher les informations concernant le
 * 				niveau.
 */

struct sokoban {
	MODE mode;
	LEVEL lev;
	BUTTON but[NB_BUTTON];
	int Lev_H_Pix, Lev_W_Pix;
	float But_H_Pix, But_W_Pix;
};

#endif
