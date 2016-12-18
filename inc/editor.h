/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions de gestion des données dans l'éditeur.
 */

#ifndef __EDITOR_H
#define __EDITOR_H

#include "structs.h"
#include "consts.h"

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  Fonctions =====================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */

/** initLevel_Editor
 * -----------------------------------------------------------------------------
 * Vérifie si le fichier est un ".xsb". Si oui, initialise le Sokoban avec
 * avec les infos de la ligne de commande pointées par argv pour éditer
 * un niveau.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S pré-initialisé.
 */

SOKOBAN initLevel_Editor(char** argv);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN initSokoban_Editor(SOKOBAN S);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

LEVEL editSokoban_Editor(LEVEL L, ACTION A);

#endif
