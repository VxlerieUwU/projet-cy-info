#include "CosmicYonder.h"
#include "logger.h"

#include "ui/ui.h"
#include <ncurses.h>

int main()
{
    int hauteur, longueur;

    char logBuffer[255];

    setlocale(LC_ALL,""); // nécessaire pour UTF-8

    createLog();
    logMessage(INFO, "init ncurses");
    initscr(); //initialise l'ecran
    noecho(); //empeche d'afficher les caracteres saisis dans le terminal
    cbreak(); //permet de quitter le programme avec Ctrl+c
    curs_set(0); //rend le curseur invisible
    initCouleur();
	int etatJeu = 1; //permet de quitter le jeu si besoin
    getmaxyx(stdscr,hauteur,longueur); //recupere la taille du terminal
	
    WINDOW* mainwin = newwin(hauteur,longueur,0,0);
    sprintf(logBuffer, "window longueur = %d, hauteur = %d", longueur, hauteur);
    logMessage(INFO, logBuffer);
    clearBuf(logBuffer);

    // creer une fenetre de la taille du terminal ou le coin superieur gauche est a la position (0,0)
    refresh();
    wrefresh(mainwin);
    nodelay(mainwin, true);
    //refresh et wrefresh permettent de rafraichir l ecran pour y afficher ce qui est contenu dans la memoire
    keypad(mainwin, true); // active la possibilite de lire certains caracteres commes les fleches du clavier
    keypad(stdscr, true);
    // initialisation des interfaces graphiques
    int touche = -1;
    int fichier_exists = 0;

	while(etatJeu){

		int etatPartie = 1; // permet de quitter la partie si besoin
        int etatSauvegarde = 0; // effectue une sauvegarde si égal à 1
		Partie * partie = creerPartie();


		Menu * menu = cosmicMenu(hauteur, longueur); //affiche le menu
		MiniMenu * parametres = options(longueur / 2, hauteur / 2, hauteur / 2, longueur / 2);
		MiniMenu * pause = pauseMenu(longueur / 2, hauteur / 2, hauteur / 2, longueur / 2);
        InvMenu * inventMenu = initInvMenu(longueur / 2, hauteur / 2, hauteur / 2, longueur / 2);
		EntreeTexte * graineEntree = graineMenu(longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);
        EntreeTexte * nomEntree = nomMenu(longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);
        EntreeTexte * sauvegardeEntree = sauvegardeMenu(longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);

		renduFenetreMenu(mainwin, *menu, hauteur, longueur);

		while(menu->selEtat == 0) {
            wrefresh(mainwin);

            touche = wgetch(mainwin);
			renduBoutons(mainwin, menu->boutons, menu->selecteur, menu->nbBoutons);
            entreeMenu(menu, touche);

        }


		switch(menu->selecteur) {
			case 0:
				//NOUVELLE PARTIE
				wclear(mainwin);
				touche = -1;
				while(graineEntree->valide == 0) {
					touche = wgetch(mainwin);
					renduFenetreEntree(mainwin, graineEntree, longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);
                    entreeNum(graineEntree, touche);
					wrefresh(mainwin);
					napms(1000 / IMAGES_PAR_SECONDE);
				}
				wclear(mainwin);
				// init graine
				partie->graine = creation_graine(graineEntree);
				srand(partie->graine);
				//init partie->carte

				//creation de la premiere salle
				partie->carte[0] = creerSalleProced(longueur/2, hauteur/2, 4, -1,mainwin, &partie->nsalles,&partie->objets_speciaux_apparus,partie->portesNonOuvertes);
				partie->salles_existantes++;

				//init joueur
				initJoueur(partie->joueur);
				partie->joueur->x = partie->carte[0]->x + partie->carte[0]->longueur/2;
				partie->joueur->y = partie->carte[0]->y + partie->carte[0]->hauteur/2;
                while(nomEntree->valide == 0) {
                    touche = wgetch(mainwin);
                    renduFenetreEntree(mainwin, nomEntree, longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);
                    entreeTexte(nomEntree, touche);
                    wrefresh(mainwin);
                    napms(1000 / IMAGES_PAR_SECONDE);
                }
                partie->joueur->nom = malloc(strlen(nomEntree->buffer) + 1);
                strcpy(partie->joueur->nom, nomEntree->buffer);

                break;
			case 1:
				//CHARGER PARTIE
				wclear(mainwin);
                do {
                    sauvegardeEntree->valide = 0;
                    while(sauvegardeEntree->valide == 0) {
                        touche = wgetch(mainwin);
                        renduFenetreEntree(mainwin, sauvegardeEntree, longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);
                        entreeTexte(sauvegardeEntree, touche);
                        wrefresh(mainwin);
                        napms(1000 / IMAGES_PAR_SECONDE);
                    }
                    fichier_exists = verifFichier(sauvegardeEntree->buffer);
                    if(!fichier_exists) { // affiche erreur
                        for(int i = 0; i < longueur/2-1; i++) {
                            mvwaddch(mainwin, hauteur / 2, longueur / 2 - 8 + i, ' ');
                        }
                        wattron(mainwin, COLOR_PAIR(1));
                        mvwprintw(mainwin, hauteur / 2, longueur / 2 - 8, "%s.json inexistant", sauvegardeEntree->buffer);
                        wattroff(mainwin, COLOR_PAIR(1));
                    }

                } while (!fichier_exists);
                partie = loadGame(sauvegardeEntree->buffer);

                break;
			case 2:
				wclear(mainwin);
				while(parametres->curseur !=3) {
					renduFenetreOptions(mainwin, *parametres);
					touche = wgetch(mainwin);
					entreeMessage(parametres, touche);
					wrefresh(mainwin);
					napms(1000 / IMAGES_PAR_SECONDE);

				}
				break;
			case 3:
				// NOT IMPLEMENTED
				endwin();//ferme la fenetre
				moveLog();
				return 0;
			default:
				break;
		}

		HUD * hud = hudJeu(0, hauteur - hauteur/6, hauteur / 6, longueur, partie->joueur, partie->minuteur);
		Texte * resTxt = respawnTexte(longueur/2 - longueur/5, hauteur/2 - hauteur/5, longueur);

		

		//positionne le joueur au centre de l ecran
        wattron(mainwin, COLOR_PAIR(3));
        mvwaddch(mainwin,partie->joueur->y,partie->joueur->x, 'o');
        wattroff(mainwin, COLOR_PAIR(3));

		touche = wgetch(mainwin);//recupere touche pressee

		logMessage(INFO, "fin init");
		while(etatPartie){ // BOUCLE DU JEU
			//boucle qui parcourt toutes les salles existantes
			for(int j=0;j<partie->salles_existantes;j++){
				//boucle qui parcourt toutes les portes de la salle
				for(int k=0; k<partie->carte[j]->nportes;k++){
					/*conditions servent a creer une salle quand le joueur passe devant une porte,
					en fonction de la position de la porte par rapport au joueur
					verifie parmi le tableau de salles si une porte se trouve a cote du joueur et cree une salle si c'est le cas*/
					if(partie->carte[j]->portes[k].ouvert==0){
						//porte en haut
						if(partie->carte[j]->portes[k].x+partie->carte[j]->x==partie->joueur->x && partie->carte[j]->portes[k].y+partie->carte[j]->y==partie->joueur->y-1){
							if(partie->carte[partie->salles_existantes] != NULL) {
								libereSalle(partie->carte[partie->salles_existantes]);
							}
							partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,BAS,mainwin, &(partie->nsalles), &partie->objets_speciaux_apparus, partie->portesNonOuvertes);
							ouvrirPorte(partie->carte,j,partie->salles_existantes, k, BAS);
							dessineSalle(mainwin, partie->carte[partie->salles_existantes]);
							partie->salles_existantes++;
							partie->portesNonOuvertes--;
						}
						//porte en bas
						else if(partie->carte[j]->portes[k].x+partie->carte[j]->x==partie->joueur->x && partie->carte[j]->portes[k].y+partie->carte[j]->y==partie->joueur->y+1){
							if(partie->carte[partie->salles_existantes] != NULL) {
								libereSalle(partie->carte[partie->salles_existantes]);
							}
							partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,HAUT,mainwin,&partie->nsalles ,&partie->objets_speciaux_apparus, partie->portesNonOuvertes);
							ouvrirPorte(partie->carte,j,partie->salles_existantes, k, HAUT);
							dessineSalle(mainwin, partie->carte[partie->salles_existantes]);
							partie->salles_existantes++;
							partie->portesNonOuvertes--;
						}
						//porte a gauche
						else if(partie->carte[j]->portes[k].x+partie->carte[j]->x==partie->joueur->x-1 && partie->carte[j]->portes[k].y+partie->carte[j]->y==partie->joueur->y){
							if(partie->carte[partie->salles_existantes] != NULL) {
								libereSalle(partie->carte[partie->salles_existantes]);
							}
							partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,DROITE,mainwin,&partie->nsalles,&partie->objets_speciaux_apparus, partie->portesNonOuvertes);
							ouvrirPorte(partie->carte,j,partie->salles_existantes, k, DROITE);
							dessineSalle(mainwin, partie->carte[partie->salles_existantes]);
							partie->salles_existantes++;
							partie->portesNonOuvertes--;
						}
						//porte a droite
						else if(partie->carte[j]->portes[k].x+partie->carte[j]->x==partie->joueur->x+1 && partie->carte[j]->portes[k].y+partie->carte[j]->y==partie->joueur->y){
							if(partie->carte[partie->salles_existantes] != NULL) {
								libereSalle(partie->carte[partie->salles_existantes]);
							}
							partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,GAUCHE,mainwin,&partie->nsalles,&partie->objets_speciaux_apparus, partie->portesNonOuvertes);
							ouvrirPorte(partie->carte,j,partie->salles_existantes, k, GAUCHE);
							dessineSalle(mainwin, partie->carte[partie->salles_existantes]);
							partie->salles_existantes++;
						}
					}
				}
			}
			partie->portesNonOuvertes = compteurPortesNonOuvertes(partie->carte, partie->salles_existantes);

			//interactions du joueur avec le jeu
			interactions(touche, partie->joueur,partie->carte, partie->salles_existantes, mainwin,&(partie->nb_obj_inv), &(partie->nb_obj_spe_inv));

			//boucle qui parcourt toutes les salles existantes
			for(int i=0; i<partie->salles_existantes; i++){ 
				//condition verifie si l ennemi associe a la salle existe puis actualise son etat et le deplace en fonction du compteur
				if(partie->carte[i]->ennemi_existant==1){ 
					ennemietat(partie->carte[i]->ennemi,partie->carte[i],partie->joueur,mainwin);
					if(partie->mvEnnemic>40){
						ennemimv(partie->carte[i]->ennemi,partie->carte[i],partie->joueur,mainwin);
					}
				}
			}	
			//efface l'ecran	
			wclear(mainwin);
			//affiche carte
			dessineSalles(mainwin, partie->carte, partie->salles_existantes);
			//affiche ennemis
			for(int i=0; i<partie->salles_existantes; i++){
				if(partie->carte[i]->ennemi_existant==1){
					afficheEnnemi(partie->carte[i]->ennemi, mainwin);
				}
			}	
			//affiche joueur
            wattron(mainwin, COLOR_PAIR(3));
			mvwaddch(mainwin,partie->joueur->y,partie->joueur->x, 'o');
            wattroff(mainwin, COLOR_PAIR(3));
			//affiche hud
			
			maj_niveau(partie->joueur);
				
			
			renduHUD(mainwin, hud, partie->minuteur, partie->joueur, partie->nb_obj_inv, partie->nb_obj_spe_inv);
			//rafraichit l'ecran
			wrefresh(mainwin);
			etatPartie = condition_victoire(partie);

			/*on recupere la touche pressee
			si le joueur appuie sur echap, le jeu est mis en pause*/
			touche = wgetch(mainwin);
			if(touche == ESC) {
				pauseBoucle(mainwin, &touche, pause, &etatJeu, &etatPartie, &etatSauvegarde);
			}
            if(touche == 'i') {
            	invBoucle(mainwin, &touche, inventMenu, &(partie->joueur->inventaire),&(partie->minuteur),partie->joueur);
            }

			/*remet le compteur du mouvement des ennemis a 0 s'il depasse 40
			puis l'incremente*/
			if(partie->mvEnnemic>40){
				partie->mvEnnemic=0;
			}
			partie->mvEnnemic++;
			
			napms(1000 / IMAGES_PAR_SECONDE);
			chronos(&(partie->minuteur),&(partie->decr_minuteur));
			if(partie->minuteur <= 0){
				etatPartie = 0;
			}
            if(etatSauvegarde) {
                etatSauvegarde = 0;
                sauvegardeBoucle(mainwin, sauvegardeEntree, longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur, longueur, &touche);
                saveGame(partie, sauvegardeEntree->buffer);
            }
		}
		

		logMessage(INFO, "fin du programme");
		free(partie->carte);
		freeMenu(menu);
		werase(mainwin);
	}
		endwin();//ferme la fenetre
		moveLog();
		return 0;
}
