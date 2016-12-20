/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions permettant de manipuler l'historique
 * d'un Sokoban.
 */

#include "../inc/historic.h"

/**
 * # Création et initialisation ...............................................:
 */

HISTORIC createHisto() {
	HISTORIC H;
	H.histoUndo.head = NULL;
	H.histoRedo.head = NULL;
	return H;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

HISTOELEM* createHistoElem() {
	HISTOELEM* E;
	E = malloc(sizeof(HISTOELEM));
	if (!E) {
		fprintf(stderr, "Memory allocation error for histoElem\n");
		exit(EXIT_FAILURE);
	}
	E->suiv = NULL;
	E->ptr1 = NULL;
	E->ptr2 = NULL;
	E->A = NONE;
	return E;
}

/**
 * # Ajout et retrait d'élément ...............................................:
 */

STACK pushHistoElem(STACK S, HISTOELEM* E) {
	if (!E) {
		fprintf(stderr, "Impossible to insert an empty element\n");
		return S;
	}
	E->suiv = S.head;
	S.head = E;
	return S;
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

STACK popHistoElem(STACK S, HISTOELEM* E) {
	HISTOELEM* toFree;
	/* Guard */
	if (!S.head) {
		fprintf(stderr, "Impossible to pull an element from an "
				"empty stack\n");
		return S;
	}
	if (!E) {
		fprintf(stderr, "Impossible to pull an element to an "
				"unallocated element\n");
		return S;
	}
	/* Copie du premier élément */
	E->A = S.head->A;
	E->ptr1 = S.head->ptr1;
	E->ptr2 = S.head->ptr2;
	/* Sauvegarde et suppression du premier élément, et MAJ de la pile */
	toFree = S.head;
	S.head = S.head->suiv;
	free(toFree);
	return S;
}

/**
 * # Libération de la mémoire .................................................:
 */

STACK freeStack(STACK S) {
	if (!S.head) {
		/* Fin de la pile */
		return S;
	}
	else {
		/* Avancer dans la pile */
		STACK S2 = S;
		S2.head = S2.head->suiv;
		S2 = freeStack(S2);
		/* Libération de l'élément actuel */
		free(S.head);
		S.head = NULL;
		return S;
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

HISTOELEM* freeHistoElem(HISTOELEM* E) {
	free(E);
	return NULL;
}
