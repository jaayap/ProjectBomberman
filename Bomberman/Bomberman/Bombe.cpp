#include "Bombe.h"
#include "Niveau.h"
#include <iostream>
#include "Bomberman.h"
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>

using namespace std; 

extern Niveau niveau;
extern Bomberman bomberman;
extern vector<GLuint> texture;

bool arretExplosionHaut = false;
bool arretExplosionBas = false;
bool arretExplosionGauche = false;
bool arretExplosionDroite = false;

Bombe::Bombe()
{
}

Bombe::Bombe(int x, int y) {
	this->x = x;
	this->y = y;
	posee = false;
	explosion = false;
}

Bombe::~Bombe()
{
}


void Bombe::effacerExplosion() {
	// on efface la bombe
	niveau.modifierCase(y, x, '0'); 
	//on efface les murs detruits

	//on remet les booleens a false
	 arretExplosionHaut = false;
	 arretExplosionBas = false;
	 arretExplosionGauche = false;
	 arretExplosionDroite = false;
}

void Bombe::dessinerExplosion() {

	//Centre de l'explosion
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
			else {
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
			}

			//Test si il y a des mort
			if (x == bomberman.getX() && y - i == bomberman.getY()) bomberman.setVivant(false);
		}
		else arretExplosionHaut = true;

	}

	if (niveau.caseLibre(y - portee + 1, x) && !arretExplosionHaut) {
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

		//Test si il y a des mort
		if (x == bomberman.getX() && y - portee + 1 == bomberman.getY()) bomberman.setVivant(false);
	}
	
}

void Bombe::dessinerExplosionBas() {

	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y + i, x)) { //En bas
			if (niveau.caseMurDestructible(y + i, x)) {
				niveau.modifierCase(y + i, x, '3');
				arretExplosionBas = true;
			}
			else {
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
			}

			//Test si il y a des mort
			if (x == bomberman.getX() && y + i == bomberman.getY()) bomberman.setVivant(false);
		}
		else arretExplosionBas = true;
	}

	if (niveau.caseLibre(y + portee - 1, x) && !arretExplosionBas) { //En bas
																	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 1, y + 1 + portee - 1);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1, y + portee - 1);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + portee - 1);
		glTexCoord2f(0.75f, 0.75f); glVertex2d(x, y + 1 + portee -1);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//Test si il y a des mort
		if (x == bomberman.getX() && y + portee - 1 == bomberman.getY()) bomberman.setVivant(false);

	}
}

void Bombe::dessinerExplosionGauche() {


	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y, x - i)) { //A gauche

			if (niveau.caseMurDestructible(y, x - i)) {
				niveau.modifierCase(y, x - i, '3');
				arretExplosionGauche = true;
			}
			else {
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
			}

			//Test si il y a des mort
			if ((x - i) == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);

		}
		else arretExplosionGauche = true;

	}
	//extremité de l'explosion
	if (niveau.caseLibre(y, x - portee + 1) && !arretExplosionGauche) { //A gauche
																		
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
		
		//Test si il y a des mort
		if (x - portee + 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
	}
		

	
}

void Bombe::dessinerExplosionDroite() {

	for (int i = 1; i < portee - 1; i++) {
		if (niveau.caseLibre(y, x + i)) { //A droite

			if (niveau.caseMurDestructible(y, x + i)) {
				niveau.modifierCase(y, x + i, '3');
				arretExplosionDroite = true;
			}
			else {
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

			}

			//Test si il y a des mort
			if (x + i == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		}
		else arretExplosionDroite = true;
	}

	if (niveau.caseLibre(y, x + portee - 1) && !arretExplosionDroite) { //A droite
		
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
		
		//Test si il y a des mort
		if (x + portee - 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
	}
		

	
}