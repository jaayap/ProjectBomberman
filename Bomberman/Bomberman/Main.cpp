#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <time.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <String>
#include "Niveau.h"
#include "Personnage.h"
#include "Bomberman.h"
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"
#include "Animation.h"
#include "SFML/Audio.hpp"
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>

using namespace std;

int HAUTEUR_FENETRE = 1046;
int LARGEUR_FENETRE = 900;

int score = 0;
int vie = 3;
int numNiveau = 1;

bool enMouvement = false;
bool haut = false, bas = false, gauche = false, droite = false;
bool victoire = false;
bool afficherMenu = false;
float position_cursor_x = 0.25;
float position_cursor_y = 0.63;
int position_cursor = 1; // 1 : normal Game, 2 : Battle Game , 3 : Option
bool pause = false; //permet de mettre le jeu en pause

bool utiliserManette = false;
bool explosionEnCours = false;

bool gameOver = false;



vector<GLuint>	texture; // tableau qui contient nos textures
vector<EnnemiAleatoire> TableEA;
vector<EnnemiAllerRetour> TableEAR;

Niveau niveau;

//Joueur
Bomberman bomberman(3, 1);

//Declaration des ennemis

vector<Personnage*> ennemisTab;

EnnemiAleatoire ennemiTest(99, 99);
EnnemiAleatoire ennemi1(5, 9);
EnnemiAllerRetour ennemi2(5, 3, 1, false);
EnnemiAllerRetour ennemi3(8, 5, 4, false);

// Sons
vector<sf::Music*> tableMusic;
sf::Music musicIntro;
sf::Music musicMenu;
sf::Music musicZone1;
int volume = 100;

// Intro
bool afficherHistoire = true;
bool incrAlpha = true;
float alphaImg = 1.0f;
int numImage = 13;


//Arduino
Serial* SP = new Serial("COM3");    // adjust as needed - port com
char incomingData[256] = "";		// don't forget to pre-allocate memory
int dataLength = 256;
int readResult = 0;


// Déclarations de fonctions
void LabyAffichage();
void LabyRedim(int width, int height);
void TraitementClavier(int key, int x, int y);
void TraitementClavierASCII(unsigned char key, int x, int y);
void TraitementArduino(int z);
int  LoadGLTextures(string name);

