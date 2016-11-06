#include "Bombe.h"
#include "Niveau.h"
#include <iostream>
#include "Bomberman.h"
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"
#include "Animation.h"

using namespace std; 

extern Niveau niveau;
extern Bomberman bomberman;
extern vector<Personnage*> ennemisTab;
extern vector<GLuint> texture;
extern int valueExplo;
extern bool spawn;

float coordExplo[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };

Bombe::Bombe()
{
}

Bombe::Bombe(int x, int y, int portee) {
	this->x = x;
	this->y = y;
	this->portee = portee;
	posee = false;
	explosion = false;
}

int Bombe::getX()
{
	return x;
}

int Bombe::getY()
{
	return y;
}

Bombe::~Bombe()
{
}

void Bombe::exploser() {
	//Centre de l'explosion  : 
	//Test si il y a des mort
	if (x == bomberman.getX() && y == bomberman.getY())	bomberman.setVivant(false);
	for (int i = 0; i < size(ennemisTab); i++) {
		if (ennemisTab[i]->getX() == x && ennemisTab[i]->getY() == y) {
			ennemisTab[i]->setVivant(false);
		}
	}

	//Test s'il on detruit un bonus 
	for (int k = 0; k < size(niveau.bonusTab); k++) {
		if (x == niveau.bonusTab[k].getX() && y == niveau.bonusTab[k].getY()) {
			niveau.bonusTab[k].setVisible(false);
			niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
		}
	}

	//Test s'il y a une autre bombe - au cas ou
	for (int k = 0; k < size(bomberman.bombes); k++) {
		if (x == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
			bomberman.bombes[k].explosion = true;
			bomberman.bombes[k].Timer = 12;
			bomberman.declancherExplosion(k);
		}
	}
	
	//Explosion vers le haut 
	explosionHaut();
	//Explosion vers le bas
	explosionBas();
	//Explosion vers la gauche
	explosionGauche();
	//Explosion vers la droite
	explosionDroite();

}

void Bombe::explosionHaut() {
	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibreBombe(y - i, x) && !arretExplosionHaut) { //En haut

			if (niveau.caseMurDestructible(y - i, x)) {
				niveau.modifierCase(y - i, x, '3');
				arretExplosionHaut = true;
			}
			else {
				nbCaseHaut++;
			}		

			//Test s'il on detruit un bonus 
			for (int k = 0; k < size(niveau.bonusTab); k++) {
				if (x == niveau.bonusTab[k].getX() && y - i == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
					niveau.bonusTab[k].setVisible(false);
					niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
				}
			}
			//Test s'il y a une autre bombe
			for (int k = 0; k < size(bomberman.bombes); k++) {
				if (x == bomberman.bombes[k].getX() && y - i == bomberman.bombes[k].getY()) {
					arretExplosionHaut = true;
				}
			}
		}
		else arretExplosionHaut = true;
	}

	if (niveau.caseLibreBombe(y - portee + 1, x) && !arretExplosionHaut) {

		if (!niveau.caseMurDestructible(y - portee + 1, x) && niveau.getCase(y - portee + 1, x) != '3') {
			//on affiche l'extremite de l'explosion si ce n'est pas un mur destructible
			afficherExtremHaut = true;
		}
		else {
			niveau.modifierCase(y - portee + 1, x, '3');
		}
		//Test s'il on detruit un bonus 
		for (int k = 0; k < size(niveau.bonusTab); k++) {
			if (x == niveau.bonusTab[k].getX() && y - portee + 1 == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
				niveau.bonusTab[k].setVisible(false);
				niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x == bomberman.bombes[k].getX() && y - portee + 1 == bomberman.bombes[k].getY()) {
				afficherExtremHaut = false;
			}
		}
	}
}

