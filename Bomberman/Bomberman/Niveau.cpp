#include <Sstream>
#include <fstream>
#include <iostream>
#include <String>
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
int textBombe = 2;

float nbrNiveau = 0;

bool PlacerBonus;
bool finDestruction = true;

extern vector<GLuint> texture;

extern int valueBombe, valueExplo, valueMur, valueSortie;
extern int vie;
extern int numNiveau;

extern bool victoire;
extern bool gameOver;
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
			//if (victoire && matrice[i][j] == '2') {
			//	matrice[i][j] = '0';
			//}

			// destruction des murs
			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 17; j++) {
					if (!finDestruction && matrice[i][j] == '2') {
						matrice[i][j] = '0';
						maxMur = 0;
					}
				}
			}

			// destruction des bonus
			if (!finDestruction && size(bonusTab) > 0) {
				for (int k = 0; k < size(bonusTab); k++) {
					bonusTab[k].setVisible(false);
					bonusTab[k].setUtiliser(true); // l'objet agit comme s'il avait ete utilise
				}
				bonusTab.erase(bonusTab.begin(), bonusTab.begin() + size(bonusTab));
				PlacerBonus = false;
				finDestruction = true;
			}

			// TEXTURES SELON NIVEAU
			if (numNiveau == 1) {
				nbrNiveau = 0.0f;
				textBombe = 2;
			}
			else if (numNiveau == 2) {
				nbrNiveau = 0.25f;
				textBombe = 19;
			}
			else if (numNiveau == 3) {
				nbrNiveau = 0.5f;
				textBombe = 20;
			}
			else if (numNiveau == 5) {
				nbrNiveau = 0.75f;
				textBombe = 21;
			}

			//Affichage des mur indestructible.
			if (matrice[i][j] == '1') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.75f, 0.75f - nbrNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.75f, 1.0f - nbrNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.5f, 1.0f - nbrNiveau); glVertex2d(j, i);
				glTexCoord2f(0.5f, 0.75f - nbrNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage du décors.
			if (matrice[i][j] == '5') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(1.0f, 0.75f - nbrNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(1.0f, 1.0f - nbrNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.75f, 1.0f - nbrNiveau); glVertex2d(j, i);
				glTexCoord2f(0.75f, 0.75f - nbrNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			if (matrice[i][j] == '3') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[24]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(coord[2 + valueMur], 0.75f - nbrNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(coord[2 + valueMur], 1.0f - nbrNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(coord[0 + valueMur], 1.0f - nbrNiveau); glVertex2d(j, i);
				glTexCoord2f(coord[0 + valueMur], 0.75f - nbrNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage du sol.
			if (matrice[i][j] == '0') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.75f - nbrNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 1.0f - nbrNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 1.0f - nbrNiveau); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.75f - nbrNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				// apparition aléatoire de murs destructibles
				testAleatoire = (rand() % 2 + 1);
				if (testAleatoire == 1 && maxMur < 60) {
					matrice[i][j] = '2';
					maxMur++;
				}
			}

			//Affichage du spawn
			if (matrice[i][j] == '4') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.25f, 0.75f - nbrNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.25f, 1.0f - nbrNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.0f, 1.0f - nbrNiveau); glVertex2d(j, i);
				glTexCoord2f(0.0f, 0.75f - nbrNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

			//Affichage des mur destructible.
			if (matrice[i][j] == '2') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.5f, 0.75f - nbrNiveau); glVertex2d(j + 1, i + 1);
				glTexCoord2f(0.5f, 1.0f - nbrNiveau); glVertex2d(j + 1, i);
				glTexCoord2f(0.25f, 1.0f - nbrNiveau); glVertex2d(j, i);
				glTexCoord2f(0.25f, 0.75f - nbrNiveau); glVertex2d(j, i + 1);
				glEnd();
				glDisable(GL_TEXTURE_2D);

				if (!PlacerBonus) {
					definirBonus(i, j); //on place les bonus derriere les mur destructible
				}
			}

			//Affichage des bombes.
			if (matrice[i][j] == '8') {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[textBombe]);
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
			if (gameOver) {
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
	int nbAleatoire = rand() % 8 + 1;    //entre 1-8
	
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