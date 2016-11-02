#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <time.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include "Niveau.h"
#include "Personnage.h"
#include "Bomberman.h"
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"
#include "Animation.h"


using namespace std;

int HAUTEUR_FENETRE = 1046;
int LARGEUR_FENETRE = 900;

int score = 0;
int vie = 3;

bool enMouvement = false;
bool haut = false, bas = false, gauche = false, droite = false;
bool ennemi1V = false, ennemi2V = false, ennemi3V = false;
bool victoire = false;

vector<GLuint>	texture; // tableau qui contient nos textures
vector<EnnemiAleatoire> TableEA;
vector<EnnemiAllerRetour> TableEAR;

Niveau niveau;
Bomberman bomberman(3,3);
EnnemiAleatoire ennemi1(3, 4);
EnnemiAllerRetour ennemi2(5, 3, 1, false);
EnnemiAllerRetour ennemi3(8, 5, 4, false);

// Déclarations de fonctions
void LabyAffichage();
void LabyRedim(int width, int height);
void TraitementClavier(int key, int x, int y);
void TraitementClavierASCII(unsigned char key, int x, int y);
int  LoadGLTextures(string name);


void LabyAffichage() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	niveau.dessinerNiveau();

	//Test colision et bonus
	//bomberman.collisionEnnemi();
	bomberman.ramasserBonus();

	//Affichage des personnages
	if (bomberman.vivant) bomberman.dessiner();
	if (ennemi1.vivant) ennemi1.dessiner();
	if (ennemi2.vivant) ennemi2.dessiner();
	if (ennemi3.vivant) ennemi3.dessiner();

	for (int i = 0; i < size(bomberman.bombes); i++) {
		
		if (bomberman.bombes[i].explosion) {
			cout << "explosion a dessiner" << i <<endl;
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
}

void TraitementClavierASCII(unsigned char key, int x, int y) {
	glutPostRedisplay();
	if (key == 27) {// Escape key
		glutDestroyWindow(1);
		exit(0);
	}

	if (key == 66 || key == 98) { // touche B
		bomberman.lancerBombe();
	}
	glFlush();
}


void LabyTimerExplosion(int z) {

	for (int i = 0; i < size(bomberman.bombes); i++) {
		
		if (bomberman.bombes[i].posee) {
			bomberman.bombes[i].Timer++;
			//Explosion au bout de 5 secondes
			if (bomberman.bombes[i].Timer > 10 && !bomberman.bombes[i].explosion) {//creer explosion
				bomberman.bombes[i].explosion = true;
				bomberman.declancherExplosion(i);	
			}

			//500 ms plus tard
			if (bomberman.bombes[i].Timer > 11) {//effacer explosion		
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

				
			}
			glutPostRedisplay();//important !
		}
	}

	glutTimerFunc(500, LabyTimerExplosion, 0); 
}

void LabyTimerEnnemi(int z) {
	ennemi1.calculDeplacement();
	ennemi2.calculDeplacement();
	ennemi3.calculDeplacement();
	ennemi1.dessiner();
	ennemi1.dessiner();
	ennemi3.dessiner();

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
}

void detecteEnnemis(int z) {
	if (size(TableEA) == 0 && size(TableEAR) == 0) {
		victoire = true;
		return;
	}

	else {
		if (!ennemi1.vivant && !ennemi1V) {
			TableEA.pop_back();
			ennemi1V = true;
			glutTimerFunc(100, detecteEnnemis, 0);
			return;
		}
		if (!ennemi2.vivant && !ennemi2V) {
			TableEAR.pop_back();
			ennemi2V = true;
			glutTimerFunc(100, detecteEnnemis, 0);
			return;
		}
		if (!ennemi3.vivant && !ennemi3V) {
			TableEAR.pop_back();
			ennemi3V = true;
			glutTimerFunc(100, detecteEnnemis, 0);
			return;
		}
		glutTimerFunc(100, detecteEnnemis, 0);
	}
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
	glutTimerFunc(100, detecteEnnemis, 0);

	// Gestion des textures
	/* 0 */ LoadGLTextures("images/Test.png");
	/* 1 */ LoadGLTextures("images/Niveaux.png");
	/* 2 */ LoadGLTextures("images/Bombes&Bonus.png");
	/* 3 */ LoadGLTextures("images/Bomberman.png");
	/* 4 */ LoadGLTextures("images/EnnemiAllerRetour.png");
	/* 5 */ LoadGLTextures("images/EnnemiAleatoire.png");
	/* 6 */ LoadGLTextures("images/Sortie.png");
	/* 7 */ LoadGLTextures("images/Score&Vie.png");

	glutMainLoop();
}