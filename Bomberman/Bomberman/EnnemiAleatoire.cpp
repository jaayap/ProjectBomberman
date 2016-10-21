#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include<iostream>
#include "EnnemiAleatoire.h"
#include "Niveau.h"

using namespace std;

extern Niveau niveau;

EnnemiAleatoire::EnnemiAleatoire(int xDepart, int yDepart) : Personnage(x, y)
{
	this->x = xDepart;
	this->y = yDepart;
}


EnnemiAleatoire::~EnnemiAleatoire()
{
}

void EnnemiAleatoire::dessiner() {
	glBegin(GL_QUADS);
	glColor3d(0.580392, 0, 0.827451);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1 + offsetX, y + 1 + offsetY);//top left
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1 + offsetX, y + offsetY);//bottom left	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x + offsetX, y + offsetY);//bottom right	
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x + offsetX, y + 1 + offsetY);	//top right	
	glEnd();
}


void EnnemiAleatoire::Deplacer() {
	if (vivant) {
	
		switch (deplacement) {	//1 : A gauche, 2 : A droite, 3 : En bas, 4 : En haut
			case 1:
				deplacementGauche();
				break;
			case 2:
				deplacementDroite();
				break;
			case 3:
				deplacementBas();
				break;
			case 4:
				deplacementHaut();
				break;
			default:
				break;
		}
	}

	glutPostRedisplay();
}


void EnnemiAleatoire::calculDeplacement() {//1 : A gauche, 2 : A droite, 3 : En bas, 4 : En haut
 
	//on test si l'ennemi est dans la case.
	if (offsetX > -0.1 && offsetX < 0.1 && offsetY > -0.1 && offsetY < 0.1) {

		//GAUCHE
		if (deplacement_precedent == 1) {

			if (!niveau.caseLibre(y, x - 1) || niveau.caseMurDestructible(y, x - 1)) { //Mur devant (gauche)

				if (!niveau.caseLibre(y - 1, x) || niveau.caseMurDestructible(y -1, x)) { // Mur en haut
					if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x )) {//Mur en bas
						deplacement = 2; // Retour en arriere
					}
					else deplacement = 3;
				}
				else if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x )) deplacement = 4; //Mur en bas
				else deplacement = rand() % (5 - 3) + 3; //nombre aleatoire entre 3 et 4
			}
			else if (!niveau.caseLibre(y - 1, x) || niveau.caseMurDestructible(y - 1, x )) { // Mur en haut
				if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x)) deplacement = deplacement_precedent; //et Mur en bas
				else {
					deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
					if (deplacement == 2) { // 2 : on veut aller en bas -> 3
						deplacement = 3;
					}
				}
			}
			else if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x)) { // Mur en bas
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
				if (deplacement == 2) { // 2 : on veut aller en haut -> 4
					deplacement = 4;
				}
			}
			else {
				do {
					deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
				} while (deplacement == 2);//Evite le retour en arriere
			}

		}
		//DROITE
		else if (deplacement_precedent == 2) { // Droite	
			if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) { //Mur devant (droite)
				if (!niveau.caseLibre(y - 1, x) || niveau.caseMurDestructible(y - 1, x)) { // Mur en haut
					if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x )) deplacement = 1; //ET mur en bas
					else deplacement = 3; //retour en arriere
				}
				else if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x)) deplacement = 4; //Mur en bas
				else deplacement = rand() % (5 - 3) + 3; //nombre aleatoire entre 3 et 4
			}
			else if (!niveau.caseLibre(y - 1, x) || niveau.caseMurDestructible(y-1, x)) { // Mur en haut
				if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x)) deplacement = deplacement_precedent; //et Mur en bas
				else {
					deplacement = rand() % (4 - 2) + 2; // nombre aleatoire entre 2 et 3
				}
			}
			else if (!niveau.caseLibre(y + 1, x) || niveau.caseMurDestructible(y + 1, x)) { // Mur en bas
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
				if (deplacement == 1) { // 2 : on veut aller en haut -> 4
					deplacement = 4;
				}
			}
			else {
				do {
					deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
				} while (deplacement == 1);
			}
		}
		//BAS
		else if (deplacement_precedent == 3) {
		
			if (!niveau.caseLibre(y + 1, x)  || niveau.caseMurDestructible(y+1,x)) { //Mur devant (bas)
					if (!niveau.caseLibre(y, x - 1) || niveau.caseMurDestructible(y, x - 1)) {// Mur a gauche
					if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) {
						deplacement = 4; // Et mur a droite : demi-tour
					}
					else deplacement = 2; 
				}
				else if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) deplacement = 1; //Mur a droite
				else deplacement = rand() % (2) + 1; //nombre aleatoire entre 1 et 2
			}
			else if (!niveau.caseLibre(y, x - 1) || niveau.caseMurDestructible(y, x - 1)) { // Mur a gauche
				if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) deplacement = deplacement_precedent; //et Mur a droite
				else {
					deplacement = rand() % (4 - 2) + 2; // nombre aleatoire entre 2 et 3
				}
			}
			else if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) { // Mur a droite
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
				if (deplacement == 2) { // 2 : on veut aller en bas -> 3
					deplacement = 3;
				}
			}
			else {
				do {
					deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
				} while (deplacement == 4);
			}
		}
		//HAUT
		else if (deplacement_precedent == 4) {
			if (!niveau.caseLibre(y - 1, x) || niveau.caseMurDestructible(y - 1, x )) { //Mur devant (haut)
				if (!niveau.caseLibre(y, x - 1 || niveau.caseMurDestructible(y, x - 1))) {// Mur a gauche
					if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) deplacement = 3;
					else deplacement = 2; 
				}
				else if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) deplacement = 1; //Mur a droite
				else deplacement = rand() % (2) + 1; //nombre aleatoire entre 1 et 2
			}
			else if (!niveau.caseLibre(y, x - 1) || niveau.caseMurDestructible(y, x - 1)) { // Mur a gauche
				if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) deplacement = deplacement_precedent; //et Mur a droite
				else {
					deplacement = rand() % (2) + 1; // nombre aleatoire entre 2 et 4
					if (deplacement == 1) { deplacement = 4; }
				}
			}
			else if (!niveau.caseLibre(y, x + 1) || niveau.caseMurDestructible(y, x + 1)) { // Mur a droite
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 4
				if (deplacement == 2) { // 2 : on veut aller en haut -> 4
					deplacement = 4;
				}
			}
			else {
				do {
					deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
				} while (deplacement == 3);
			}
		}
	}
	else deplacement = deplacement_precedent;

	deplacement_precedent = deplacement; // on enregistre la valeur
	Deplacer(); // on se deplace
}