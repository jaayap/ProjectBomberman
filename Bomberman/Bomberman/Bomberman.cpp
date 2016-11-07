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
float vitesseDeplacement;

int rotation;
int tailleTab;

bool GameOver = false;
bool die = false;
bool life = true;
bool spawn = false;

extern int valueBomberman;
extern int spriteBomberdeath;
extern int direction;
extern int vie;
extern int maxMur;
extern int nbrMur;

extern float valueBomberdeath;
extern float numeroNiveau;

extern bool victoire;
extern bool PlacerBonus;
extern bool afficherMenu;

extern vector<GLuint> texture;
extern Niveau niveau;

extern Bomberman bomberman;

extern EnnemiAleatoire ennemi1;
extern EnnemiAllerRetour ennemi2;
extern EnnemiAllerRetour ennemi3;

//pour gerer les collisions :
extern vector<Personnage*> ennemisTab;


void AnimDeath(int z) {
	die = true;
}

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
	bool dejaBombe = false;

	if (nb_bombes > 0) {
		for (int i = 0; i < size(bombes); i++) {
			if (bombes[i].getX() == x && bombes[i].getY() == y)
				dejaBombe = true;
		}
		if (!dejaBombe) {
			if (niveau.getCase(y, x) == '4') {
				spawn = true;
			}
			else if (niveau.getCase(y, x) == '0') {
				spawn = false;
			}
			niveau.modifierCase(y, x, '8');

			Bombe bombe = Bombe(x, y, portee_bombe);
			bombe.posee = true;

			bombes.push_back(bombe);
			nb_bombes--;
		}
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

	if (size(ennemisTab) > 1) {
		for (int i = 0; i < size(ennemisTab); i++) {
			if (ennemisTab[i]->getX() == x && ennemisTab[i]->getY() == y && ennemisTab[i]->vivant) {
				vivant = false;
			}
		}
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

// Retour à la case départ après la perte d'une vie
void Bomberman::retour() {
	x = 2;
	y = 1;
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

	if (victoire && x == 8 && y == 6) {
		numeroNiveau = 0.25f;
		retour();
		maxMur = 0;
		victoire = false;
	}

	if (vivant == false && life) {
		if (vie == 0 && !GameOver && life && !die) {
			GameOver = true;
			life = false;
			nb_bombes = 1;
			portee_bombe = 3;
			spriteBomberdeath = 0;
			for (int k = 0; k < size(niveau.bonusTab); k++) {
				niveau.bonusTab[k].setVisible(false);
				niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise	
			}
			vivant = true;
			glutTimerFunc(600, AnimDeath, 0);
		}
		else if (life && !die && !afficherMenu) {
			life = false;
			nb_bombes = 1;
			portee_bombe = 3;
			spriteBomberdeath = 0;
			for (int k = 0; k < size(niveau.bonusTab); k++) {
				niveau.bonusTab[k].setVisible(false);
				niveau.bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
			}
			vivant = true;
			glutTimerFunc(600, AnimDeath, 0);
		}
	}
	

	if (life) {
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
	else if (!life) {
		vitesseDeplacement = 0.0f;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(valueBomberdeath, coordBomb[0]); glVertex2d(x + offsetX + 1, y + offsetY + 1);
		glTexCoord2f(valueBomberdeath + 0.16666667, coordBomb[0]); glVertex2d(x + offsetX, y + offsetY + 1);
		glTexCoord2f(valueBomberdeath + 0.16666667, coordBomb[8]); glVertex2d(x + offsetX, y + offsetY - 0.5);
		glTexCoord2f(valueBomberdeath, coordBomb[8]); glVertex2d(x + offsetX + 1, y + offsetY - 0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}

	if (die) {
		if (GameOver && vie == 0) {
			vie = 3;
			retour();
			// Respawn ennemis
			tailleTab = size(ennemisTab);
			if (tailleTab > 1) {
				for (int i = 1; i < tailleTab; i++) {
					ennemisTab[i]->vivant = false;
				}
				ennemisTab.erase(ennemisTab.begin() + 1, ennemisTab.begin() + tailleTab);
				ennemisTab.push_back(&ennemi1);
				ennemisTab.push_back(&ennemi2);
				ennemisTab.push_back(&ennemi3);
				ennemi1.retour();
				ennemi2.retour();
				ennemi3.retour();
				for (int i = 1; i < size(ennemisTab); i++) {
					ennemisTab[i]->vivant = true;
					//ennemisTab[i].retour();
				}
			}
			maxMur = 0;
			vitesseDeplacement = 0.10f;
			bomberman.vivant = true;
			life = true;
			die = false;
			// Forcer les bombes à se détruire
			for (int i = 0; i < size(bomberman.bombes); i++) {
				bomberman.bombes[i].effacerBombes();
				bomberman.eraseExplosion(i);
				//on efface les murs détruits
				for (int i = 0; i < 13; i++) {
					for (int j = 0; j < 17; j++) {
						if (niveau.getCase(i, j) == '3') {
							niveau.modifierCase(i, j, '0');
						}
					}
				}
			}
			afficherMenu = true;
			return;
		}
		retour();
		vie--;
		// Respawn ennemis
		tailleTab = size(ennemisTab);
		if (tailleTab > 1) {
			for (int i = 1; i < tailleTab; i++) {
				ennemisTab[i]->vivant = false;
			}
			ennemisTab.erase(ennemisTab.begin() + 1, ennemisTab.begin() + tailleTab);
			ennemisTab.push_back(&ennemi1);
			ennemisTab.push_back(&ennemi2);
			ennemisTab.push_back(&ennemi3);
			ennemi1.retour();
			ennemi2.retour();
			ennemi3.retour();
			for (int i = 1; i < size(ennemisTab); i++) {
				ennemisTab[i]->vivant = true;
			}
		}
		maxMur = 0;
		vitesseDeplacement = 0.10f;
		bomberman.vivant = true;
		life = true;
		die = false;
		// Forcer les bombes à se détruire
		for (int i = 0; i < size(bomberman.bombes); i++) {
			bomberman.bombes[i].effacerBombes();
			bomberman.eraseExplosion(i);
			//on efface les murs détruits
			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 17; j++) {
					if (niveau.getCase(i, j) == '3') {
						niveau.modifierCase(i, j, '0');
					}
				}
			}
		}
		return;
	}
	
}