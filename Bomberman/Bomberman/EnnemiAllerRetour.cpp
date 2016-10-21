#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include<iostream>
#include "Niveau.h"
#include "EnnemiAllerRetour.h"


using namespace std;

extern Niveau niveau;

EnnemiAllerRetour::EnnemiAllerRetour(int x,int y,int direction, bool traverse) : Personnage(x, y)
{
	this->x = x;
	this->y = y;
	this->deplacement = direction;
	this->traverseMurDestructible = traverse;
}


EnnemiAllerRetour::~EnnemiAllerRetour()
{
}


void EnnemiAllerRetour::dessiner() {
	glBegin(GL_QUADS);
	glColor3d(0, 0, 0.501961);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1 + offsetX, y + 1 + offsetY);//top left
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1 + offsetX, y + offsetY);//bottom left	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x + offsetX, y + offsetY);//bottom right	
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x + offsetX, y + 1 + offsetY);	//top right	
	glEnd();
}


void EnnemiAllerRetour::Deplacer() {
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


void EnnemiAllerRetour::calculDeplacement() {
	
	 //on test si l'ennemi est dans la case.
	if (offsetX > -0.1 && offsetX < 0.1 && offsetY > -0.1 && offsetY < 0.1) {

		switch (deplacement) {	//1 : A gauche, 2 : A droite, 3 : En bas, 4 : En haut
		case 1:
			if (!niveau.caseLibre(y, x - 1) || (niveau.caseMurDestructible(y, x - 1) && !traverseMurDestructible))  deplacement = 2;
			else deplacement = 1;
			break;
		case 2:
			if (!niveau.caseLibre(y, x + 1) || (niveau.caseMurDestructible(y, x + 1) && !traverseMurDestructible)) deplacement = 1;
			else deplacement = 2;
			break;
		case 3:
			if (!niveau.caseLibre(y + 1, x) || (niveau.caseMurDestructible(y + 1, x) && !traverseMurDestructible)) deplacement = 4;
			else deplacement = 3;
			break;
		case 4:
			if (!niveau.caseLibre(y - 1, x) || (niveau.caseMurDestructible(y - 1, x) && !traverseMurDestructible)) deplacement = 3;
			else deplacement = 4;
			break;
		default:
			break;
		}

	}

	deplacement_precedent = deplacement; // on enregistre la valeur
	Deplacer(); // on se deplace
}

void EnnemiAllerRetour::deplacementGauche()
{
	if (offsetY < 0.35 && offsetY > -0.35) {
		if (niveau.caseLibre(this->y, this->x - 1)) {
			offsetX -= 0.1f;
			offsetY = 0;
			if (offsetX < -0.95) {
				x--;
				offsetX = 0;
			}
		}
		else {
			offsetY = 0;
			if (offsetX > 0.20) offsetX -= 0.1f;
			else offsetX = 0;
		}
	}

	direction = 1;
}

void EnnemiAllerRetour::deplacementDroite()
{
	if (offsetY < 0.35 && offsetY > -0.35) {
		if (niveau.caseLibre(this->y, this->x + 1)) {
			offsetX += 0.1f;
			offsetY = 0;
			if (offsetX > 0.95) {
				x++;
				offsetX = 0;
			}
		}
		else {
			offsetY = 0;
			if (offsetX < -0.20) offsetX += 0.1f;
			else offsetX = 0;
		}
	}

	direction = 2;
}

void EnnemiAllerRetour::deplacementHaut()
{
	if (offsetX < 0.35 && offsetX > -0.35) {
		if (niveau.caseLibre(this->y - 1, this->x) ) {
			offsetY -= 0.1f;
			offsetX = 0;
			if (offsetY < -0.95) {
				y--;
				offsetY = 0;
			}
		}
		else {
			offsetX = 0;
			if (offsetY > 0.20) offsetY -= 0.1f;
			else offsetY = 0;
		}
	}

	direction = 3;
}

void EnnemiAllerRetour::deplacementBas()
{
	if (offsetX < 0.35 && offsetX > -0.35) {
		if (niveau.caseLibre(this->y + 1, this->x) ) {
			offsetY += 0.1f;
			offsetX = 0;
			if (offsetY > 0.95) {
				y++;
				offsetY = 0;
			}
		}
		else {
			offsetX = 0;
			if (offsetY < -0.20) offsetY += 0.1f;
			else offsetY = 0;
		}
	}

	direction = 4;
}