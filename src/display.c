/**
 * # Nom ..........: AYOUB
 * # Prénom .......: Pierre
 * # N° étudiant ..: 21501002
 *
 * Ce fichier contient les fonctions d'affichage du programme.
 */

#include "../inc/display.h"

/**
 * # Initialisation de l'affichage ............................................:
 */

void initDisplay(SOKOBAN S) {
	init_graphics(S.Lev_W_Pix, S.Lev_H_Pix + NB_BUT_H*S.But_H_Pix + 
		      NB_SEPARATOR_V*H_SEPARATOR_V);
	SDL_WM_SetCaption("Mario Sokoban - Pierre AYOUB", NULL);
	affiche_auto_off();
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

SOKOBAN initButtons(SOKOBAN S) {
	int i;
	S.But_H_Pix = ((S.Lev_H_Pix * H_BUT_RATIO) + 
		      (S.Lev_W_Pix * (H_BUT_RATIO/2))) / 2;
	if (S.But_H_Pix > 40)
		S.But_H_Pix = 40;
	S.But_W_Pix = S.Lev_W_Pix;
	for (i=0; i<NB_BUTTON; i++) {
		/* Calcul des coordonnées pour tout les bouttons */
		S.but[i].tl.x = i*(S.But_W_Pix / NB_BUTTON);
		S.but[i].tl.y = S.Lev_H_Pix + NB_BUT_H*S.But_H_Pix + 
				NB_SEPARATOR_V*H_SEPARATOR_V;
		S.but[i].tr.x = S.but[i].tl.x + (S.But_W_Pix / NB_BUTTON);
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

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

BUTTON initSpecificButton(BUTTON B, int i, MODE M) {
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
	return B;
}

/**
 * # Affichage ................................................................:
 */

void displaySokoban(SOKOBAN S) {
	fill_screen(black);
	displayButtons(S.but, S.But_W_Pix, S.But_H_Pix);
	displayLevel(S.lev);
	displayInfosLevel(S.lev, S.But_H_Pix);
	affiche_all();
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

void displayButtons(BUTTON B[], float W, float H) {
	int i;
	POINT Ptmp1, Ptmp2;
	for (i=0; i<NB_BUTTON; i++) {
		draw_fill_rectangle(B[i].tl, B[i].br, tan);
	}
	/* Deuxième boucle pour afficher les éléments par dessus */
	for (i=0; i<NB_BUTTON; i++) {
		/* Séparateur vertical */
		if (i < NB_BUTTON - 1)
			draw_line(B[i].tr, B[i].br, dimgray);
		/* Nom du boutton */
		Ptmp1.x = B[i].tl.x + (W/NB_BUTTON)/2;
		Ptmp1.y = B[i].tl.y - H/2;
		aff_pol_centre(B[i].name, WIDTH*W_BUT_TXT_RATIO*0.85
		+ H*H_BUT_TXT_RATIO*0.85, Ptmp1, black);
		/* Séparateur horizontal */
		Ptmp1.x = B[i].bl.x;	Ptmp1.y = B[i].bl.y;
		Ptmp2.x = B[i].br.x;	Ptmp2.y = B[i].br.y - H_SEPARATOR_V+1;
		draw_fill_rectangle(Ptmp1, Ptmp2, dimgray);
	}
}

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

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

/**
 * = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
 */

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

/**
 * # Fermeture de l'affichage .................................................:
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
