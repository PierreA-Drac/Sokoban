/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions d'affichage du programme.
 */

#include <stdio.h>
#include <string.h>
#include <uvsqgraphics.h>
#include "../inc/display.h"

/**
 * 1. Fonctions d'interface ...................................................:
 */

/**
 * 1.1 Initialisation de l'affichage ..........................................:
 */

void initDisplay(SOKOBAN S) {
	char title[BUFFER_SIZE];
	strcpy(title, "Pierre AYOUB - Mario Sokoban");
	if (S.mode.m_type == PLAY)
		strcat(title, " (Mode Jeu)");
	else
		strcat(title, " (Mode Éditeur)");
	init_graphics(S.Lev_W_Pix, S.Lev_H_Pix + NB_BUT_H*S.But_H_Pix + 
		      NB_SEPARATOR_V*H_SEPARATOR_V);
	SDL_WM_SetCaption(title, NULL);
	affiche_auto_off();
}

/**
 * 1.2 Affichage ..............................................................:
 */

void displaySokoban(SOKOBAN S) {
	fill_screen(black);
	displayButtons(S.but, S.But_W_Pix, S.But_H_Pix, S.mode);
	displayLevel(S.lev);
	displayInfosLevel(S.lev, S.But_H_Pix);
	affiche_all();
}

/* -------------------------------------------------------------------------- */

SOKOBAN initButtons(SOKOBAN S) {
	int i, NbButtons;
	/* Différenciation mode jeu vs éditeur */
	if (S.mode.m_type == PLAY || (S.mode.m_type == EDITOR && 
				      S.mode.m_step == PLAY_EDIT))
		NbButtons = NB_BUTTON;
	else
		NbButtons = NB_BUTTON_EDITOR_BUILDING;
	/* Hauteur et largeur pour la zone des boutons */
	S.But_H_Pix = ((S.Lev_H_Pix * H_BUT_RATIO) + 
		      (S.Lev_W_Pix * (H_BUT_RATIO/2))) / 2;
	if (S.But_H_Pix > 40)
		S.But_H_Pix = 40;
	S.But_W_Pix = S.Lev_W_Pix;
	for (i=0; i<NbButtons; i++) {
		/* Calcul des coordonnées pour tout les bouttons */
		S.but[i].tl.x = i*(S.But_W_Pix / NbButtons);
		S.but[i].tl.y = S.Lev_H_Pix + NB_BUT_H*S.But_H_Pix + 
				NB_SEPARATOR_V*H_SEPARATOR_V;
		S.but[i].tr.x = S.but[i].tl.x + (S.But_W_Pix / NbButtons);
		S.but[i].tr.y = S.but[i].tl.y;
		S.but[i].bl.x = S.but[i].tl.x;
		S.but[i].bl.y = S.but[i].tl.y - S.But_H_Pix;
		S.but[i].br.x = S.but[i].tr.x;
		S.but[i].br.y = S.but[i].tr.y - S.But_H_Pix;
		/* Initialisation du reste du bouton */
		S.but[i] = initSpecificButton(S.but[i], i, S.mode);
	}
	return S;
}

/* -------------------------------------------------------------------------- */

void displayMessage(char* text) {
	POINT p;
	int size = 20;
	p.x = WIDTH/2 - largeur_texte(text, size)/2;
	while (p.x < 0) {
		size--;
		p.x = WIDTH/2 - largeur_texte(text, size)/2;
	}
	p.y = hauteur_texte(text, size);
	aff_pol(text, size, p, tan);
	affiche_all();
	sleep(WAIT_TIME_MESSAGE);
}

/**
 * 1.3 Fermeture de l'affichage ...............................................:
 */

void quitDisplay() {
	/* Libère la surface de la fenêtre et ferme les systèmes de la SDL */
	printf("Free surface\n");
	SDL_FreeSurface(SDL_screen);
	printf("Quitsubsystem\n");
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	printf("Quit\n");
	SDL_Quit();
}

/**
 * 2. Fonctions locales .......................................................:
 */

BUTTON initSpecificButton(BUTTON B, int i, MODE M) {
	if (M.m_type == PLAY) {
		switch (i) {
			case 0 :
				B.name = "Undo"; 	B.A = UNDO;
				break;
			case 1 :
				B.name = "Redo";	B.A = REDO;
				break;
			case 2 :
				B.name = "Prev";	B.A = PREV;
				break;
			case 3 :
				B.name = "Next";	B.A = NEXT;
				break;
			case 4 :
				B.name = "Init";	B.A = INIT;
				break;
			case 5 :
				B.name = "Quit";	B.A = QUIT;
				break;
		}
	}
	else if (M.m_type == EDITOR) {
		if (M.m_step == BUILDING) {
			switch (i) {
				case 0 :
					B.name = "Play Back";	B.A = PLAY_BACK;
					break;
				case 1 :
					B.name = "Quit";	B.A = QUIT;
					break;
			}
		}
		else if (M.m_step == PLAY_EDIT) {
			switch (i) {
				case 0 :
					B.name = "Undo";	B.A = UNDO;
					break;
				case 1 :
					B.name = "Redo";	B.A = REDO;
					break;
				case 2 :
					B.name = "Init";	B.A = INIT;
					break;
				case 3 :
					B.name = "Alea";	B.A = ALEA;
					break;
				case 4 :
					B.name = "Save";	B.A = SAVE;
					break;
				case 5 :
					B.name = "Quit";	B.A = QUIT;
					break;
			}
		}
	}
	return B;
}

