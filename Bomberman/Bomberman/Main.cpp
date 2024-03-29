//Point d'entree de l'application.

#include "GL/glut.h"
#include "SOIL/SOIL.h" //utile pour les textures.
#include <time.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <String>
#include <string>
#include "SFML/Audio.hpp" // utile pour les sons.
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h" // Librarie pour l'arduino.
#include "Niveau.h"
#include "Personnage.h"
#include "Bomberman.h"
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"
#include "Animation.h"

using namespace std;

// ---------------------------------------------
// Declarations des variables
// ---------------------------------------------
int HAUTEUR_FENETRE = 1046;
int LARGEUR_FENETRE = 900;
vector<GLuint>	texture; // tableau qui contient nos textures.

int score = 0;
int vie = 3;
int numNiveau = 1;

bool enMouvement = false;
bool enMouvement2 = false;
bool haut = false, bas = false, gauche = false, droite = false;
bool haut2 = false, bas2 = false, gauche2 = false, droite2 = false;
bool victoire = false;

// Intro
bool afficherHistoire = true;
bool incrAlpha = true;
float alphaImg = 1.0f;
int numImage = 13;

//Menu
bool afficherMenu = false;
float position_cursor_x = 0.25;
float position_cursor_y = 0.63;
int position_cursor = 1; // 1 : normal Game, 2 : Battle Game , 3 : Option.
bool duel = false;

bool pause = false; //permet de mettre le jeu en pause.

//Menu option 
bool afficherOption = false;
bool afficherCommande = false;


//Jeux
Niveau niveau;
bool explosionEnCours = false;
bool explosionEnCours2 = false;

bool gameOver = false;

// Affichage ecrans victoire / defaite
bool afficherJ1 = false;
bool afficherJ2 = false;
bool afficherV = false;
bool afficherGO = false;
bool afficherEgalite = false;

//Joueurs
Bomberman bomberman(3, 1);
Bomberman bomberman2(14, 11);
int textureJoueur1 = 3;
int textureJoueur2 = 25;

//Declaration des ennemis
vector<Personnage*> ennemisTab;

EnnemiAleatoire ennemiTest(99, 99);
EnnemiAleatoire ennemi1(5, 9);
EnnemiAleatoire ennemi4(5, 5);
EnnemiAllerRetour ennemi2(5, 3, 1, false);
EnnemiAllerRetour ennemi3(8, 5, 4, false);
EnnemiAllerRetour ennemi5(8, 10, 4, false);

// Deplacement
extern float vitesseDeplacement;

// Sons
vector<sf::Music*> tableMusic;
sf::Music musicIntro;
sf::Music musicMenu;
sf::Music musicZone1;
sf::Music musicZone2;
sf::Music musicZone3;
sf::Music musicDuel;
sf::Music sonBombes;
bool sonB = false;
sf::Music sonExplo;
bool sonE = false;
sf::Music sonBonus;
bool sonBo = false;
sf::Music sonMort;
bool sonM = false;
sf::Music sonNiveau;
bool sonN = false;
sf::Music sonMonstre;
bool sonMo = false;
sf::Music sonMenu;
bool sonMe = false;
int volume = 100;

//Arduino
bool utiliserManette = true;
Serial* SP = new Serial("COM3");    // adjust as needed - port com.
char incomingData[256] = "";		// don't forget to pre-allocate memory.
int dataLength = 256;
int readResult = 0;
bool allumerLedVerte = false;

// ---------------------------------------------
// Declarations des fonctions
// ---------------------------------------------
void LabyAffichage();
void LabyRedim(int width, int height);
void LabyTimerExplosion(int z);
void LabyTimerEnnemi(int z);
void TraitementClavier(int key, int x, int y);
void TraitementClavierASCII(unsigned char key, int x, int y);
void TraitementAucuneTouche(int key, int x, int y);
void TraitementArduino(int z);
void transitionHistoire(int z);
int  LoadGLTextures(string name);
void affichageVictoireDefaite(int z);
void PlayMusic(int z);

// ---------------------------------------------
// Definitions des fonctions
// ---------------------------------------------

//Affiche les ecrans de victoires et de defaites
void affichageVictoireDefaite(int z) {
	if (afficherJ1) {
		afficherJ1 = false;
		vie++;
	}
	if (afficherJ2) {
		afficherJ2 = false;
		vie++;
	}
	if (afficherEgalite) {
		afficherEgalite = false;
		vie++;
	}
	if (afficherV) {
		afficherV = false;
	}
	if (afficherGO) {
		afficherGO = false;
	}

	afficherMenu = true;
}

