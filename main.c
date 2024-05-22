#include "CosmicYonder.h"
#include "logger.h"

#include "ui/ui.h"
#include <ncurses.h>

int main()
{
	char logBuffer[255];

	setlocale(LC_ALL,""); // nécessaire pour UTF-8

   	createLog();
   	logMessage(INFO, "init ncurses");
	int graine; //init rand
	initscr(); //initialise l'ecran
	noecho(); //empeche d'afficher les caracteres saisis dans le terminal
	cbreak(); //permet de quitter le programme avec Ctrl+c
	curs_set(0); //rend le curseur invisible
	initCouleur();
    int etatJeu = 1; // permet de quitter le jeu si besoin
	int hauteur, longueur;
	int nsalles = MAX_SALLES; //bug constante a regler
	int salles_existantes = 0; //compteur de salles existantes
	int objets_speciaux_apparus = 0; //Compteur des objets à récupérer pour gagner apparus
	int portesNonOuvertes = 0; //Compte les portes non ouvertes sur la carte
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
            break;
        case 1:

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
    // init graine
    graine = creation_graine(graineEntree);
    srand(graine);
    //init carte
    Salle** carte;
    carte = malloc(MAX_SALLES * sizeof(Salle));
    if(carte == NULL) {
    	logMessage(CRITICAL, "erreur malloc portes salle");
    	exit(2);
    }

    //creation de la premiere salle
	carte[0] = creerSalleProced(longueur/2, hauteur/2, 4, -1,mainwin, &nsalles,&objets_speciaux_apparus,portesNonOuvertes);
	salles_existantes++;
	
	//init joueur
    Joueur joueur;
    initJoueur(&joueur);
    joueur.x = carte[0]->x + carte[0]->longueur/2;
    joueur.y = carte[0]->y + carte[0]->hauteur/2;
	joueur.nom = "Test";
	HUD * hud = hudJeu(0, hauteur - hauteur/6, hauteur / 6, longueur, &joueur);


    //init ennemi
    Ennemi ennemi = initEnnemi(5,5,10,10,10);

	mvwaddch(mainwin,joueur.y, joueur.x, 'o'); // positionne le curseur au centre de l ecran
	//pour l instant, j ai represente le joueur avec le caractere 'o' pour tester le programme

	touche = wgetch(mainwin);//recupere touche pressee

    logMessage(INFO, "fin init");
	while(etatJeu){ // BOUCLE DU JEU
		//boucle qui parcourt toutes les salles existantes
		for(int j=0;j<salles_existantes;j++){ 
			//boucle qui parcourt toutes les portes de la salle
			for(int k=0; k<carte[j]->nportes;k++){
				/*conditions servent a creer une salle quand le joueur passe devant une porte, 
				en fonction de la position de la porte par rapport au joueur
				verifie parmi le tableau de salles si une porte se trouve a cote du joueur et cree une salle si c'est le cas*/
				if(carte[j]->portes[k].ouvert==0){
					//porte en haut
					if(carte[j]->portes[k].x+carte[j]->x==joueur.x && carte[j]->portes[k].y+carte[j]->y==joueur.y-1){ 
						if(carte[salles_existantes] != NULL) {  
							libereSalle(carte[salles_existantes]);
						}
						carte[salles_existantes] = creerSalleProced(joueur.x, joueur.y,4,BAS,mainwin, &nsalles, &objets_speciaux_apparus, portesNonOuvertes);
						ouvrirPorte(carte,j,salles_existantes, k, BAS);
						dessineSalle(mainwin, carte[salles_existantes]);
						salles_existantes++;
						portesNonOuvertes--;			
					}
					//porte en bas
					else if(carte[j]->portes[k].x+carte[j]->x==joueur.x && carte[j]->portes[k].y+carte[j]->y==joueur.y+1){ 
						if(carte[salles_existantes] != NULL) {
							libereSalle(carte[salles_existantes]);
						}
						carte[salles_existantes] = creerSalleProced(joueur.x, joueur.y,4,HAUT,mainwin,&nsalles,&objets_speciaux_apparus, portesNonOuvertes);
						ouvrirPorte(carte,j,salles_existantes, k, HAUT);
						dessineSalle(mainwin, carte[salles_existantes]);
						salles_existantes++;
						portesNonOuvertes--;	
					}
					//porte a gauche
					else if(carte[j]->portes[k].x+carte[j]->x==joueur.x-1 && carte[j]->portes[k].y+carte[j]->y==joueur.y){ 
						if(carte[salles_existantes] != NULL) {
							libereSalle(carte[salles_existantes]);
						}
						carte[salles_existantes] = creerSalleProced(joueur.x, joueur.y,4,DROITE,mainwin,&nsalles,&objets_speciaux_apparus, portesNonOuvertes);
						ouvrirPorte(carte,j,salles_existantes, k, DROITE);
						dessineSalle(mainwin, carte[salles_existantes]);
						salles_existantes++;
						portesNonOuvertes--;
					}
					//porte a droite
					else if(carte[j]->portes[k].x+carte[j]->x==joueur.x+1 && carte[j]->portes[k].y+carte[j]->y==joueur.y){ 
						if(carte[salles_existantes] != NULL) {
							libereSalle(carte[salles_existantes]);
						}
						carte[salles_existantes] = creerSalleProced(joueur.x, joueur.y,4,GAUCHE,mainwin,&nsalles,&objets_speciaux_apparus, portesNonOuvertes);
						ouvrirPorte(carte,j,salles_existantes, k, GAUCHE);
						dessineSalle(mainwin, carte[salles_existantes]);	
						salles_existantes++;
					}

						
				}	
			}
		}
		portesNonOuvertes = compteurPortesNonOuvertes(carte, salles_existantes);
		interactions(touche, &joueur,carte, salles_existantes, mainwin);
		//ennemimv(&ennemi,carte[0],&joueur,mainwin);
		werase(mainwin);
		dessineSalles(mainwin, carte, salles_existantes);
		//afficheEnnemi(&ennemi, mainwin);
		mvwaddch(mainwin,joueur.y,joueur.x, 'o'); //deplace le joueur a la nouvelle position
		renduHUD(mainwin, hud);
		wrefresh(mainwin);
		touche = wgetch(mainwin);
        if(touche == ESC) {
            pauseBoucle(mainwin, &touche, pause, &etatJeu);
        }
        napms(1000 / FRAMES_PER_SECOND);
    }

    logMessage(INFO, "fin du programme");
    free(carte);
    freeMenu(menu);

	endwin();//ferme la fenetre
    moveLog();
	return 0;
}