void Bombe::explosionBas() {
	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibreBombe(y + i, x) && !arretExplosionBas) { //En bas
			if (niveau.caseMurDestructible(y + i, x)) {
				niveau.modifierCase(y + i, x, '3');
				arretExplosionBas = true;
			}
			else {
				nbCaseBas++;
			}

			//Test s'il on detruit un bonus 
			for (int k = 0; k < size(niveau.bonusTab); k++) {
				if (x == niveau.bonusTab[k].getX() && y + i == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
					niveau.bonusTab[k].setVisible(false);
					niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
				}
			}

			//Test s'il y a une autre bombe
			for (int k = 0; k < size(bomberman.bombes); k++) {
				if (x == bomberman.bombes[k].getX() && y + i == bomberman.bombes[k].getY()) {
					arretExplosionBas = true;
				}
			}
		}
		else arretExplosionBas = true;
	}

	if (niveau.caseLibreBombe(y + portee - 1, x) && !arretExplosionBas) { //En bas
		if (!niveau.caseMurDestructible(y + portee - 1, x) && niveau.getCase(y + portee - 1, x) != '3') {
			afficherExtremBas = true;
		}
		else niveau.modifierCase(y + portee - 1, x, '3');

		//Test s'il on detruit un bonus 
		for (int k = 0; k < size(niveau.bonusTab); k++) {
			if (x == niveau.bonusTab[k].getX() && y + portee - 1 == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
				niveau.bonusTab[k].setVisible(false);
				niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
			}
		}
		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x == bomberman.bombes[k].getX() && y + portee - 1 == bomberman.bombes[k].getY()) {
				afficherExtremBas = false;
			}
		}
	}
}

void Bombe::explosionGauche() {
	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibreBombe(y, x - i) && !arretExplosionGauche) { //A gauche

			if (niveau.caseMurDestructible(y, x - i)) {
				niveau.modifierCase(y, x - i, '3');
				arretExplosionGauche = true;
			}
			else {
				nbCaseGauche++;
			}

			//Test s'il on detruit un bonus 
			for (int k = 0; k < size(niveau.bonusTab); k++) {
				if (x - i == niveau.bonusTab[k].getX() && y == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
					niveau.bonusTab[k].setVisible(false);
					niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
				}
			}

			//Test s'il y a une autre bombe
			for (int k = 0; k < size(bomberman.bombes); k++) {
				if (x - i == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY()) {
					arretExplosionGauche = true;
				}
			}
		}
		else arretExplosionGauche = true;

	}
	//extremité de l'explosion
	if (niveau.caseLibreBombe(y, x - portee + 1) && !arretExplosionGauche) { //A gauche
		if (!niveau.caseMurDestructible(y, x - portee + 1) && niveau.getCase(y, x - portee + 1) != '3') {
			afficherExtremGauche = true;
		}
		else niveau.modifierCase(y, x - portee + 1, '3');

		//Test s'il on detruit un bonus 
		for (int k = 0; k < size(niveau.bonusTab); k++) {
			if (x - portee + 1 == niveau.bonusTab[k].getX() && y == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
				niveau.bonusTab[k].setVisible(false);
				niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
			}
		}
		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x - portee + 1 == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY()) {
				afficherExtremGauche = false;
			}
		}

	}
}

void Bombe::explosionDroite() {
	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibreBombe(y, x + i) && !arretExplosionDroite) { //A droite

			if (niveau.caseMurDestructible(y, x + i)) {
				niveau.modifierCase(y, x + i, '3');
				arretExplosionDroite = true;
			}
			else {
				nbCaseDroite++;
			}
			//Test s'il on detruit un bonus 
			for (int k = 0; k < size(niveau.bonusTab); k++) {
				if (x + i == niveau.bonusTab[k].getX() && y == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
					niveau.bonusTab[k].setVisible(false);
					niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
				}
			}
			//Test s'il y a une autre bombe
			for (int k = 0; k < size(bomberman.bombes); k++) {
				if (x + i == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY()) {
					arretExplosionDroite = true;
				}
			}
		}
		else arretExplosionDroite = true;
	}

	if (niveau.caseLibreBombe(y, x + portee - 1) && !arretExplosionDroite) { //A droite
		if (!niveau.caseMurDestructible(y, x + portee - 1) && niveau.getCase(y, x + portee - 1) != '3') {
			afficherExtremDroite = true;
		}
		else niveau.modifierCase(y, x + portee - 1, '3');
		
		//Test s'il on detruit un bonus 
		for (int k = 0; k < size(niveau.bonusTab); k++) {
			if (x + portee - 1 == niveau.bonusTab[k].getX() && y == niveau.bonusTab[k].getY() && niveau.bonusTab[k].getVisible()) {
				niveau.bonusTab[k].setVisible(false);
				niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x + portee - 1 == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY()) {
				afficherExtremDroite = false;
			}
		}
	}
}