//fonction qui actualise l'affichage.
void LabyAffichage() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	if (afficherHistoire) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture Background Histoire.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[numImage]);
		glBegin(GL_QUADS);
		glColor4f(1.0, 1.0, 1.0, alphaImg);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	else if (afficherJ1) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[26]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (afficherJ2) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[27]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (afficherEgalite) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[29]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (afficherV) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[28]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (afficherGO) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (afficherMenu) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture Background Menu.
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[8]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glViewport(LARGEUR_FENETRE * position_cursor_x, -HAUTEUR_FENETRE * position_cursor_y, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture du curseur.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(1, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(1, 1);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		score = 0;
		numNiveau = 1;
	}
	else if (afficherOption) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture Background Menu Option.
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[22]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glViewport(LARGEUR_FENETRE * position_cursor_x, -HAUTEUR_FENETRE * position_cursor_y, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture du curseur.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(1, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(1, 1);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	else if (afficherCommande) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture des commandes.
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[23]); 
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if (duel) {
		numNiveau = 5;
		
		//on verifie la collision avec un bonus.
		bomberman.ramasserBonus(1);
		bomberman2.ramasserBonus(2);

		//on dessine le niveau et les personnages.
		niveau.dessinerNiveau();
		bomberman.dessiner();
		bomberman2.dessiner2();

		if (!bomberman.vivant && !bomberman2.vivant) {
			duel = false;
			afficherMenu = true;
			numNiveau = 1;
			bomberman2.vitesseDeplacement = 0.10f;
			bomberman.retour(1);
			bomberman2.retour(2);
			bomberman.vivant = true;
			bomberman2.vivant = true;
			for (int i = 0; i < size(bomberman2.bombes); i++) {
				bomberman2.bombes[i].effacerBombes();
				bomberman2.eraseExplosion(i);
				//on efface les murs detruits.
				for (int i = 0; i < 13; i++) {
					for (int j = 0; j < 17; j++) {
						if (niveau.getCase(i, j) == '3') {
							niveau.modifierCase(i, j, '0');
						}
					}
				}
			}
			afficherEgalite = true;
			glutTimerFunc(3000, affichageVictoireDefaite, 0);
		}
		else if (!bomberman.vivant) {
			duel = false;
			numNiveau = 1;
			bomberman2.vitesseDeplacement = 0.10f;
			bomberman.retour(1);
			bomberman2.retour(2);
			bomberman.vivant = true;
			afficherJ2 = true;
			glutTimerFunc(3000, affichageVictoireDefaite, 0);
		}
		else if (!bomberman2.vivant) {
			duel = false;
			afficherMenu = true;
			numNiveau = 1;
			bomberman2.vitesseDeplacement = 0.10f;
			bomberman.retour(1);
			bomberman2.retour(2);
			bomberman2.vivant = true;
			for (int i = 0; i < size(bomberman2.bombes); i++) {
				bomberman2.bombes[i].effacerBombes();
				bomberman2.eraseExplosion(i);
				//on efface les murs detruits.
				for (int i = 0; i < 13; i++) {
					for (int j = 0; j < 17; j++) {
						if (niveau.getCase(i, j) == '3') {
							niveau.modifierCase(i, j, '0');
						}
					}
				}
			}
			afficherJ1 = true;
			glutTimerFunc(3000, affichageVictoireDefaite, 0);
		}

		//on dessine les explosions.
		for (int i = 0; i < size(bomberman.bombes); i++) {
			if (bomberman.bombes[i].explosion) {
				bomberman.bombes[i].dessinerExplosion();
			}
		}

		for (int i = 0; i < size(bomberman2.bombes); i++) {
			if (bomberman2.bombes[i].explosion) {
				bomberman2.bombes[i].dessinerExplosion();
			}
		}

		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();

		if (pause) {
			//Affichage de l'ecran pause.
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[12]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}
	else {
		//on dessine le niveau.
		niveau.dessinerNiveau();

		//Test colision ennemi et bonus.
		bomberman.collisionEnnemi();
		bomberman.ramasserBonus(1);

		//Affichage des personnages.
		bomberman.dessiner();
		if (size(ennemisTab) > 1) {
			for (int i = 0; i < size(ennemisTab); i++) {
				if (ennemisTab[i]->vivant) {
					ennemisTab[i]->dessiner();
				}
				else {
					ennemisTab.erase(ennemisTab.begin() + i);
					score += 100;
					sonMo = true;
				}
			}
		}
		else if (size(ennemisTab) == 1 && !victoire && numNiveau == 3) {
			victoire = true;
			afficherV = true;
			glutTimerFunc(3000, affichageVictoireDefaite, 0);
		}
		else if (size(ennemisTab) == 1 && !victoire) {
			victoire = true;
		}

		for (int i = 0; i < size(bomberman.bombes); i++) {
			if (bomberman.bombes[i].explosion) {
				bomberman.bombes[i].dessinerExplosion();
			}
		}

		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();

		// Texture score & vies.
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[7]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 1);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		// Affichage du score.
		if (gameOver && score != 0) {
			afficherGO = true;
			glutTimerFunc(3000, affichageVictoireDefaite, 0);
		}
		if (gameOver) {
			score = 0;
		}
		string s = to_string(score);
		int tailleScore = s.size();

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(5, 0.6f);
		string scor = s;
		for (int i = 0; i < tailleScore; ++i) {
			glColor3d(1.0, 0.0, 0.0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scor[i]);
		}

		// Affichage de la vie.
		string v = to_string(vie);
		int tailleVie = v.size();

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(0.7f, 0.6f);
		string vi = v;
		for (int i = 0; i < tailleVie; ++i) {
			glColor3d(1.0, 0.0, 0.0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, vi[i]);
		}

		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE - 60);
		glLoadIdentity();

		if (pause) {
			//Affichage de l'ecran pause.
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[12]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}
	glFlush();
}

void LabyRedim(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)17, (double)13, 0.0); // nbColonnes , nbLignes
	HAUTEUR_FENETRE = height;
	LARGEUR_FENETRE = width;
}

