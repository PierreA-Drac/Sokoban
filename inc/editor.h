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
#include "sokoban.h"
#include "display.h"

/**
 * # Initialisation de l'éditeur ..............................................:
 */

/** preInitLevel_Editor
 * -----------------------------------------------------------------------------
 * Vérifie si le fichier est un ".xsb". Si oui, initialise le Sokoban avec
 * avec les infos de la ligne de commande pointées par argv pour éditer
 * un niveau.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S pré-initialisé.
 */

SOKOBAN preInitLevel_Editor(char** argv);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initSokoban_Editor
 * -----------------------------------------------------------------------------
 * Initialise le niveau a zéro et les boutons du Sokoban S pour être utiliser 
 * dans l'éditeur.
 * -----------------------------------------------------------------------------
 * Renvoie le Sokoban S prêt à être afficher et éditer.
 */

SOKOBAN initSokoban_Editor(SOKOBAN S);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initLevel_Editor
 * -----------------------------------------------------------------------------
 * Initialise le niveau avec des cases vides calcul les coordonnées des
 * cases, la taille du niveau en cases et en pixel.
 * -----------------------------------------------------------------------------
 * Renvoie un niveau vide prêt à être affiché.
 */

SOKOBAN initLevel_Editor(SOKOBAN S);

/**
 * # Édition de l'éditeur .....................................................:
 */

/** editSokoban_Editor
 * -----------------------------------------------------------------------------
 * Modifie le niveau du Sokoban S en mode éditeur en fonction de l'action A et
 * de l'étape du mode éditeur.
 * -----------------------------------------------------------------------------
 * Renvoie le SOKOBAN S modifié et prêt à être ré-afficher.
 */

SOKOBAN editSokoban_Editor(SOKOBAN S, ACTION A);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** changeCaseType_Editor
 * -----------------------------------------------------------------------------
 * Modifie le type d'une case d'indice h et w, varie entre mur, caisse sur
 * aire de stockage, personnage et case vide.
 * -----------------------------------------------------------------------------
 */

void changeCaseType_Editor(CASE** map, int h, int w);

#endif