void Bombe::effacerExplosion() {
	//on remet les booleens a false
	 arretExplosionHaut = false;
	 arretExplosionBas = false;
	 arretExplosionGauche = false;
	 arretExplosionDroite = false;

	 nbCaseHaut = 0;
	 nbCaseBas = 0;
	 nbCaseGauche = 0;
	 nbCaseDroite = 0;

	 afficherExtremHaut = false;
	 afficherExtremBas = false;
	 afficherExtremGauche = false;
	 afficherExtremDroite = false;
}

void Bombe::dessinerExplosion() {
	// on efface la bombe
	if (spawn) {
		niveau.modifierCase(y, x, '4');
	}
	else if (!spawn) {
		niveau.modifierCase(y, x, '0');
	}

	//Centre de l'explosion
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.25f, coordExplo[6 - valueExplo]); glVertex2d(x + 1, y + 1);
	glTexCoord2f(0.25f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y);
	glTexCoord2f(0.0f, coordExplo[7 - valueExplo]); glVertex2d(x, y);
	glTexCoord2f(0.0f, coordExplo[6 - valueExplo]); glVertex2d(x, y + 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);


	dessinerExplosionHaut();
	dessinerExplosionBas();
	dessinerExplosionGauche();
	dessinerExplosionDroite();
}

void Bombe::dessinerExplosionHaut() {
	for (int i = 1; i < nbCaseHaut+1; i++) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.25f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y + 1 - i);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]);  glVertex2d(x + 1, y - i);
		glTexCoord2f(0.25f, coordExplo[6 - valueExplo]);  glVertex2d(x, y - i);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x, y + 1 - i);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//on laisse les tests dans cette fonction car on souhaite vérifier pendant toute la duree de l'explosion
		//Test si il y a des mort
		if (x == bomberman.getX() && y - i == bomberman.getY() && (bomberman.offsetX == 0)) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x && ennemisTab[k]->getY() == y - i) {
				ennemisTab[k]->setVivant(false);
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x == bomberman.bombes[k].getX() && y - i == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 12;
				bomberman.declancherExplosion(k);
			}
		}
	}
	
	if(afficherExtremHaut) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y + 1 - portee + 1);
		glTexCoord2f(0.75f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y - portee + 1);
		glTexCoord2f(0.75f, coordExplo[6 - valueExplo]); glVertex2d(x, y - portee + 1);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x, y + 1 - portee + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		
		//Test si il y a des mort
		if (x == bomberman.getX() && y - portee + 1 == bomberman.getY() && (bomberman.offsetX == 0)) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x && ennemisTab[k]->getY() == y - portee + 1) {
				ennemisTab[k]->setVivant(false);
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x == bomberman.bombes[k].getX() && y - portee + 1 == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 12;
				bomberman.declancherExplosion(k);
			}
		}
	}
}

void Bombe::dessinerExplosionBas() {

	for (int i = 1; i < nbCaseBas + 1; i++) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.25f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y + 1 + i);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]);  glVertex2d(x + 1, y + i);
		glTexCoord2f(0.25f, coordExplo[6 - valueExplo]);  glVertex2d(x, y + i);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x, y + 1 + i);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//Test si il y a des mort
		if (x == bomberman.getX() && y + i == bomberman.getY() && bomberman.offsetX == 0) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x && ennemisTab[k]->getY() == y + i) {
				ennemisTab[k]->setVivant(false);
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x == bomberman.bombes[k].getX() && y + i == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 12;
				bomberman.declancherExplosion(k);
			}
		}
	}
	
	if(afficherExtremBas){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.75f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y + 1 + portee - 1);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]); glVertex2d(x + 1, y + portee - 1);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x, y + portee - 1);
		glTexCoord2f(0.75f, coordExplo[6 - valueExplo]); glVertex2d(x, y + 1 + portee - 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);


		//Test si il y a des mort
		if (x == bomberman.getX() && y + portee - 1 == bomberman.getY() && bomberman.offsetX == 0) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x && ennemisTab[k]->getY() == y + portee - 1) {
				ennemisTab[k]->setVivant(false);
			}
		}


		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x == bomberman.bombes[k].getX() && y + portee - 1 == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 12;
				bomberman.declancherExplosion(k);
			}
		}
	}
}