//Traitement des touches haut et bas
void TraitementClavier(int key, int x, int y)
{
	glutPostRedisplay();

	if (afficherMenu || afficherOption) {
		//Bouge le curseur 
		if (key == GLUT_KEY_UP) {
			if (position_cursor_y > 0.63) {
				position_cursor_y -= 0.07;
				position_cursor -= 1;
			}
		}

		if (key == GLUT_KEY_DOWN) {
			if (position_cursor_y < 0.7) {
				position_cursor_y += 0.07;
				position_cursor += 1;
			}
		}
	}
	else {
		if (!pause) {
			//Deplacement
			if (key == GLUT_KEY_UP) {
				haut = true;
			}
			if (key == GLUT_KEY_DOWN) {
				bas = true;
			}
			if (key == GLUT_KEY_LEFT) {
				gauche = true;
			}
			if (key == GLUT_KEY_RIGHT) {
				droite = true;
			}
		}
	}
	glFlush();
}

//fonction utile pour l'annimation
void TestDirection(int z) {

	float test = bomberman.getVitesseDeplacement() / 2.00;
	float test2 = bomberman2.getVitesseDeplacement() / 2.00;

	if (haut) {
		for (float i = 0.00; i < test; i += 0.1) {
			enMouvement = true;
			bomberman.deplacementHaut();
		}
	}
	else if (bas) {
		for (float i = 0.00; i < test; i += 0.1) {
			enMouvement = true;
			bomberman.deplacementBas();
		}
	}
	else if (gauche) {
		for (float i = 0.00; i < test; i += 0.1) {
			enMouvement = true;
			bomberman.deplacementGauche();
		}
	}
	else if (droite) {
		for (float i = 0.00; i < test; i += 0.1) {
			enMouvement = true;
			bomberman.deplacementDroite();
		}
	}

	if (haut2) {
		for (float i = 0.00; i < test2; i += 0.1) {
			enMouvement2 = true;
			bomberman2.deplacementHaut();
		}
	}
	else if (bas2) {
		for (float i = 0.00; i < test2; i += 0.1) {
			enMouvement2 = true;
			bomberman2.deplacementBas();
		}
	}
	else if (gauche2) {
		for (float i = 0.00; i < test2; i += 0.1) {
			enMouvement2 = true;
			bomberman2.deplacementGauche();
		}
	}
	else if (droite2) {
		for (float i = 0.00; i < test2; i += 0.1) {
			enMouvement2 = true;
			bomberman2.deplacementDroite();
		}
	}
	glutTimerFunc(25, TestDirection, 0);
}

