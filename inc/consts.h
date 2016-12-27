/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient toutes les constantes et énumérations 
 * utilisées dans le jeu.
 */

#ifndef __CONSTS_H
#define __CONSTS_H

/**
 * 1. Constantes ..............................................................:
 */

/**
 * 1.1 Divers .................................................................:
 */

/* Taille du buffer */
#define BUFFER_SIZE 256

/* Nombre de coups joués aléatoirement en mode édition par l'ordinateur */
#define NB_ALEA 40

/**
 * 1.2 Boutons ................................................................:
 */

/* Nombre de boutons en mode jeu */
#define NB_BUTTON 6
/* Nombre de boutons en mode éditeur et à l'étape de construction du niveau */
#define NB_BUTTON_EDITOR_BUILDING 2

/* Ratio appliqué aux dimensions du niveau pour calculer la hauteur des 
 * boutons */
#define H_BUT_RATIO 0.13

/* Ratios appliqués aux dimensions de la fenêtre pour calculer la taille
 * de la police des titres des boutons */
#define H_BUT_TXT_RATIO 0.0175 
#define W_BUT_TXT_RATIO 0.03

/* N.B. : Les ratios ci-dessus sont déterminés par des tests empiriques. */

/**
 * 1.3 Affichage ..............................................................:
 */

/* Taille d'une case carré en pixel, peut prendre les valeurs 16 et 32 */
#define CASE_SIZE 32
/* N.B. : Les affichage sont très long en 16x16, surement car la SDL doit faire
 * beaucoup de traitements pour afficher de si petites images. Les niveaux ne
 * sont donc pas très jouable en 16x16, mais je laisse quand même la possibilité
 * d'essayer maintenant que cela est programmé. */

/* Nombre de cases en hauteur et en largeur d'une map en cours de création
 * dans le mode éditeur */
#define HEIGHT_MAP_EDITOR 19
#define WIDTH_MAP_EDITOR 30

/* Nombre de séparateur horizontaux */
#define NB_SEPARATOR_V 2

/* Hauteur des séparateurs horizontaux (en pixel) */
#define H_SEPARATOR_V 2

/* Nombre d'emplacement de la hauteur des boutons utilisés */
#define NB_BUT_H 2

/* Temps d'attente (en secondes) pour les messages affichés à l'écran */
#define WAIT_TIME_MESSAGE 3

/**
 * 2. Énumérations ............................................................:
 */

/**
 * 2.1 Déclarations ...........................................................:
 */

typedef enum action_type ACTION_TYPE;
typedef enum mode_type MODE_TYPE;
typedef enum mode_editor_step MODE_EDITOR_STEP;
typedef enum case_type CASE_TYPE;

/**
 * 2.2 Définitions ............................................................:
 */

/** ACTION_TYPE
 * =============================================================================
 * Indique quelle action à été choisie par l'utilisateur.
 * =============================================================================
 * CHARAC      : Déplace le personnage sur le jeu.
 * UNDO, REDO  : Reculer ou avancer dans l'historique.
 * INIT, QUIT  : Réinitialise le niveau en cours ou quitte le jeu.
 * PREV, NEXT  : Lance le niveau suivant ou précédent.
 * SAVE, ALEA  : Sauvegarde le niveau, ou fait jouer
 * 	         l'ordinateur aléatoirement.
 * CHANGE_CASE : Modifie le type d'une case de coordonnées A.p dans l'éditeur.
 * PLAY_BACK   : Passer du mode éditon à jouer à l'envers.
 * NONE        : Aucune action.
 */

enum action_type {
	CHARAC_TOP, CHARAC_BOTTOM, CHARAC_LEFT, CHARAC_RIGHT,
	UNDO, REDO,
	INIT, QUIT,
	PREV, NEXT,
	SAVE, ALEA,
	CHANGE_CASE,
	PLAY_BACK,
	NONE
};

/* -------------------------------------------------------------------------- */

/** MODE_TYPE
 * =============================================================================
 * Indique dans quel mode du programme on se trouve.
 * =============================================================================
 * PLAY   : Mode de jeu dans un niveau.
 * EDITOR : Mode de création de niveau.
 */

enum mode_type {
	PLAY, EDITOR
};

/* -------------------------------------------------------------------------- */

/** MODE_EDITOR_STEP
 * =============================================================================
 * Indique dans quellé étape du mode éditeur on se trouve.
 * =============================================================================
 * BUILDING   : Mode de création du niveau à la souris.
 * PLAY_EDIT  : Mode où on joue à l'envers pour finaliser le placements des
 * 		caisses et du personnage.
 */

enum mode_editor_step {
	BUILDING, PLAY_EDIT
};

/* -------------------------------------------------------------------------- */

/** CASE_TYPE
 * =============================================================================
 * Indique le type d'une case.
 * =============================================================================
 * WALL 	     : Mur.
 * BOX 	       	     : Caisse.
 * BOX_STORAGE       : Rangement d'une caisse.
 * CHARAC 	     : Personnage.
 * BOX_ON_STORAGE    : Caisse sur son rangement.
 * CHARAC_ON_STORAGE : Personnage sur une zone de rangement.
 * EMPTY	     : Case vide.
 */

enum case_type {
	WALL, BOX, BOX_STORAGE, CHARAC, BOX_ON_STORAGE, CHARAC_ON_STORAGE, EMPTY
};

#endif
