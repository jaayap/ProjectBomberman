#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Niveau.h"
#include "Bomberman.h"
#include <vector>
#include "Animation.h"
#include "Bonus.h"

using namespace std;

float coord[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };
int testAleatoire;
int maxMur = 0;
float numeroNiveau = 0;
bool PlacerBonus;

extern vector<GLuint> texture;

extern int valueBombe, valueExplo, valueMur, valueSortie;

extern bool victoire;
extern bool GameOver;
extern bool die;



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
	Animation anim;
}

void Niveau::dessinerNiveau() {

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {

			// destruction des murs
			if (victoire && matrice[i][j] == '2') {
				matrice[i][j] = '0';
			}

			// destruction des murs
			if (die && matrice[i][j] == '2') {
				matrice[i][j] = '0';
			}

			//Affichage des mur indestructible.
			if (matrice[i][j] == '1') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.75f, 0.75f - numeroNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.75f, 1.0f - numeroNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.5f, 1.0f - numeroNiveau); glVertex2d(j, i);
				glTexCoord2f(0.5f, 0.75f - numeroNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage du décors.
			if (matrice[i][j] == '5') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(1.0f, 0.75f - numeroNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(1.0f, 1.0f - numeroNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.75f, 1.0f - numeroNiveau); glVertex2d(j, i);
				glTexCoord2f(0.75f, 0.75f - numeroNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			if (matrice[i][j] == '3') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(coord[2 + valueMur], 0.0f); glVertex2d(j + 1, i + 1);
				glTexCoord2f(coord[2 + valueMur], 0.25f); glVertex2d(j + 1, i);
				glTexCoord2f(coord[0 + valueMur], 0.25f); glVertex2d(j, i);
				glTexCoord2f(coord[0 + valueMur], 0.0f); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage de l'herbe.
			if (matrice[i][j] == '0') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.75f - numeroNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 1.0f - numeroNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 1.0f - numeroNiveau); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.75f - numeroNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);

				// apparition aléatoire de murs destructibles
				testAleatoire = (rand() % 2 + 1);
				if (testAleatoire == 1 && maxMur < 50) {
					matrice[i][j] = '2';
					maxMur++;
				}
			}

			//Affichage des mur destructible.
			if (matrice[i][j] == '2') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.5f, 0.75f - numeroNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.5f, 1.0f - numeroNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.25f, 1.0f - numeroNiveau); glVertex2d(j, i);
				glTexCoord2f(0.25f, 0.75f - numeroNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);


				if (!PlacerBonus) {
					definirBonus(i, j); //on place les bonus derriere les mur destructible
				}
			}

			//Affichage de l'herbe SPAWN.
			if (matrice[i][j] == '4') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.75f - numeroNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 1.0f - numeroNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 1.0f - numeroNiveau); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.75f - numeroNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage des bombes.
			if (matrice[i][j] == '8') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[2]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(coord[2 + valueBombe], coord[7]); glVertex2d(j + 1, i + 1);
				glTexCoord2f(coord[2 + valueBombe], coord[8]); glVertex2d(j + 1, i);
				glTexCoord2f(coord[0 + valueBombe], coord[8]); glVertex2d(j, i);
				glTexCoord2f(coord[0 + valueBombe], coord[7]); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage de la sortie.
			if (victoire) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[6]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(coord[1 + valueSortie], 0.0f); glVertex2d(8 + 1, 6 + 1);
				glTexCoord2f(coord[1 + valueSortie], 1.0f); glVertex2d(8 + 1, 5 - 1);
				glTexCoord2f(coord[0 + valueSortie], 1.0f); glVertex2d(8, 5 - 1);
				glTexCoord2f(coord[0 + valueSortie], 0.0f); glVertex2d(8, 6 + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			}

			// Affichage du Game Over
			if (GameOver) {
				//cout << "gameover" << endl;
			}

			for (int k = 0; k < size(bonusTab); k++) {
				if (!caseMurDestructible(j, i) && bonusTab[k].getX() == i && bonusTab[k].getY() == j && !bonusTab[k].getUtiliser()) {
					bonusTab[k].setVisible(true); // si le mur est detruit on affiche le bonus
				}

				if (bonusTab[k].getVisible()) {
					bonusTab[k].dessiner();
				}
			}

		}
		
	}
	PlacerBonus = true;
}

bool Niveau::caseLibre(int x,int y) { // penser a inverser quand on appelle la fonction : caseLibre(y,x)
	if (x < 0 || y < 0 || x > 13 || y > 17) return false;
	if (matrice[x][y] == '1' || matrice[x][y] == '8' || matrice[x][y] == '5') return false;
	else return true;
}

bool Niveau::caseMurDestructible(int x,int y) {
	if (matrice[x][y] == '2') return true;
	else return false;
}

bool Niveau::caseLibreBombe(int x, int y) {
	if (x < 0 || y < 0 || x > 13 || y > 17) return false;
	if (matrice[x][y] == '1' || matrice[x][y] == '5') return false;
	else return true;
}

void Niveau::modifierCase(int x, int y, char valeur) {
	matrice[x][y] = valeur;
}

char Niveau::getCase(int x, int y) {
	return matrice[x][y];
}

void Niveau::definirBonus(int i, int j) {
	//Definition des bonus
	int nbAleatoire = rand() % 4 + 1;    //entre 1-4
	
	if (nbAleatoire == 1) {
		Bonus bonusNbNombre(j, i, 1);
		bonusTab.push_back(bonusNbNombre);
	}
	else if (nbAleatoire == 2) {
		Bonus bonusPortee(j, i, 2);
		bonusTab.push_back(bonusPortee);
	}
	else if (nbAleatoire == 3) {
		Bonus bonusVitesse(j, i, 3);
		bonusTab.push_back(bonusVitesse);
	}
	//Si le nombre est égal a 4 on ne place pas de bonus

}