//Remet les variables de mouvements a faux lorsque la touche est relachee.
void TraitementAucuneTouche(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		haut = false;
		enMouvement = false;
	}
	if (key == GLUT_KEY_DOWN) {
		bas = false;
		enMouvement = false;
	}
	if (key == GLUT_KEY_LEFT) {
		gauche = false;
		enMouvement = false;
	}
	if (key == GLUT_KEY_RIGHT) {
		droite = false;
		enMouvement = false;
	}
}

void TraitementClavierASCII(unsigned char key, int x, int y) {
	glutPostRedisplay();
	if (afficherHistoire) {
		if (key == 10 || key == 13) { // Touche entree.
			afficherHistoire = false;
			afficherMenu = true;
		}
	}
	else if (afficherMenu && !afficherHistoire) {
		if (key == 10 || key == 13) { // Touche entree.
			if (position_cursor == 1) { // on lance le niveau.
				afficherMenu = false;
				sonMe = true;
			}
			else if (position_cursor == 2) { // on lance le mode duel.
				afficherMenu = false;
				duel = true;
				sonMe = true;
			}
			else if (position_cursor == 3) { // on ouvre le menu option.
				afficherMenu = false;
				afficherOption = true;
				sonMe = true;
			}
		}
	}
	else if (afficherOption) {
		if (key == 10 || key == 13) { // Touche entree.
			if (position_cursor == 1) { // volume +
				sonMe = true;
				if (volume < 100) volume += 5;
			}
			else if (position_cursor == 2) { //Volume -
				sonMe = true;
				if (volume > 0) volume -= 5;
			}
			else if (position_cursor == 3) { //Commandes
				sonMe = true;
				afficherOption = false;
				afficherCommande = true;
			}
		}
	}
	else if( !afficherMenu && ! afficherOption && !afficherCommande){
			if ((key == 66 || key == 98) && !pause) { // touche B.
				bomberman.lancerBombe();
			}

			//mettre en pause le jeu.
			if (key == 80 || key == 112) { // touche P.
				if (pause) pause = false;
				else pause = true;
			}
	}

	if (key == 27) {// touche Echap.
		if (afficherCommande) { //retour.
			afficherCommande = false;
			afficherOption = true;
		}
		else if (afficherOption) { //retour.
			afficherOption = false;
			afficherMenu = true;		
		}
		else {
			glutDestroyWindow(1);
			exit(0);
		}
	}

	// DUEL - touches pour le joueurs 2.
	if (duel && !pause) {
		if (key == 90 || key == 122) { // touche Z.
			haut2 = true;
		}
		if (key == 83 || key == 115) { // touche S.
			bas2 = true;
		}
		if (key == 81 || key == 113) { // touche Q.
			gauche2 = true;
		}
		if (key == 68 || key == 100) { // touche D.
			droite2 = true;
		}
		if ((key == 88 || key == 120) && !pause) { // touche X.
			bomberman2.lancerBombe();
		}
	}
	glFlush();
}

//Remet les variables de mouvements du joueur 2 a faux lorsque la touche est relachee.
void TraitementAucuneToucheASCII(unsigned char key, int x, int y) {
	if (duel) {
		if (key == 90 || key == 122) { // touche Z.
			haut2 = false;
			enMouvement2 = false;
		}
		if (key == 83 || key == 115) { // touche S.
			bas2 = false;
			enMouvement2 = false;
		}
		if (key == 81 || key == 113) { // touche Q.
			gauche2 = false;
			enMouvement2 = false;
		}
		if (key == 68 || key == 100) { // touche D.
			droite2 = false;
			enMouvement2 = false;
		}
	}	
}

