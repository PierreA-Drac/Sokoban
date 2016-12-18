/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions nécéssaire à la gestion des données 
 * durant une partie, et à la lecture dans le fichier .xsb.
 */

#ifndef __GAME_H
#define __GAME_H

#include "structs.h"
#include "consts.h"
#include "sokoban.h"
#include "display.h"

/**
 * ####  -----------------------------------------------------------------  ####
 * ##	  Fonctions =====================================================     ##
 * ####  -----------------------------------------------------------------  ####
 */
 
/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 * Initialisation du Sokoban : -------------------------------------------------
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initFirstLevel_Game 
 * -----------------------------------------------------------------------------
 * Vérifie si le fichier est un ".xsb". Si oui, initialise le Sokoban avec
 * avec les infos de la ligne de commande pointées par argv pour jouer le 
 * premier niveau.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S pré-initialisé.
 */

SOKOBAN initFirstLevel_Game(char** argv);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initOtherLevel_Game 
 * -----------------------------------------------------------------------------
 * Vérifie si le fichier est un ".xsb". Si oui, initialise le Sokoban avec
 * avec les infos de la ligne de commande pointées par argv pour jouer le 
 * niveau spécifié.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S pré-initialisé.
 */

SOKOBAN initOtherLevel_Game(char** argv);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initSokoban_Game 
 * -----------------------------------------------------------------------------
 * Initialise les informations de jeu encore non-initalisé, le niveau et 
 * les bouttons à afficher. Le niveau passe la vérification de solubilité.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S initialisé, résoluble et prêt à être afficher.
 */

SOKOBAN initSokoban_Game(SOKOBAN S);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** initLevel 
 * -----------------------------------------------------------------------------
 * Initialise le niveau contenu dans le Sokoban à partir du fichier, ainsi que
 * la taille en pixel du niveau.
 * -----------------------------------------------------------------------------
 * Renvoie un SOKOBAN S avec un niveau initalisé.
 */

SOKOBAN initLevel(SOKOBAN S);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** setLevelPosition 
 * -----------------------------------------------------------------------------
 * Place le pointeur de lecture du fichier qui contient le niveau à
 * l'emplacement où commencer la lecture du niveau par effet de bord.
 * -----------------------------------------------------------------------------
 * Renvoie TRUE si le placement à réussis, FALSE si le niveau
 * n'existe pas.
 */

int setLevelPosition(FILE* F, int numLevel);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** createLevel
 * -----------------------------------------------------------------------------
 * Gère les déplacement dans le ficher pour l'initialisation du niveau, et crée
 * un niveau prêt à être utilisé à partir d'un fichier.
 * -----------------------------------------------------------------------------
 * Renvoie un LEVEL L prêt à être utilisé.
 */

LEVEL createLevel(FILE* F, LEVEL L);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** calcLevelSize
 * -----------------------------------------------------------------------------
 * Lit le fichier pour calculer la taille d'un taille niveau et déterminer son
 * allocation mémoire.
 * -----------------------------------------------------------------------------
 * Renvoie un LEVEL L avec sa taille w (width / largeur) et h (height / hauteur)
 * initialisé.
 */

LEVEL calcLevelSize(FILE* F, LEVEL L);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** readMap
 * -----------------------------------------------------------------------------
 * Lit le fichier qui contient le niveau pour initalisé la map du niveau avec
 * les types des cases qu'il contient, et initialise les coordonnées des cases.
 * -----------------------------------------------------------------------------
 * Renvoie un tableau de double dimensions CASE** map contenant la map du niveau
 * actuel.
 */

CASE** readMap(FILE* F, int w, int h);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** calcPosMap
 * -----------------------------------------------------------------------------
 * Calcul les positions en pixels des cases de la map en fonction de 
 * la largeur w et de la hauteur h et les inscrits par effet de bord.
 * -----------------------------------------------------------------------------
 */

void calcPosMap(CASE** map, int w, int h);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** findCharac
 * -----------------------------------------------------------------------------
 * Cherche la case dans la map de largeur w et de hauteur h qui contient le
 * personnage.
 * -----------------------------------------------------------------------------
 * Renvoie un point comportant les indices en largeur et en hauteur de la case 
 * qui contient le personnage.
 */

POINT findCharac(CASE** map, int w, int h);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 * Édition du Sokoban : --------------------------------------------------------
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** editSokoban_Game
 * -----------------------------------------------------------------------------
 * Modifie le niveau L en fontion de l'action A dans le cadre d'une partie de
 * jeu.
 * -----------------------------------------------------------------------------
 * Renvoie le niveau L modifié et prêt à être traité.
 */

LEVEL editSokoban_Game(LEVEL L, ACTION A);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** nextLevel
 * -----------------------------------------------------------------------------
 * Permet de faire passer le niveau au niveau suivant.
 * -----------------------------------------------------------------------------
 * Renvoie un LEVEL L prêt à être ré-initialisé au niveau suivant.
 */

LEVEL nextLevel(LEVEL L);

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

/** prevLevel
 * -----------------------------------------------------------------------------
 * Permet de faire passer le niveau au niveau précédent.
 * -----------------------------------------------------------------------------
 * Renvoie un LEVEL L prêt à être ré-initialisé au niveau précédent.
 */

LEVEL prevLevel(LEVEL L);

#endif
