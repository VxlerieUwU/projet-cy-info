#include "CosmicYonder.h"
#include "logger.h"

#include "ui/ui.h"
#include <ncurses.h>

Partie * creerPartie() {
	Partie * partie = NULL;
	partie = malloc(sizeof(Partie));
	if(partie == NULL) {
		logMessage(CRITICAL, "erreur malloc partie");
		exit(1);
	}
	partie->joueur = malloc(sizeof(Joueur));
	if(partie->joueur == NULL) {
		logMessage(CRITICAL, "erreur malloc joueur");
		exit(1);
	}
	partie->carte = malloc(MAX_SALLES * sizeof(Salle));
	if(partie->carte == NULL) {
		logMessage(CRITICAL, "erreur malloc carte");
		exit(1);
	}
	partie->salles_existantes = 0; 	//compteur de salles existantes
	partie->objets_speciaux_apparus = 0;  //Compteur des objets à récupérer pour gagner apparus
	partie->portesNonOuvertes = 0;//Compte les portes non ouvertes sur la carte
	return partie;
}

int main()
{
	char logBuffer[255];

	setlocale(LC_ALL,""); // nécessaire pour UTF-8

   	createLog();
   	logMessage(INFO, "init ncurses");
	initscr(); //initialise l'ecran
	noecho(); //empeche d'afficher les caracteres saisis dans le terminal
	cbreak(); //permet de quitter le programme avec Ctrl+c
	curs_set(0); //rend le curseur invisible
	initCouleur();
    int etatJeu = 1; // permet de quitter le jeu si besoin
	int hauteur, longueur;
	int nsalles = MAX_SALLES; //bug constante a regler
	Partie * partie = creerPartie();

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
	// initialisation des interfaces graphiques
	Menu * menu = cosmicMenu(hauteur, longueur); //affiche le menu
    MiniMenu * parametres = options(longueur / 2, hauteur / 2, hauteur / 2, longueur / 2);
    MiniMenu * pause = pauseMenu(longueur / 2, hauteur / 2, hauteur / 2, longueur / 2);
    EntreeTexte * graineEntree = graineMenu(longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);

	renduFenetreMenu(mainwin, *menu, hauteur, longueur);
	int touche = -1;

	while(touche != ESC && menu->selEtat == 0) {
		touche = wgetch(mainwin);
		renduBoutons(mainwin, menu->boutons, menu->selecteur, menu->nbBoutons);
		entreeMenu(menu, touche);
		wrefresh(mainwin);
    }


	switch(menu->selecteur) {
        case 0:
            wclear(mainwin);
            touche = -1;
            while(graineEntree->valide == 0) {
                touche = wgetch(mainwin);
                renduFenetreEntree(mainwin, graineEntree, longueur / 2 - longueur/8, hauteur / 2 - hauteur / 8, hauteur / 3, longueur / 3);
                entreeTexte(graineEntree, touche);
                wrefresh(mainwin);
                napms(1000 / FRAMES_PER_SECOND);
            }
            wclear(mainwin);
			// init graine
			partie->graine = creation_graine(graineEntree);
			srand(partie->graine);
			//init partie->carte

			//creation de la premiere salle
			partie->carte[0] = creerSalleProced(longueur/2, hauteur/2, 4, -1,mainwin, &nsalles,&partie->objets_speciaux_apparus,partie->portesNonOuvertes);
			partie->salles_existantes++;

			//init joueur
			initJoueur(partie->joueur);
			partie->joueur->x = partie->carte[0]->x + partie->carte[0]->longueur/2;
			partie->joueur->y = partie->carte[0]->y + partie->carte[0]->hauteur/2;
			partie->joueur->nom = "Test";
            break;
        case 1:
        	partie = loadGame();
			wclear(mainwin);


            break;
        case 2:
            wclear(mainwin);
            while(parametres->curseur !=3) {
                renduFenetreOptions(mainwin, *parametres);
                touche = wgetch(mainwin);
                entreeMessage(parametres, touche);
                wrefresh(mainwin);
                napms(1000 / FRAMES_PER_SECOND);

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

	HUD * hud = hudJeu(0, hauteur - hauteur/6, hauteur / 6, longueur, partie->joueur);
	Texte * resTxt = respawnTexte(longueur/2 - longueur/5, hauteur/2 - hauteur/5, longueur);

    //init ennemi
    Ennemi ennemi = initEnnemi(5,5,10,10,10);

	mvwaddch(mainwin,partie->joueur->y, partie->joueur->x, 'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	touche = wgetch(mainwin);//recupere touche pressee

    logMessage(INFO, "fin init");
	while(etatJeu){ // BOUCLE DU JEU
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
						partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,BAS,mainwin, &nsalles, &partie->objets_speciaux_apparus, partie->portesNonOuvertes);
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
						partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,HAUT,mainwin,&nsalles,&partie->objets_speciaux_apparus, partie->portesNonOuvertes);
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
						partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,DROITE,mainwin,&nsalles,&partie->objets_speciaux_apparus, partie->portesNonOuvertes);
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
						partie->carte[partie->salles_existantes] = creerSalleProced(partie->joueur->x, partie->joueur->y,4,GAUCHE,mainwin,&nsalles,&partie->objets_speciaux_apparus, partie->portesNonOuvertes);
						ouvrirPorte(partie->carte,j,partie->salles_existantes, k, GAUCHE);
						dessineSalle(mainwin, partie->carte[partie->salles_existantes]);
						partie->salles_existantes++;
					}


				}
			}
		}
		partie->portesNonOuvertes = compteurPortesNonOuvertes(partie->carte, partie->salles_existantes);
		interactions(touche, partie->joueur,partie->carte, partie->salles_existantes, mainwin);
		for(int i=0; i<partie->salles_existantes; i++){
			if(partie->carte[i]->ennemi!=NULL){
				ennemipos(partie->carte[i]->ennemi,partie->carte[i]);
				if(mvEnnemic>40){
					ennemimv(partie->carte[i]->ennemi,partie->carte[i],partie->joueur,mainwin);
				}
			}
		}	
		werase(mainwin);
		dessineSalles(mainwin, partie->carte, partie->salles_existantes);
		for(int i=0; i<partie->salles_existantes; i++){
			if(partie->carte[i]->ennemi!=NULL){
				afficheEnnemi(partie->carte[i]->ennemi, mainwin);
			}
		}	
    mvwaddch(mainwin,partie->joueur->y,partie->joueur->x, 'o'); //deplace le joueur a la nouvelle position
		renduHUD(mainwin, hud);

		wrefresh(mainwin);
		touche = wgetch(mainwin);
        if(touche == ESC) {
            pauseBoucle(mainwin, &touche, pause, &etatJeu);
        }
       if(mvEnnemic>40){
        	mvEnnemic=0;
        }
        mvEnnemic++;
        napms(1000 / FRAMES_PER_SECOND);
    }

	saveGame(*partie);
    logMessage(INFO, "fin du programme");
    free(partie->carte);
    freeMenu(menu);

	endwin();//ferme la fenetre
    moveLog();
	return 0;
}