//Gestion des explosions.
void LabyTimerExplosion(int z) {

	for (int i = 0; i < size(bomberman.bombes); i++) {
		if (bomberman.bombes[i].posee) {
			explosionEnCours = true;
			if (!pause) bomberman.bombes[i].Timer++;
			//Explosion au bout de 2,5 secondes.
			if (bomberman.bombes[i].Timer > 5 && !bomberman.bombes[i].explosion) {//creation de l'explosion.
				bomberman.bombes[i].explosion = true;
				bomberman.declancherExplosion(i);
			}

			//500 ms plus tard.
			if (bomberman.bombes[i].Timer > 6) {// Suppression de l'explosion.
												// Efface la trace de l'explosion et reinitialise les booleens.
				bomberman.bombes[i].explosion = false;
				bomberman.eraseExplosion(i);

				//on efface les murs detruits.
				for (int i = 0; i < 13; i++) {
					for (int j = 0; j < 17; j++) {
						if (niveau.getCase(i, j) == '3') {
							niveau.modifierCase(i, j, '0');
						}
					}
				}
				explosionEnCours = false;
			}
			glutPostRedisplay();
		}
	}

	if (duel) {
		for (int i = 0; i < size(bomberman2.bombes); i++) {
			if (bomberman2.bombes[i].posee) {
				explosionEnCours2 = true;
				if (!pause) bomberman2.bombes[i].Timer++;
				//Explosion au bout de 2,5 secondes.
				if (bomberman2.bombes[i].Timer > 5 && !bomberman2.bombes[i].explosion) {//creation de l'explosion.
					bomberman2.bombes[i].explosion = true;
					bomberman2.declancherExplosion(i);

				}

				//500 ms plus tard.
				if (bomberman2.bombes[i].Timer > 6) {// Effacer explosion.	
													 // Efface la trace de l'explosion et reinitialise les booleens.
					bomberman2.bombes[i].explosion = false;
					bomberman2.eraseExplosion(i);

					//on efface les murs detruits.
					for (int i = 0; i < 13; i++) {
						for (int j = 0; j < 17; j++) {
							if (niveau.getCase(i, j) == '3') {
								niveau.modifierCase(i, j, '0');
							}
						}
					}
					explosionEnCours2 = false;

				}
				glutPostRedisplay();
			}
		}
	}

	glutTimerFunc(500, LabyTimerExplosion, 0);
}

//Calcul le deplacement des ennemis en boucle.
void LabyTimerEnnemi(int z) {
	if (!pause && size(ennemisTab) > 0) {
		for (int i = 0; i < size(ennemisTab); i++) {
			ennemisTab[i]->calculDeplacement();
		}
	}
	glutTimerFunc(30, LabyTimerEnnemi, 0);
}