void LabyAffichage() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	if (afficherHistoire) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture Background Histoire
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
	else if (afficherMenu) {
		glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
		glLoadIdentity();
		// Texture Background Menu
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
		// Texture du curseur
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
	else {

		niveau.dessinerNiveau();

		//Test colision et bonus
		bomberman.collisionEnnemi();
		bomberman.ramasserBonus();

		//Affichage des personnages
		bomberman.dessiner();
		if (size(ennemisTab) > 1) {
			for (int i = 0; i < size(ennemisTab); i++) {
				if (ennemisTab[i]->vivant) {
					ennemisTab[i]->dessiner();
				}
				else {
					ennemisTab.erase(ennemisTab.begin() + i);
					score += 100;
				}
			}
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

		// Texture score & vie
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

		// Affichage du score
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

		// Affichage de la vie
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
			//Affichage de l'ecran pause
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
	gluOrtho2D(0.0, (double)17, (double)13, 0.0); // nbColonnes /nbLignes
	HAUTEUR_FENETRE = height;
	LARGEUR_FENETRE = width;
}

void TraitementClavier(int key, int x, int y)
{
	glutPostRedisplay();

	if (afficherMenu) {
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


void TestDirection(int z) {

	float test = bomberman.getVitesseDeplacement() / 2.00;

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
	glutTimerFunc(25, TestDirection, 0);
}


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

	//TEST
	if (key == GLUT_KEY_F1) {
		numNiveau = 1;
	}
	//TEST
	if (key == GLUT_KEY_F2) {
		numNiveau = 2;
	}
	//TEST
	if (key == GLUT_KEY_F3) {
		numNiveau = 3;
	}
}

void TraitementClavierASCII(unsigned char key, int x, int y) {
	glutPostRedisplay();
	if (afficherHistoire) {
		if (key == 10 || key == 13) { // Touche entree
			afficherHistoire = false;
			afficherMenu = true;
		}
	}
	else if (afficherMenu && !afficherHistoire) {
		if (key == 10 || key == 13) { // Touche entree
			if (position_cursor == 1) { // on lance le niveau
				afficherMenu = false;
			}
		}
	}
	else {
		if ((key == 66 || key == 98) && !pause) { // touche B
			bomberman.lancerBombe();
		}
		//mettre en pause le jeu
		if (key == 80 || key == 112) { // touche P
			if (pause) pause = false;
			else pause = true;
		}

	}

	if (key == 27) {// Escape key
		glutDestroyWindow(1);
		exit(0);
	}

	glFlush();
}


void LabyTimerExplosion(int z) {

	for (int i = 0; i < size(bomberman.bombes); i++) {

		if (bomberman.bombes[i].posee) {
			explosionEnCours = true;
			if (!pause) bomberman.bombes[i].Timer++;
			//Explosion au bout de 5 secondes
			if (bomberman.bombes[i].Timer > 5 && !bomberman.bombes[i].explosion) {//creer explosion
				bomberman.bombes[i].explosion = true;
				bomberman.declancherExplosion(i);

			}

			//500 ms plus tard
			if (bomberman.bombes[i].Timer > 6) {//effacer explosion		
												// Efface la trace de l'explosion et réinitialise les booléens
				bomberman.bombes[i].explosion = false;

				bomberman.eraseExplosion(i);

				//on efface les murs détruits
				for (int i = 0; i < 13; i++) {
					for (int j = 0; j < 17; j++) {
						if (niveau.getCase(i, j) == '3') {
							niveau.modifierCase(i, j, '0');
						}
					}
				}

				explosionEnCours = false;

			}
			glutPostRedisplay();//important !
		}
	}

	glutTimerFunc(500, LabyTimerExplosion, 0);
}

void LabyTimerEnnemi(int z) {
	if (!pause && size(ennemisTab) > 0) {
		for (int i = 0; i < size(ennemisTab); i++) {
			ennemisTab[i]->calculDeplacement();
		}
	}
	glutTimerFunc(30, LabyTimerEnnemi, 0);
}


// Chargement des textures
int LoadGLTextures(string name) //Charge l'image et la convertit en texture
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

	return true;  // Return Success
}

void tableEnnemis() {
	TableEA.push_back(ennemi1);
	TableEAR.push_back(ennemi2);
	TableEAR.push_back(ennemi3);

	ennemisTab.push_back(&ennemiTest);
	ennemisTab.push_back(&ennemi1);
	ennemisTab.push_back(&ennemi2);
	ennemisTab.push_back(&ennemi3);
}

void PlayMusic(int z) {

	if (afficherHistoire) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicIntro) {
				if (musicIntro.getStatus() == sf::Sound::Status::Playing) {
					glutTimerFunc(50, PlayMusic, 0);
					return;
				}
				else {
					cout << "Musique Intro" << endl;
					musicIntro.setVolume(volume);
					musicIntro.play();
					musicIntro.setLoop(true);
				}
			}
		}
	}
	else if (afficherMenu && !afficherHistoire) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicMenu) {
				if (musicMenu.getStatus() == sf::Sound::Status::Playing) {
					glutTimerFunc(50, PlayMusic, 0);
					return;
				}
				else {
					cout << "Musique Menu" << endl;
					volume = 100;
					musicMenu.setVolume(volume);
					musicMenu.play();
					musicMenu.setLoop(true);
				}
			}
			else {
				musicZone1.stop();
				musicZone1.setLoop(false);
				musicIntro.stop();
				musicIntro.setLoop(false);
				// utiliser le tableau pour stopper TOUTES les autres musiques
			}
		}
	}
	else if (!afficherMenu && !afficherHistoire) {
		for (int i = 0; i < size(tableMusic); i++) {
			if (tableMusic[i] == &musicZone1) {
				if (musicZone1.getStatus() == sf::Sound::Status::Playing) {
					glutTimerFunc(50, PlayMusic, 0);
					return;
				}
				else {
					cout << "Musique Zone 1" << endl;
					musicZone1.setVolume(volume);
					musicZone1.play();
					musicZone1.setLoop(true);
				}
			}
			else {
				musicMenu.stop();
				musicMenu.setLoop(false);
				// utiliser le tableau pour stopper TOUTES les autres musiques
			}
		}
	}

	// PAUSE
	glutTimerFunc(50, PlayMusic, 0);

}

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


