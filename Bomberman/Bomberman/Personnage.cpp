#include <string>
#include <iostream>
#include "Personnage.h"
#include "Niveau.h"

using namespace std;

extern Niveau niveau;

Personnage::Personnage(int x, int y)
{
	this->x = x;
	this->y = y;
	vivant = true;
}


Personnage::~Personnage()
{
}
//Getters
int Personnage::getX() {
	return x;
}
int Personnage::getY() {
	return y;
}
bool Personnage::getVivant() {
	return vivant;
}

int Personnage::getVitesseDeplacement() {
	return vitesseDeplacement;
}
//Setter
void Personnage::setVivant(bool vivant) {
	this->vivant = vivant;
}
void Personnage::setVitesseDeplacement(int vitesse) {
	this->vitesseDeplacement = vitesse;
}

void Personnage::deplacementGauche()
{
	if (offsetY < 0.35 && offsetY > -0.35) {
		if (niveau.caseLibre(this->y, this->x - 1) && !niveau.caseMurDestructible(this->y, this->x-1)) {	
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

void Personnage::deplacementDroite()
{
	if (offsetY < 0.35 && offsetY > -0.35) {
		if (niveau.caseLibre(this->y, this->x + 1) && !niveau.caseMurDestructible(this->y, this->x + 1)) {
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

void Personnage::deplacementHaut()
{
	if (offsetX < 0.35 && offsetX > -0.35) {
		if (niveau.caseLibre(this->y - 1, this->x) && !niveau.caseMurDestructible(this->y - 1, this->x)) {
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

void Personnage::deplacementBas()
{
	if (offsetX < 0.35 && offsetX > -0.35) {
		if (niveau.caseLibre(this->y + 1, this->x) && !niveau.caseMurDestructible(this->y +1, this->x)) {
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