// Chargement des textures.
int LoadGLTextures(string name) //Charge l'image et la convertit en texture.
{
	GLuint essai = SOIL_load_OGL_texture
	(
		name.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	texture.push_back(essai);

	if (texture.at(texture.size() - 1) == 0)
		return false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;  // Return Success.
}

//Remplis le tableau d'ennemis.
void tableEnnemis() {
	ennemisTab.push_back(&ennemiTest);
	ennemisTab.push_back(&ennemi1);
	ennemisTab.push_back(&ennemi2);
	ennemisTab.push_back(&ennemi3);
}

void PlayMusic(int z) {
	//SONS
	if (sonB) {
		sonBombes.play();
		sonB = false;
	}
	if (sonBo) {
		sonBonus.play();
		sonBo = false;
	}
	if (sonM) {
		sonMort.play();
		sonM = false;
	}
	if (sonE) {
		sonExplo.play();
		sonE = false;
	}
	if (sonMe) {
		sonMenu.play();
		sonMe = false;
	}
	if (sonMo) {
		sonMonstre.play();
		sonMo = false;
	}
	if (sonN) {
		sonNiveau.play();
		sonN = false;
	}

	// Musique Intro
	if (afficherHistoire) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicIntro) {
				if (musicIntro.getStatus() == sf::Sound::Status::Playing) {
					glutTimerFunc(50, PlayMusic, 0);
					return;
				}
				else {
					cout << "Musique Intro" << endl;
					musicIntro.play();
					musicIntro.setLoop(true);
				}
			}
		}
	}
	// Stopper musique
	else if (afficherJ1 || afficherJ2 || afficherV || afficherGO || afficherEgalite) {
		for (int i = 0; i < size(tableMusic); i++) {
			tableMusic[i]->stop();
			tableMusic[i]->setLoop(false);
		}
	}
	// Musique Menu
	else if (afficherMenu && !afficherHistoire || afficherOption || afficherCommande) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicMenu) {
				if (musicMenu.getStatus() == sf::Sound::Status::Playing) {
					glutTimerFunc(50, PlayMusic, 0);
					musicMenu.setVolume(volume);
					return;
				}
				else {
					cout << "Musique Menu" << endl;
					volume = 100;
					musicMenu.play();
					musicMenu.setLoop(true);
				}
			}
			else {
				tableMusic[i]->stop();
				tableMusic[i]->setLoop(false);
			}
		}
	}
	// Musique Zone 1
	else if (!afficherMenu && !afficherHistoire && numNiveau == 1) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicZone1) {
				if (musicZone1.getStatus() == sf::Sound::Status::Playing && !pause) {
					glutTimerFunc(50, PlayMusic, 0);
					musicZone1.setVolume(volume);
					return;
				}
				else {
					cout << "Musique Zone 1" << endl;
					musicZone1.play();
					musicZone1.setLoop(true);
				}
			}
			else if (!pause) {
				tableMusic[i]->stop();
				tableMusic[i]->setLoop(false);
			}
		}
	}
	// Musique Zone 2
	else if (!afficherMenu && !afficherHistoire && numNiveau == 2) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicZone2) {
				if (musicZone2.getStatus() == sf::Sound::Status::Playing && !pause) {
					glutTimerFunc(50, PlayMusic, 0);
					musicZone2.setVolume(volume);
					return;
				}
				else {
					cout << "Musique Zone 2" << endl;
					musicZone2.play();
					musicZone2.setLoop(true);
				}
			}
			else if (!pause) {
				tableMusic[i]->stop();
				tableMusic[i]->setLoop(false);
			}
		}
	}
	// Musique Zone 3
	else if (!afficherMenu && !afficherHistoire && numNiveau == 3) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicZone3) {
				if (musicZone3.getStatus() == sf::Sound::Status::Playing && !pause) {
					glutTimerFunc(50, PlayMusic, 0);
					musicZone3.setVolume(volume);
					return;
				}
				else {
					cout << "Musique Zone 3" << endl;
					musicZone3.play();
					musicZone3.setLoop(true);
				}
			}
			else if (!pause) {
				tableMusic[i]->stop();
				tableMusic[i]->setLoop(false);
			}
		}
	}
	// Musique Duel
	else if (!afficherMenu && !afficherHistoire && numNiveau == 5) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicDuel) {
				if (musicDuel.getStatus() == sf::Sound::Status::Playing && !pause) {
					glutTimerFunc(50, PlayMusic, 0);
					musicDuel.setVolume(volume);
					return;
				}
				else if (!pause) {
					cout << "Musique Duel" << endl;
					musicDuel.play();
					musicDuel.setLoop(true);
				}
			}
			else {
				tableMusic[i]->stop();
				tableMusic[i]->setLoop(false);
			}
		}
	}

	// PAUSE
	if (pause) {
		for (int i = 0; i < size(tableMusic); i++) {
			tableMusic[i]->pause();
		}
	}
	glutTimerFunc(50, PlayMusic, 0);
}

//Gestion des images de l'introduction
void transitionHistoire(int z) {
	if (afficherHistoire) {
		if (numImage < 19) {
			if (incrAlpha) {
				if (alphaImg >= 1.0f) {
					incrAlpha = false;
					glutTimerFunc(2000, transitionHistoire, 0);
					return;
				}
				else if (alphaImg < 1.0f) {
					alphaImg += 0.01f;
				}
			}
			else if (!incrAlpha) {
				if (alphaImg <= 0.0f) {
					incrAlpha = true;
					if (numImage == 18) {
						afficherHistoire = false;
						afficherMenu = true;
						return;
					}
					numImage++;
				}
				else if (alphaImg > 0.0f && numImage != 18) {
					alphaImg -= 0.01f;
				}
				else {
					alphaImg -= 0.01f;
					if (volume > 0) {
						volume--;
						musicIntro.setVolume(volume);
					}
				}
			}
		}
		glutTimerFunc(50, transitionHistoire, 0);
	}
}