/* -------------------------------------------------------------------------- */

void displayButtons(BUTTON B[], float W, float H, MODE M) {
	int i, NbButtons;
	POINT Ptmp1, Ptmp2;
	/* Différenciation mode jeu vs éditeur */
	if (M.m_type == PLAY || (M.m_type == EDITOR && 
				 M.m_step == PLAY_EDIT))
		NbButtons = NB_BUTTON;
	else
		NbButtons = NB_BUTTON_EDITOR_BUILDING;
	for (i=0; i<NbButtons; i++) {
		draw_fill_rectangle(B[i].tl, B[i].br, tan);
	}
	/* Deuxième boucle pour afficher les éléments par dessus */
	for (i=0; i<NbButtons; i++) {
		/* Séparateur vertical */
		if (i < NbButtons - 1)
			draw_line(B[i].tr, B[i].br, dimgray);
		/* Nom du boutton */
		Ptmp1.x = B[i].tl.x + (W/NbButtons)/2;
		Ptmp1.y = B[i].tl.y - H/2;
		aff_pol_centre(B[i].name, WIDTH*W_BUT_TXT_RATIO*0.85
		+ H*H_BUT_TXT_RATIO*0.85, Ptmp1, black);
		/* Séparateur horizontal */
		Ptmp1.x = B[i].bl.x;	Ptmp1.y = B[i].bl.y;
		Ptmp2.x = B[i].br.x;	Ptmp2.y = B[i].br.y - H_SEPARATOR_V+1;
		draw_fill_rectangle(Ptmp1, Ptmp2, dimgray);
	}
}

/* -------------------------------------------------------------------------- */

void displayLevel(LEVEL L) {
	int i, j;
	char str[BUFFER_SIZE];
	for (j=0; j<L.h; j++) {
		for (i=0; i<L.w; i++) {
			if (L.map[j][i].type != EMPTY) {
				strcpy(str, "./sprites/");
				if (CASE_SIZE == 16)
					strcat(str, "16x/");
				else
					strcat(str, "32x/");
				if (L.map[j][i].type == WALL)
					strcat(str, "wall/"
					            "wall.bmp");
				else if (L.map[j][i].type == BOX)
					strcat(str, "box/"
						    "box.bmp");
				else if (L.map[j][i].type == BOX_STORAGE)
					strcat(str, "box_storage/"
						    "box_storage.bmp");
				else if (L.map[j][i].type == CHARAC)
					strcat(str, "mario/"
						    "mario.bmp");
				else if (L.map[j][i].type == BOX_ON_STORAGE)
					strcat(str, "box_on_storage"
						    "/box_on_storage.bmp");
				else if (L.map[j][i].type == CHARAC_ON_STORAGE)
					strcat(str, "mario_on_storage"
						    "/mario_on_storage.bmp");
				affiche_image(str, L.map[j][i].tl, 
					      CASE_SIZE, CASE_SIZE);
			}
		}
	}
}

/* -------------------------------------------------------------------------- */

void displayInfosLevel(LEVEL L, int h_but) {
	/* Fonction très moche, et mal organisé */
	POINT Ptmp1, Ptmp2;
	char filename[BUFFER_SIZE], numlevel[BUFFER_SIZE], nbhit[BUFFER_SIZE];
	/* Initialisation des chaînes de caractères à afficher */
	strcpy(filename, "Nom du fichier : ");
	strcat(filename, L.infos.filename);
	sprintf(numlevel, "Numero du niveau : %d", L.infos.numLevel);
	sprintf(nbhit, "Nombre de coups effectues : %d", L.infos.nbHit);
	/* Affichage du fond */
	Ptmp1.x = 0;     Ptmp1.y = L.map[0][0].tl.y + H_SEPARATOR_V + h_but;
	Ptmp2.x = WIDTH; Ptmp2.y = Ptmp1.y - h_but;
	draw_fill_rectangle(Ptmp1, Ptmp2, tan);
	/* Affichage du nombre de coups joués */
	aff_pol(nbhit, h_but*0.125+WIDTH*0.0115, Ptmp1, black);
	/* Affichage du numéro du niveau */
	Ptmp1.y -= h_but*0.26; Ptmp1.x += 0.7*WIDTH;
	aff_pol_centre(numlevel, h_but*0.125+WIDTH*0.0115, Ptmp1, black);
	/* Affichage du nom du fichier */
	Ptmp1.y -= h_but*0.24; Ptmp1.x = 0;
	aff_pol(filename, h_but*0.125+WIDTH*0.0115, Ptmp1, black);
	/* Affichage du séparateur horizontal */
	Ptmp1.x = 0;     Ptmp1.y = L.map[0][0].tl.y + H_SEPARATOR_V-1;
	Ptmp2.x = WIDTH; Ptmp2.y = Ptmp1.y - H_SEPARATOR_V+1;
	draw_fill_rectangle(Ptmp1, Ptmp2, dimgray);
}
