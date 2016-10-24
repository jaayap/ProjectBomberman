#include "Bombe.h"
#include "Niveau.h"
#include <iostream>
#include "Bomberman.h"
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"

using namespace std; 

extern Niveau niveau;
extern Bomberman bomberman;
extern EnnemiAleatoire ennemi1;
extern EnnemiAllerRetour ennemi2;
extern EnnemiAllerRetour ennemi3;
extern vector<GLuint> texture;

bool arretExplosionHaut = false;
bool arretExplosionBas = false;
bool arretExplosionGauche = false;
bool arretExplosionDroite = false;

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

Bombe::~Bombe()
{
}


void Bombe::effacerExplosion() {
	//on remet les booleens a false
	 arretExplosionHaut = false;
	 arretExplosionBas = false;
	 arretExplosionGauche = false;
	 arretExplosionDroite = false;
}

void Bombe::dessinerExplosion() {


	// on efface la bombe
	niveau.modifierCase(y, x, '0');

	//Centre de l'explosion
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.25f, 0.75f); glVertex2d(x + 1, y + 1);
	glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y);
	glTexCoord2f(0.0f, 0.875f); glVertex2d(x, y);
	glTexCoord2f(0.0f, 0.75f); glVertex2d(x, y + 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	dessinerExplosionHaut();
	dessinerExplosionBas();
	dessinerExplosionGauche();
	dessinerExplosionDroite();
}

void Bombe::dessinerExplosionHaut() {
	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y - i, x)) { //En haut

			if (niveau.caseMurDestructible(y - i, x)) {
				niveau.modifierCase(y - i, x, '3');
				arretExplosionHaut = true;
			}
			else if (!arretExplosionHaut ){
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y + 1 - i);
				glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y - i);
				glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y - i);
				glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 1 - i);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			}

			//Test si il y a des mort
			if (x == bomberman.getX() && y - i == bomberman.getY()) bomberman.setVivant(false);
			if (x == ennemi1.getX() && y - i == ennemi1.getY()) ennemi1.setVivant(false);
			if (x == ennemi2.getX() && y - i == ennemi2.getY()) ennemi2.setVivant(false);
			if (x == ennemi3.getX() && y - i == ennemi3.getY()) ennemi3.setVivant(false);
		}
		else arretExplosionHaut = true;

	}

	if (niveau.caseLibre(y - portee + 1, x) && !arretExplosionHaut ) {
		
		if (!niveau.caseMurDestructible(y - portee + 1, x) && niveau.getCase(y - portee + 1, x) != '3') {
			//on affiche l'extremite de l'explosion si ce n'est pas un mur destructible
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1, y + 1 - portee + 1);
			glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 1, y - portee + 1);
			glTexCoord2f(0.75f, 0.75f); glVertex2d(x, y - portee + 1);
			glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 1 - portee + 1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
		else {
			niveau.modifierCase(y - portee + 1, x, '3');
		}
		//Test si il y a des mort
		if (x == bomberman.getX() && y - portee + 1 == bomberman.getY()) bomberman.setVivant(false);
		if (x == ennemi1.getX() && y - portee + 1 == ennemi1.getY()) ennemi1.setVivant(false);
		if (x == ennemi2.getX() && y - portee + 1 == ennemi2.getY()) ennemi2.setVivant(false);
		if (x == ennemi3.getX() && y - portee + 1 == ennemi3.getY()) ennemi3.setVivant(false);
	}

	
}

void Bombe::dessinerExplosionBas() {

	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y + i, x)) { //En bas
			if (niveau.caseMurDestructible(y + i, x)) {
				niveau.modifierCase(y + i, x, '3');
				arretExplosionBas = true;
			}
			else if(!arretExplosionBas) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y + 1 + i);
				glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y + i);
				glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y + i);
				glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 1 + i);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);

			}


			//Test si il y a des mort
			if (x == bomberman.getX() && y + i == bomberman.getY()) bomberman.setVivant(false);
			if (x == ennemi1.getX() && y + i == ennemi1.getY()) ennemi1.setVivant(false);
			if (x == ennemi2.getX() && y + i == ennemi2.getY()) ennemi2.setVivant(false);
			if (x == ennemi3.getX() && y + i == ennemi3.getY()) ennemi3.setVivant(false);
		}
		else arretExplosionBas = true;
	}

	if (niveau.caseLibre(y + portee - 1, x) && !arretExplosionBas) { //En bas
		if (!niveau.caseMurDestructible(y + portee - 1, x) && niveau.getCase(y + portee - 1, x) != '3') {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 1, y + 1 + portee - 1);
			glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1, y + portee - 1);
			glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + portee - 1);
			glTexCoord2f(0.75f, 0.75f); glVertex2d(x, y + 1 + portee - 1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
		else niveau.modifierCase(y + portee - 1, x, '3');
		//Test si il y a des mort
		if (x == bomberman.getX() && y + portee - 1 == bomberman.getY()) bomberman.setVivant(false);
		if (x == ennemi1.getX() && y + portee - 1 == ennemi1.getY()) ennemi1.setVivant(false);
		if (x == ennemi2.getX() && y + portee - 1 == ennemi2.getY()) ennemi2.setVivant(false);
		if (x == ennemi3.getX() && y + portee - 1 == ennemi3.getY()) ennemi3.setVivant(false);

	}
}