//Communication avec l'arduino.
void TraitementArduino(int z) {

	if (SP->IsConnected() && utiliserManette)
	{
		readResult = SP->ReadData(incomingData, dataLength);//on lit les infos de l'arduino.

		if (readResult != -1) {
			//BOUTONS
			if (incomingData[0] == 'A') { //on appuie sur le bouton	 A.
				if (!pause && !afficherHistoire && !afficherMenu && !afficherOption && !afficherCommande) { // touche B.
					bomberman.lancerBombe();
				}
				else  if (afficherHistoire) {
					afficherHistoire = false;
					afficherMenu = true;
				}
				else if (afficherMenu && !afficherHistoire) {
					if (position_cursor == 1) { //mode aventure.
						afficherMenu = false;
						sonMe = true;
					}
					else if (position_cursor == 2) { //mode versus.
						afficherMenu = false;
						duel = true;
						sonMe = true;
					}
					else if (position_cursor == 3) {//mode option.
						afficherMenu = false;
						afficherOption = true;
						sonMe = true;
					}
				}
				else if (afficherOption) {
					//Gestion dans le menu.
					if (position_cursor == 1) { // volume +
						sonMe = true;
						if (volume < 100) volume += 5;
					}
					else if (position_cursor == 2) { //Volume -
						sonMe = true;
						if (volume > 0) volume -= 5;
					}
					else if (position_cursor == 3) { //Commandes
						sonMe = true;
						afficherOption = false;
						afficherCommande = true;
					}
				}
			}
			else if (incomingData[0] == 'C') { //on appuie sur le bouton B.
				if (!afficherMenu && !afficherHistoire && !afficherMenu && !afficherOption && !afficherCommande) {
					if (pause) {
						pause = false;
					}
					else {
						pause = true;
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, texture[12]);
						glBegin(GL_QUADS);
						glColor3d(1.0, 1.0, 1.0);
						glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
						glTexCoord2f(1.0f, 1.0f); glVertex2d(17, 0);
						glTexCoord2f(1.0f, 0.0f); glVertex2d(17, 13);
						glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 13);
						glEnd();
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_BLEND);
					}
				}
				else if (afficherMenu) {
					glutDestroyWindow(1);
					exit(0);
				}
				else if (afficherCommande) { //retour
					afficherCommande = false;
					afficherOption = true;
				}
				else if (afficherOption) { //retour
					afficherMenu = true;
					afficherOption = false;
				}
			}

			//JOYSTICK	
			if (incomingData[0] == 'R') { // joystick qui n'est pas en mouvement.
				gauche = false;
				droite = false;
				haut = false;
				bas = false;
				enMouvement = false;
			}

			if (afficherMenu || afficherOption) {
				//Bouge le curseur dans le menu.
				if (incomingData[0] == 'H') { //joystick vers le haut
					if (position_cursor_y > 0.63) {
						position_cursor_y -= 0.07;
						position_cursor -= 1;
					}
				}

				if (incomingData[0] == 'X') { // joystick vers le bas
					if (position_cursor_y < 0.7) {
						position_cursor_y += 0.07;
						position_cursor += 1;
					}
				}
			}
			else {
				if (!pause) {
					if (incomingData[0] == 'X') { //bas.
						bas = true;
						haut = false;
						gauche = false;
						droite = false;
					}
					else if (incomingData[0] == 'H') { //haut.
						haut = true;
						bas = false;
						gauche = false;
						droite = false;
					}
					else if (incomingData[0] == 'G') { //gauche.
						gauche = true;
						droite = false;
						bas = false;
						haut = false;
					}
					else if (incomingData[0] == 'D') { // droite.
						droite = true;
						bas = false;
						haut = false;
						gauche = false;
					}
				}
			}
		}

		//LED VERTE.
		if (!afficherMenu && !afficherHistoire) {
			allumerLedVerte = true;
		}
		else allumerLedVerte = false;
		
		if (allumerLedVerte) {
			SP->WriteData("v", 1);//allume la led 5 (verte).
		}
		else {
			SP->WriteData("b", 1);//eteint la led 5 (verte).
		}
		//LED RGB.
		if (explosionEnCours) {
			SP->WriteData("e", 1);
		}
		else {
			SP->WriteData("d", 1);
		}
	}
	glFlush();
	glutTimerFunc(200, TraitementArduino, 0);
}

