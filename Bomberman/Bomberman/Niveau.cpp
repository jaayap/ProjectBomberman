#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Niveau.h"
#include <vector>


using namespace std;

extern vector<GLuint> texture;

extern float X1, X2, Y1, Y2;

Niveau::Niveau()
{
	initialiserMatrice();
}


Niveau::~Niveau()
{
}

void Niveau::initialiserMatrice() {
	ifstream file("Matrices/Level_1.txt");
	if (file.is_open()) {
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 17; j++) {
				file >> matrice[i][j];
			}
		}
	}
}

void Niveau::dessinerNiveau() {

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {

			//Affichage des mur indestructible.
			if (matrice[i][j] == '1') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.75f, 0.5f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.75f, 1.0f); glVertex2d(j + 1, i);
				glTexCoord2f(0.5f, 1.0f); glVertex2d(j, i);
				glTexCoord2f(0.5f, 0.5f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage des mur destructible.
			if (matrice[i][j] == '2') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.5f, 0.5f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.5f, 1.0f); glVertex2d(j + 1, i);
				glTexCoord2f(0.25f, 1.0f); glVertex2d(j, i);
				glTexCoord2f(0.25f, 0.5f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			if (matrice[i][j] == '3') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.0f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 0.5f); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 0.5f); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage de l'herbe.
			if (matrice[i][j] == '0') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.5f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 1.0f); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 1.0f); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.5f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage des bombes.
			if (matrice[i][j] == '8') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(X1, Y1); glVertex2d(j + 1, i + 1);
				glTexCoord2f(X1, Y2); glVertex2d(j + 1, i);
				glTexCoord2f(X2, Y2); glVertex2d(j, i);
				glTexCoord2f(X2, Y1); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage Explosion.
			if (matrice[i][j] == '4') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.75f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 0.875f); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 0.875f); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.75f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			
			if (matrice[i][j] == '5') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.5f, 0.75f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.5f, 0.875f); glVertex2d(j + 1, i);
				glTexCoord2f(0.25f, 0.875f); glVertex2d(j, i);
				glTexCoord2f(0.25f, 0.75f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			if (matrice[i][j] == '6') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.75f, 0.75f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.75f, 0.875f); glVertex2d(j + 1, i);
				glTexCoord2f(0.5f, 0.875f); glVertex2d(j, i);
				glTexCoord2f(0.5f, 0.75f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			

		}
	}
}

bool Niveau::caseLibre(int x,int y) { // penser a inverser quand on appelle la fonction : caseLibre(y,x)
	if (x < 0 || y < 0 || x > 13 || y > 17) return false;
	if (matrice[x][y] == '1' || matrice[x][y] == '8') return false;
	else return true;
}

bool Niveau::caseMurDestructible(int x,int y) {
	if (matrice[x][y] == '2') return true;
	else return false;
}

void Niveau::modifierCase(int x, int y, char valeur) {
	matrice[x][y] = valeur;
}