void Bombe::dessinerExplosionGauche() {


	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y, x - i)) { //A gauche

			if (niveau.caseMurDestructible(y, x - i)) {
				niveau.modifierCase(y, x - i, '3');
				arretExplosionGauche = true;
			}
			else if (!arretExplosionGauche) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.5f, 0.75f); glVertex2d(x + 1 - i, y + 1);
				glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1 - i, y);
				glTexCoord2f(0.25f, 0.875f); glVertex2d(x - i, y);
				glTexCoord2f(0.25f, 0.75f); glVertex2d(x - i, y + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);	
				glDisable(GL_BLEND);
			}

			//Test si il y a des mort
			if ((x - i) == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
			if ((x - i) == ennemi1.getX() && y == ennemi1.getY()) ennemi1.setVivant(false);
			if ((x - i) == ennemi2.getX() && y == ennemi2.getY()) ennemi2.setVivant(false);
			if ((x - i) == ennemi3.getX() && y == ennemi3.getY()) ennemi3.setVivant(false);

		}
		else arretExplosionGauche = true;

	}
	//extremité de l'explosion
	if (niveau.caseLibre(y, x - portee + 1) && !arretExplosionGauche) { //A gauche
		if (!niveau.caseMurDestructible(y, x - portee + 1) && niveau.getCase(y, x - portee + 1) != '3') {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.5f, 0.75f);  glVertex2d(x + 1 - portee + 1, y + 1);
			glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1 - portee + 1, y);
			glTexCoord2f(0.75f, 0.875f); glVertex2d(x - portee + 1, y);
			glTexCoord2f(0.75f, 0.75f); glVertex2d(x - portee + 1, y + 1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
		else niveau.modifierCase(y, x - portee + 1, '3');
		//Test si il y a des mort
		if (x - portee + 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		if (x - portee + 1 == ennemi1.getX() && y == ennemi1.getY()) ennemi1.setVivant(false);
		if (x - portee + 1 == ennemi2.getX() && y == ennemi2.getY()) ennemi2.setVivant(false);
		if (x - portee + 1 == ennemi3.getX() && y == ennemi3.getY()) ennemi3.setVivant(false);
	}

}

void Bombe::dessinerExplosionDroite() {

	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y, x + i)) { //A droite

			if (niveau.caseMurDestructible(y, x + i)) {
				niveau.modifierCase(y, x + i, '3');
				arretExplosionDroite = true;
			}
			else if (!arretExplosionDroite){
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.5f, 0.75f); glVertex2d(x + 1 + i, y + 1);
				glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1 + i, y);
				glTexCoord2f(0.25f, 0.875f); glVertex2d(x + i, y);
				glTexCoord2f(0.25f, 0.75f); glVertex2d(x + i, y + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			}

			//Test si il y a des mort
			if (x + i == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
			if (x + i == ennemi1.getX() && y == ennemi1.getY()) ennemi1.setVivant(false);
			if (x + i == ennemi2.getX() && y == ennemi2.getY()) ennemi2.setVivant(false);
			if (x + i == ennemi3.getX() && y == ennemi3.getY()) ennemi3.setVivant(false);
		}
		else arretExplosionDroite = true;
	}

	if (niveau.caseLibre(y, x + portee - 1) && !arretExplosionDroite) { //A droite
		if (!niveau.caseMurDestructible(y, x + portee - 1) && niveau.getCase(y, x + portee - 1) != '3') {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.75f, 0.75f); glVertex2d(x + 1 + portee - 1, y + 1);
			glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 1 + portee - 1, y);
			glTexCoord2f(0.5f, 0.875f); glVertex2d(x + portee - 1, y);
			glTexCoord2f(0.5f, 0.75f); glVertex2d(x + portee - 1, y + 1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		} else niveau.modifierCase(y, x + portee - 1, '3');

		//Test si il y a des mort
		if (x + portee - 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		if (x + portee - 1 == ennemi1.getX() && y == ennemi1.getY()) ennemi1.setVivant(false);
		if (x + portee - 1 == ennemi2.getX() && y == ennemi2.getY()) ennemi2.setVivant(false);
		if (x + portee - 1 == ennemi3.getX() && y == ennemi3.getY()) ennemi3.setVivant(false);
	}
}