void main() {
	srand((unsigned)time(0)); //initialisation des nombres aleatoires.
	tableEnnemis();//on remplit le tableau d'ennemis.

	// Gestion de la fen�tre
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(HAUTEUR_FENETRE, LARGEUR_FENETRE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("Bomberman");

	// Gestion des evenements
	glutDisplayFunc(LabyAffichage);
	glutReshapeFunc(LabyRedim);
	glutKeyboardFunc(TraitementClavierASCII);
	glutSpecialFunc(TraitementClavier);
	glutSpecialUpFunc(TraitementAucuneTouche);
	glutKeyboardUpFunc(TraitementAucuneToucheASCII);
	glutTimerFunc(50, TestDirection, 0);
	glutTimerFunc(1000, LabyTimerExplosion, 0);
	glutTimerFunc(500, LabyTimerEnnemi, 0);
	glutTimerFunc(100, transitionHistoire, 0);
	glutTimerFunc(100, TraitementArduino, 0);

	// Gestion des textures
	/* 0 */  LoadGLTextures("images/Test.png");
	/* 1 */  LoadGLTextures("images/Niveaux.png");
	/* 2 */  LoadGLTextures("images/Bombes&Bonus.png");
	/* 3 */  LoadGLTextures("images/Bomberman.png");
	/* 4 */  LoadGLTextures("images/EnnemiAllerRetour.png");
	/* 5 */  LoadGLTextures("images/EnnemiAleatoire.png");
	/* 6 */  LoadGLTextures("images/Sortie.png");
	/* 7 */  LoadGLTextures("images/Score&Vie.png");
	/* 8 */  LoadGLTextures("images/Menu.png");
	/* 9 */  LoadGLTextures("images/TeteMenu.png");
	/* 10 */ LoadGLTextures("images/Bomberdeath.png");
	/* 11 */ LoadGLTextures("images/GameOver.png");
	/* 12 */ LoadGLTextures("images/Pause.png");
	/* 13 */ LoadGLTextures("images/Intro1.png");
	/* 14 */ LoadGLTextures("images/Intro2.png");
	/* 15 */ LoadGLTextures("images/Intro3.png");
	/* 16 */ LoadGLTextures("images/Intro4.png");
	/* 17 */ LoadGLTextures("images/Intro5.png");
	/* 18 */ LoadGLTextures("images/Intro6.png");
	/* 19 */ LoadGLTextures("images/Bombes&Bonus2.png");
	/* 20 */ LoadGLTextures("images/Bombes&Bonus3.png");
	/* 21 */ LoadGLTextures("images/Bombes&Bonus4.png");
	/* 22 */ LoadGLTextures("images/Options.png");
	/* 23 */ LoadGLTextures("images/Commandes.png");
	/* 24 */ LoadGLTextures("images/MurExplo.png");
	/* 25 */ LoadGLTextures("images/Bomberman2.png");
	/* 26 */ LoadGLTextures("images/VictoireJ1.png");
	/* 27 */ LoadGLTextures("images/VictoireJ2.png");
	/* 28 */ LoadGLTextures("images/Victoire.png");
	/* 29 */ LoadGLTextures("images/Egalite.png");

	// Gestion des musiques
	musicIntro.openFromFile("Musiques/intro.wav");
	musicMenu.openFromFile("Musiques/menu.wav");
	musicZone1.openFromFile("Musiques/zone1.wav");
	musicZone2.openFromFile("Musiques/zone2.wav");
	musicZone3.openFromFile("Musiques/zone3.wav");
	musicDuel.openFromFile("Musiques/duel.wav");
	// Gestion des sons
	sonBombes.openFromFile("Musiques/bombe.wav");
	sonExplo.openFromFile("Musiques/explo.wav");
	sonBonus.openFromFile("Musiques/bonus.wav");
	sonMort.openFromFile("Musiques/mort.wav");
	sonMenu.openFromFile("Musiques/toucheMenu.wav");
	sonMonstre.openFromFile("Musiques/monstre.wav");
	sonNiveau.openFromFile("Musiques/changerNiveau.wav");

	// Integration des musiques dans un tableau
	tableMusic.push_back(&musicIntro);
	tableMusic.push_back(&musicMenu);
	tableMusic.push_back(&musicZone1);
	tableMusic.push_back(&musicZone2);
	tableMusic.push_back(&musicZone3);
	tableMusic.push_back(&musicDuel);
	//Integration des sons dans un tableau
	tableMusic.push_back(&sonBombes);
	tableMusic.push_back(&sonExplo);
	tableMusic.push_back(&sonBonus);
	tableMusic.push_back(&sonMort);
	tableMusic.push_back(&sonMenu);
	tableMusic.push_back(&sonMonstre);
	tableMusic.push_back(&sonNiveau);

	glutTimerFunc(50, PlayMusic, 0);

	glutMainLoop();
}