void Bombe::dessinerExplosionGauche() {

	for (int i = 1; i < nbCaseGauche + 1; i++) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x + 1 - i, y + 1);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]); glVertex2d(x + 1 - i, y);
		glTexCoord2f(0.25f, coordExplo[7 - valueExplo]); glVertex2d(x - i, y);
		glTexCoord2f(0.25f, coordExplo[6 - valueExplo]); glVertex2d(x - i, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//Test si il y a des mort
		if ((x - i) == bomberman.getX() && y == bomberman.getY() && bomberman.offsetY == 0) bomberman.setVivant(false);
	
		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == (x - i) && ennemisTab[k]->getY() == y) {
				ennemisTab[k]->setVivant(false);
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x - i == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.declancherExplosion(k);
				bomberman.bombes[k].Timer = 12;
			}
		}
	}
		
	//extremité de l'explosion
	if (afficherExtremGauche) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]);  glVertex2d(x + 1 - portee + 1, y + 1);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]); glVertex2d(x + 1 - portee + 1, y);
		glTexCoord2f(0.75f, coordExplo[7 - valueExplo]); glVertex2d(x - portee + 1, y);
		glTexCoord2f(0.75f, coordExplo[6 - valueExplo]); glVertex2d(x - portee + 1, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//Test si il y a des mort
		if (x - portee + 1 == bomberman.getX() && y == bomberman.getY() && bomberman.offsetY == 0) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x - portee + 1 && ennemisTab[k]->getY() == y) {
				ennemisTab[k]->setVivant(false);
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x - portee + 1 == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 11;
				bomberman.declancherExplosion(k);
			}
		}
	}
}

void Bombe::dessinerExplosionDroite() {

	for (int i = 1; i < nbCaseDroite + 1; i++) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x + 1 + i, y + 1);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]); glVertex2d(x + 1 + i, y);
		glTexCoord2f(0.25f, coordExplo[7 - valueExplo]); glVertex2d(x + i, y);
		glTexCoord2f(0.25f, coordExplo[6 - valueExplo]); glVertex2d(x + i, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//Test si il y a des mort
		if (x + i == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x + i && ennemisTab[k]->getY() == y ) {
				ennemisTab[k]->setVivant(false);
			}
		}

		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x + i == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 12;
				bomberman.declancherExplosion(k);
			}
		}
	}

	if (afficherExtremDroite) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.75f, coordExplo[6 - valueExplo]); glVertex2d(x + 1 + portee - 1, y + 1);
		glTexCoord2f(0.75f, coordExplo[7 - valueExplo]); glVertex2d(x + 1 + portee - 1, y);
		glTexCoord2f(0.5f, coordExplo[7 - valueExplo]); glVertex2d(x + portee - 1, y);
		glTexCoord2f(0.5f, coordExplo[6 - valueExplo]); glVertex2d(x + portee - 1, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//Test si il y a des mort
		if (x + portee - 1 == bomberman.getX() && y == bomberman.getY() && bomberman.offsetY == 0) bomberman.setVivant(false);

		for (int k = 0; k < size(ennemisTab); k++) {
			if (ennemisTab[k]->getX() == x + portee - 1 && ennemisTab[k]->getY() == y) {
				ennemisTab[k]->setVivant(false);
			}
		}
		//Test s'il y a une autre bombe
		for (int k = 0; k < size(bomberman.bombes); k++) {
			if (x + portee - 1 == bomberman.bombes[k].getX() && y == bomberman.bombes[k].getY() && !bomberman.bombes[k].explosion) {
				bomberman.bombes[k].explosion = true;
				bomberman.bombes[k].Timer = 12;
				bomberman.declancherExplosion(k);
			}
		}
	} 
}