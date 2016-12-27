/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions de gestion des données dans l'éditeur,
 * et à l'écriture du niveau dans un fichier .xsb.
 */

#ifndef __EDITOR_H
#define __EDITOR_H

#include "structs.h"
#include "consts.h"

/**
 * 1. Fonctions d'interface ...................................................:
 */

/**
 * 1.1 Initialisation de l'éditeur ............................................:
 */

/** preInitLevel_Editor
 * =============================================================================
 * Vérifie si le fichier est un ".xsb". Si oui, initialise le Sokoban avec
 * avec les infos de la ligne de commande pointées par argv pour éditer
 * un niveau.
 * =============================================================================
 * Renvoie un SOKOBAN S pré-initialisé.
 */

SOKOBAN preInitLevel_Editor(char** argv);

/* -------------------------------------------------------------------------- */

/** initSokoban_Editor
 * =============================================================================
 * Initialise le niveau a zéro et les boutons du Sokoban S pour être utiliser 
 * dans l'éditeur.
 * =============================================================================
 * Renvoie le Sokoban S prêt à être afficher et éditer.
 */

SOKOBAN initSokoban_Editor(SOKOBAN S);

/**
 * 1.2 Édition de la map ......................................................:
 */

/** editSokoban_Editor
 * =============================================================================
 * Modifie le niveau du Sokoban S en mode éditeur en fonction de l'action A et
 * de l'étape du mode éditeur.
 * =============================================================================
 * Renvoie le SOKOBAN S modifié et prêt à être ré-afficher.
 */

SOKOBAN editSokoban_Editor(SOKOBAN S, ACTION A);

/**
 * 2.2 Fonctions locales ......................................................:
 */

/** initLevel_Editor
 * =============================================================================
 * Initialise le niveau avec des cases vides calcul les coordonnées des
 * cases, la taille du niveau en cases et en pixel.
 * =============================================================================
 * Renvoie un niveau vide prêt à être affiché.
 */

SOKOBAN initLevel_Editor(SOKOBAN S);

/* -------------------------------------------------------------------------- */

/** getNumLevel
 * =============================================================================
 * Permet de connaître le numéro du niveau que l'on va crée en
 * fonction du fichier du nom pointée par filename.
 * =============================================================================
 * Renvoie 1 si le fichier n'existe pas, sinon renvoie le numéro du dernier
 * niveau + 1.
 */

int getNumLevel(char* filename);

/* -------------------------------------------------------------------------- */

/** editSokoban_EditorBuild
 * =============================================================================
 * Modifie le niveau du Sokoban S en mode éditeur à l'étape de construction
 * du niveau en fonction de l'action A.
 * =============================================================================
 * Renvoie le Sokoban S modifié.
 */

SOKOBAN editSokoban_EditorBuild(SOKOBAN S, ACTION A);

/* -------------------------------------------------------------------------- */

/** editSokoban_EditorPlay
 * =============================================================================
 * Modifie le niveau du Sokoban S en mode éditeur à l'étape de jouer à l'envers
 * en fonction de l'action A.
 * =============================================================================
 * Renvoie le Sokoban S modifié.
 */

SOKOBAN editSokoban_EditorPlay(SOKOBAN S, ACTION A);

/* -------------------------------------------------------------------------- */

/** changeCaseType_Editor
 * =============================================================================
 * Modifie le type d'une case d'indice h et w, varie entre mur, caisse sur
 * aire de stockage, personnage et case vide.
 */

void changeCaseType_Editor(CASE** map, int h, int w);

/* -------------------------------------------------------------------------- */

/** alea
 * =============================================================================
 * Joue NB_ALEA fois aléatoirement à la place du joueur sur le Sokoban S.
 * =============================================================================
 * Renvoie le Sokoban S modifié.
 */

SOKOBAN alea(SOKOBAN S);

/**
 * 2.2 Écriture du Sokoban ....................................................:
 */

/** save
 * =============================================================================
 * Sauvegarde le Sokoban S dans le fichier spécifié par S.lev.infos.filename,
 * soit en créant le fichier s'il n'existe pas, soit en mettant à jour le
 * fichier existant.
 * =============================================================================
 * Renvoie TRUE si le niveau à bien été écris, sinon FALSE.
 */

int save(SOKOBAN S);

/* -------------------------------------------------------------------------- */

/** calcRealLevelSize
 * =============================================================================
 * Calcul les indices de début et de fin de hauteur (h_start & h_end) et de 
 * largeur (w_start & w_end) pour parcourir le niveau sans les lignes vides 
 * et les fin de lignes vides.
 */

void calcRealLevelSize(LEVEL L, int* w_start, int* w_end,
				int* h_start, int* h_end);

/* -------------------------------------------------------------------------- */

/** writeLevelNum
 * =============================================================================
 * Saute une ligne et écris le numéro du niveau sur une ligne de
 * commentaire.
 */

void writeLevelNum(FILE* F, int n);

/* -------------------------------------------------------------------------- */

/** writeLevelSchema
 * =============================================================================
 * Saute une ligne et écris le schéma du niveau.
 */

void writeLevelSchema(FILE* F, CASE** map, int w_start, int w_end,
					   int h_start, int h_end);

/* -------------------------------------------------------------------------- */

/** whatIsChar
 * =============================================================================
 * Détermine le caractère représentant la case en fonction du type passé 
 * en argument.
 * =============================================================================
 * Renvoie le caractère pour écrire la case.
 */

char whatIsChar(CASE_TYPE type);

#endif
