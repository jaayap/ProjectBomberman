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

void Bombe::exploser() {



	niveau.modifierCase(y, x, '4');

		for (int i = 1; i < portee - 1; i++) {
			//dessin de l'explosion : 4 milieu de la bombe, 5 suite, 6 fin explosion

			if (niveau.caseLibre(y, x - i)) { //A gauche
					
				if (niveau.caseMurDestructible(y, x - i)) {
					//niveau.modifierCase(y, x - i, '3');
					arretExplosionGauche = true;
				}
				else {
					//niveau.modifierCase(y, x - i, '5');
				}

				//Test si il y a des mort
				if ((x - i) == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);

			}
			else {
				arretExplosionGauche = true;
			}
			if (niveau.caseLibre(y, x + i)) { //A droite
				
				if (niveau.caseMurDestructible(y, x + i)) {
				//	niveau.modifierCase(y, x + i, '3');
					arretExplosionDroite = true;
				}
				//else niveau.modifierCase(y, x + i, '5');

				//Test si il y a des mort
				if (x+i == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
			}
			else {
				arretExplosionDroite = true;
			}
			if (niveau.caseLibre(y - i, x)) { //En haut
			
				if (niveau.caseMurDestructible(y - i, x)) {
					//niveau.modifierCase(y - i, x, '3');
					arretExplosionHaut = true;
				}
				//else 	niveau.modifierCase(y - i, x, '5');

				//Test si il y a des mort
				if (x == bomberman.getX() && y-i == bomberman.getY()) bomberman.setVivant(false);
			}
			else {
				arretExplosionHaut = true;
			}
			if (niveau.caseLibre(y + i, x)) { //En bas
				
				if (niveau.caseMurDestructible(y + i, x)) {
					//niveau.modifierCase(y + i, x, '3');
					arretExplosionBas = true;
				} //else niveau.modifierCase(y + i, x, '5');
				//Test si il y a des mort
				if (x == bomberman.getX() && y+i == bomberman.getY()) bomberman.setVivant(false);

			}
			else {
				arretExplosionBas = true;
			}

			//Test si il y a des mort
			if (x == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);

		}

		//extremité de l'explosion
		if (niveau.caseLibre(y, x - portee+1) && !arretExplosionGauche) { //A gauche
			//niveau.modifierCase(y, x - portee+1, '6');

			//Test si il y a des mort
			if (x - portee + 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		}
		if (niveau.caseLibre(y, x + portee-1) && !arretExplosionDroite) { //A droite
			//niveau.modifierCase(y, x + portee-1, '6');
			if (x + portee - 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		}
		if (niveau.caseLibre(y - portee+1, x) && !arretExplosionHaut) { //En haut
		//	niveau.modifierCase(y - portee+1, x, '6');
			if (x == bomberman.getX() && y - portee + 1 == bomberman.getY()) bomberman.setVivant(false);
		}
		if (niveau.caseLibre(y + portee - 1, x) && !arretExplosionBas) { //En bas
			//niveau.modifierCase(y + portee-1, x, '6');
			if (x == bomberman.getX() && y + portee - 1 == bomberman.getY()) bomberman.setVivant(false);
		}
}


void Bombe::effacerExplosion() {

	niveau.modifierCase(y, x, '0');

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
	if (arretExplosionHaut) {		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y);
		glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y - 1);
		glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y - 1);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else {
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y);
		glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y - 1);
		glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y - 1);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1, y - 1);
		glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 1, y - 2);
		glTexCoord2f(0.75f, 0.75f); glVertex2d(x, y - 2);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y - 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
	}
}

void Bombe::dessinerExplosionBas() {
	if (arretExplosionBas) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y + 2);
		glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y + 1);
		glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y + 1);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 2);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else {

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y + 2);
		glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y + 1 );
		glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y + 1);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 2);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 1, y + 3);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 1, y + 2);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 2);
		glTexCoord2f(0.75f, 0.75f); glVertex2d(x, y + 3);
		glEnd();
		glDisable(GL_TEXTURE_2D);

	}
}

void Bombe::dessinerExplosionGauche() {
/*if (arretExplosionGauche) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 1);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x, y);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x - 1, y);
		glTexCoord2f(0.25f, 0.75f); glVertex2d(x - 1, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else {*/

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x , y + 1);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x, y);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x - 1, y);
		glTexCoord2f(0.25f, 0.75f); glVertex2d(x - 1, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, 0.75f);  glVertex2d(x - 1, y + 1);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x - 1, y);
		glTexCoord2f(0.75f, 0.875f); glVertex2d(x - 2, y);
		glTexCoord2f(0.75f, 0.75f); glVertex2d(x - 2, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);

	//}
}

void Bombe::dessinerExplosionDroite() {
	/*if (arretExplosionDroite) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x + 2, y + 1);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 2, y);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y);
		glTexCoord2f(0.25f, 0.75f); glVertex2d(x + 1, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else {*/

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x + 2, y + 1);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 2, y);
		glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y);
		glTexCoord2f(0.25f, 0.75f); glVertex2d(x + 1, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.75f, 0.75f); glVertex2d(x + 3, y + 1);
		glTexCoord2f(0.75f, 0.875f); glVertex2d(x + 3, y);
		glTexCoord2f(0.5f, 0.875f); glVertex2d(x + 2, y);
		glTexCoord2f(0.5f, 0.75f); glVertex2d(x + 2, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);

	//}
}