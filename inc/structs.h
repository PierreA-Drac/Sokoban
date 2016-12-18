/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient toutes les structures utilisées dans le jeu.
 */

#ifndef __STRUCTS_H
#define __STRUCTS_H

#include <uvsqgraphics.h>
#include "consts.h"

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  Structures ====================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */

/* # Structure action : ===================================================== */

/** ACTION
 * -----------------------------------------------------------------------------
 * Correspond à une action de l'utilisateur.
 * -----------------------------------------------------------------------------
 * POINT p	    : Coordonnées de l'action (si clic).
 * ACTION_TYPE type : Type de l'action effectué.
 */

typedef struct action {
	POINT p;
	ACTION_TYPE type;
} ACTION;

/* # Structures pour former un niveau : ===================================== */

/** LEVEL_INFOS
 * -----------------------------------------------------------------------------
 * Contient les informations relative au niveau actuel à afficher.
 * -----------------------------------------------------------------------------
 * int nbHit      : Nombre de coups joués.
 * int numLevel	  : Numéro du niveau.
 * char* filename : Nom du fichier qui contient le niveau.
 */

typedef struct level_infos {
	int nbHit;
	int numLevel;
	char* filename;
} LEVEL_INFOS;

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** CASE
 * -----------------------------------------------------------------------------
 * Contient les information relative à une case du niveau.
 * -----------------------------------------------------------------------------
 * POINT tl, tr, bl, br  : Point des différents côtés de la case.
 * 			   tl = Top Left = Haut gauche, etc.
 * CASE_TYPE type 	 : Type de la case.
 */

typedef struct level_case {
	POINT tl, tr, bl, br;
	CASE_TYPE type;
} CASE;

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** LEVEL
 * -----------------------------------------------------------------------------
 * Contient toutes les données concernant un niveau.
 * -----------------------------------------------------------------------------
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
 */

typedef struct level {
	CASE** map;
	POINT charac;
	int h, w;
	int win, quit;
	LEVEL_INFOS infos;
} LEVEL;

/* # Structure boutons : ===================================================== */

/** BUTTON
 * -----------------------------------------------------------------------------
 * Contient toutes les données concernant un boutton.
 * -----------------------------------------------------------------------------
 * POINT tl, tr, bl, br : Points des côtés du boutton.
 * ACTION_TYPE A	: Action si le boutton est activé.
 * char* name		: Nom du boutton à afficher.
 */

typedef struct button {
	POINT tl, tr, bl, br;
	ACTION_TYPE A;
	char* name;
} BUTTON;

/* # Structure d'une fenêtre Sokoban : ====================================== */

/** SOKOBAN
 * -----------------------------------------------------------------------------
 * Contient toutes les données concernant les éléments à afficher dans notre
 * fenêtre.
 * -----------------------------------------------------------------------------
 * MODE mode  		      : Contient le mode du sokoban.
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

typedef struct sokoban {
	MODE mode;
	LEVEL lev;
	BUTTON but[NB_BUTTON];
	int Lev_H_Pix, Lev_W_Pix;
	float But_H_Pix, But_W_Pix;
} SOKOBAN;

/* # Structures de l'historique : =========================================== */

/** HISTOELEM
 * -----------------------------------------------------------------------------
 * Structure d'un élément de l'historique. Il s'agit d'un élément d'une liste
 * chaînée avec des informations propre à l'historique.
 * -----------------------------------------------------------------------------
 * ACTION_TYPE A	  : Type d'action effectué sur cet élément de
 *			    l'historique.
 * CASE* ptr1, ptr2	  : Deux pointeurs vers des cases à traitées (hormis
 * 			    la case du personnage)
 * struct histoElem* suiv : Pointeur vers l'élément suivant.
 */

typedef struct histoElem {
	ACTION_TYPE A;
	CASE* ptr1, ptr2;
	struct histoElem* suiv;
} HISTOELEM;

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** HISTORIC
 * -----------------------------------------------------------------------------
 * Structure d'un historique utilisé pour un niveau.
 * -----------------------------------------------------------------------------
 * struct histoElem* histoUndo : Pointeur vers le premier élément de l'historique
 * 			  	 où il faut piocher pour faire un Undo.
 * struct histoElem* histoRedo : Même chose avec Redo.
 */

typedef struct historic {
	struct histoElem* histoUndo;
	struct histoElem* histoRedo;
} HISTORIC;

#endif
