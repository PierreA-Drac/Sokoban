/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions permettant de manipuler l'historique
 * d'un Sokoban.
 */

#ifndef __HISTORIC_H
#define __HISTORIC_H

#include "structs.h"
#include "consts.h"

/**
 * 1. Fonctions d'interface ...................................................:
 */

/**
 * 1.1 Création et initialisation .............................................:
 */

/** createHisto
 * =============================================================================
 * Crée un historique utilisé pour gérer un niveau.
 * =============================================================================
 * Retourne un historique H initialisé.
 */

HISTORIC createHisto();

/* -------------------------------------------------------------------------- */

/** createHistoElem
 * =============================================================================
 * Crée un élément à insérer dans une pile d'un historique d'un niveau.
 * =============================================================================
 * Renvoie un pointeur sur l'élément initilisé avec mémoire allouée.
 */

HISTOELEM* createHistoElem();

/**
 * 1.2 Ajout et retrait d'élément .............................................:
 */

/** pushHistoElem
 * =============================================================================
 * Ajoute l'élément pointé par E sur la pile S.
 * =============================================================================
 * Renvoie la pile S avec son élément de tête mis à jour.
 */

STACK pushHistoElem(STACK S, HISTOELEM* E);

/* -------------------------------------------------------------------------- */

/** popHistoElem
 * =============================================================================
 * Récupère l'élément de tête de la pile S et le copie dans l'élément pointé
 * par E.
 * =============================================================================
 * Renvoie la pile S avec son élément de tête supprimé et libéré de la mémoire.
 */

STACK popHistoElem(STACK S, HISTOELEM* E);

/**
 * 1.3 Libération de la mémoire ...............................................:
 */

/** freeStack
 * =============================================================================
 * Libère de la mémoire la pile S.
 * =============================================================================
 * Retourne une pile vide.
 */

/* -------------------------------------------------------------------------- */

STACK freeStack(STACK S);

/** freeHistoElem
 * =============================================================================
 * Libère de la mémoire l'élément d'historique pointé par E.
 * =============================================================================
 * Renvoie un pointeur NULL.
 */

HISTOELEM* freeHistoElem(HISTOELEM* E);

#endif
