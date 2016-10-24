#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <iostream>
#include "Niveau.h"
#include "EnnemiAllerRetour.h"
#include "Animation.h"
#include <vector>

using namespace std;

float coordEnnemi[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };
int rotationEnnemi1;

extern int valueEnnemi1;

extern Niveau niveau;
extern vector<GLuint> texture;

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
	switch (direction)
	{
	case(1):
		rotationEnnemi1 = 2;
		break;
	case(2):
		rotationEnnemi1 = 6;
		break;
	case(3):
		rotationEnnemi1 = 0;
		break;
	case(4):
		rotationEnnemi1 = 4;
		break;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(coordEnnemi[2 + valueEnnemi1], coordEnnemi[6 - rotationEnnemi1]); glVertex2d(x + 1 + offsetX, y + 1 + offsetY);
	glTexCoord2f(coordEnnemi[2 + valueEnnemi1], coordEnnemi[8 - rotationEnnemi1]); glVertex2d(x + 1 + offsetX, y + offsetY - 0.5);
	glTexCoord2f(coordEnnemi[0 + valueEnnemi1], coordEnnemi[8 - rotationEnnemi1]); glVertex2d(x + offsetX, y + offsetY - 0.5);
	glTexCoord2f(coordEnnemi[0 + valueEnnemi1], coordEnnemi[6 - rotationEnnemi1]); glVertex2d(x + offsetX, y + 1 + offsetY);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
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