#include <vector>
#include <iostream>
#include <chrono>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Bomberman.h"
#include "Niveau.h"
#include "Animation.h"
#include "Personnage.h"
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"

using namespace std;

float coordBomb[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };
int rotation;

extern int valueBomberman;
extern int direction;

extern vector<GLuint> texture;
extern Niveau niveau;

//pour gerer les collisions :
extern EnnemiAleatoire ennemi1;
extern EnnemiAllerRetour ennemi2;
extern EnnemiAllerRetour ennemi3;


Bomberman::Bomberman(int xDepart, int  yDepart) : Personnage(x, y)
{
	this->x = xDepart;
	this->y = yDepart;
	this->vivant = true;
	this->vitesseDeplacement = 0.10f;
}


Bomberman::~Bomberman()
{
}
int Bomberman::getNbBombe()
{
	return nb_bombes;
}
int Bomberman::getPorteeBombe()
{
	return portee_bombe;
}
//Setter
void Bomberman::setNbBombe(int nb) {
	this->nb_bombes = nb;
}

void Bomberman::setPorteeBombe(int portee)
{
	this->portee_bombe = portee;
}


void Bomberman::lancerBombe() {

	if (nb_bombes > 0) {
		niveau.modifierCase(y, x, '8');

		Bombe bombe = Bombe(x, y, portee_bombe);
		bombe.posee = true;

		bombes.push_back(bombe);
		nb_bombes--;
	}
}

void Bomberman::declancherExplosion(int nb) {
	bombes[nb].exploser();
	setNbBombe(nb_bombes + 1);
}

void Bomberman::eraseExplosion(int nb) {
	bombes[nb].effacerExplosion();
	bombes.erase(bombes.begin() + nb);
}

void Bomberman::collisionEnnemi() { // test si l'on est sur la meme case qu'un ennemi

	if ((ennemi1.getX() == x && ennemi1.getY() == y) || (ennemi2.getX() == x && ennemi2.getY() == y) || (ennemi3.getX() == x && ennemi3.getY() == y)) {
		vivant = false;
	}
}

void Bomberman::ramasserBonus() {
	
	for (int i = 0; i < size(niveau.bonusTab); i++) {
		//on test si l'on est sur la case d'un bonus et qu'il est actif
		if (x == niveau.bonusTab[i].getX() && y == niveau.bonusTab[i].getY() && niveau.bonusTab[i].getVisible()) {
			niveau.bonusTab[i].ramasser();
		}
	}
}


void Bomberman::dessiner() {
	switch (direction)
	{
	case(1):
		rotation = 2;
		break;
	case(2):
		rotation = 6;
		break;
	case(3):
		rotation = 4;
		break;
	case(4):
		rotation = 0;
		break;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(coordBomb[0 + valueBomberman], coordBomb[6 - rotation]); glVertex2d(x + offsetX + 1, y + offsetY + 1);
	glTexCoord2f(coordBomb[1 + valueBomberman], coordBomb[6 - rotation]); glVertex2d(x + offsetX, y + offsetY + 1);
	glTexCoord2f(coordBomb[1 + valueBomberman], coordBomb[8 - rotation]); glVertex2d(x + offsetX, y + offsetY - 0.5);
	glTexCoord2f(coordBomb[0 + valueBomberman], coordBomb[8 - rotation]); glVertex2d(x + offsetX + 1, y + offsetY - 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}