void TraitementArduino(int z) {

	if (SP->IsConnected() && utiliserManette)
	{
		readResult = SP->ReadData(incomingData, dataLength);//on lit les infos de l'arduino

		if (readResult != -1) {
			//BOUTONS
			if (incomingData[0] == 'A') { //on appuie sur le bouton	
				if (!pause && !afficherHistoire && !afficherMenu) { // touche B
																	//printf("\n BombeButton");
					bomberman.lancerBombe();
				}
				else  if (afficherHistoire) {
					afficherHistoire = false;
					afficherMenu = true;
				}
				else if (afficherMenu && !afficherHistoire) {
					if (position_cursor == 1) { //avanture
						afficherMenu = false;
					}
					else if (position_cursor == 2) { //versus

					}
					else if (position_cursor == 3) {//option

					}
				}
			}
			else if (incomingData[0] == 'B') { //on appuie sur le bouton
				printf("\n BonusButton");
			}
			else if (incomingData[0] == 'C') { //on appuie sur le bouton
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

			if (incomingData[0] == 'R') {
				gauche = false;
				droite = false;
				haut = false;
				bas = false;
				enMouvement = false;
			}

			//JOYSTICK	
			if (afficherMenu) {
				//Bouge le curseur 
				if (incomingData[0] == 'H') {
					if (position_cursor_y > 0.63) {
						position_cursor_y -= 0.07;
						position_cursor -= 1;
					}
				}

				if (incomingData[0] == 'X') {
					if (position_cursor_y < 0.7) {
						position_cursor_y += 0.07;
						position_cursor += 1;
					}
				}
			}
			else {
				if (!pause) {
					if (incomingData[0] == 'X') {
						bas = true;
						haut = false;
						gauche = false;
						droite = false;
					}
					else if (incomingData[0] == 'H') {
						haut = true;
						bas = false;
						gauche = false;
						droite = false;
					}
					else if (incomingData[0] == 'G') {
						gauche = true;
						droite = false;
						bas = false;
						haut = false;
					}
					else if (incomingData[0] == 'D') {
						droite = true;
						bas = false;
						haut = false;
						gauche = false;
					}
				}
			}
		}

		//LED VERTE
		if (!afficherMenu && !afficherHistoire) {
			SP->WriteData("v", 1);//allume la led 5 (verte)
		}
		else SP->WriteData("b", 1);//eteint la led 5 (verte)
								   //LED RGB
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
	srand((unsigned)time(0));

	tableEnnemis();

	// Gestion de la fenêtre
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(HAUTEUR_FENETRE, LARGEUR_FENETRE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("Bomberman");

	// Gestion des événements
	glutDisplayFunc(LabyAffichage);
	glutReshapeFunc(LabyRedim);
	glutKeyboardFunc(TraitementClavierASCII);
	glutSpecialFunc(TraitementClavier);
	glutSpecialUpFunc(TraitementAucuneTouche);
	glutTimerFunc(50, TestDirection, 0);
	glutTimerFunc(1000, LabyTimerExplosion, 0);
	glutTimerFunc(500, LabyTimerEnnemi, 0);
	glutTimerFunc(100, transitionHistoire, 0);
	glutTimerFunc(100, TraitementArduino, 0);

	// Gestion des textures
	/* 0 */ LoadGLTextures("images/Test.png");
	/* 1 */ LoadGLTextures("images/Niveaux.png");
	/* 2 */ LoadGLTextures("images/Bombes&Bonus.png");
	/* 3 */ LoadGLTextures("images/Bomberman.png");
	/* 4 */ LoadGLTextures("images/EnnemiAllerRetour.png");
	/* 5 */ LoadGLTextures("images/EnnemiAleatoire.png");
	/* 6 */ LoadGLTextures("images/Sortie.png");
	/* 7 */ LoadGLTextures("images/Score&Vie.png");
	/* 8 */ LoadGLTextures("images/Menu.png");
	/* 9 */ LoadGLTextures("images/TeteMenu.png");
	/* 10 */ LoadGLTextures("images/Bomberdeath.png");
	/* 11 */ LoadGLTextures("images/GameOver.png");
	/* 12 */ LoadGLTextures("images/Pause.png");
	/* 13 */ LoadGLTextures("images/Intro1.png");
	/* 14 */ LoadGLTextures("images/Intro2.png");
	/* 15 */ LoadGLTextures("images/Intro3.png");
	/* 16 */ LoadGLTextures("images/Intro4.png");
	/* 17 */ LoadGLTextures("images/Intro5.png");
	/* 18 */ LoadGLTextures("images/Intro6.png");

	// Gestion des sons
	musicIntro.openFromFile("Musiques/intro.wav");
	musicMenu.openFromFile("Musiques/menu.wav");
	musicZone1.openFromFile("Musiques/zone1.wav");

	// Intégration des musiques dans un tableau
	tableMusic.push_back(&musicIntro);
	tableMusic.push_back(&musicMenu);
	tableMusic.push_back(&musicZone1);

	glutTimerFunc(50, PlayMusic, 0);

	glutMainLoop();
}