#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <time.h>
#include <vector>
#include <chrono>
#include <iostream>
#include "Niveau.h"
#include "Personnage.h"
#include "Bomberman.h"
#include "EnnemiAleatoire.h"
#include "EnnemiAllerRetour.h"

using namespace std;

int HAUTEUR_FENETRE = 1046;
int LARGEUR_FENETRE = 800;

vector<GLuint>	texture; // tableau qui contient nos textures

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


void LabyAffichage()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	//glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
	//glLoadIdentity();

	niveau.dessinerNiveau();
//	bomberman.collisionEnnemi();
	if (bomberman.vivant) bomberman.dessiner();
	if (ennemi1.vivant) ennemi1.dessiner();
	if (ennemi2.vivant) ennemi2.dessiner();
	if (ennemi3.vivant) ennemi3.dessiner();

	for (int i = 0; i < size(bomberman.bombes); i++) {
		if (bomberman.bombes[i].explosion) {
			bomberman.bombes[i].dessinerExplosion();
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

	if (key == GLUT_KEY_UP) {
		for (int i = 0; i < bomberman.getVitesseDeplacement(); i++) {
			bomberman.deplacementHaut();
		}
		
	}
	if (key == GLUT_KEY_DOWN) {
		for (int i = 0; i < bomberman.getVitesseDeplacement(); i++) {
			bomberman.deplacementBas();
		}
	}
	if (key == GLUT_KEY_LEFT) {
		for (int i = 0; i < bomberman.getVitesseDeplacement(); i++) {
			bomberman.deplacementGauche();
		}
	}
	if (key == GLUT_KEY_RIGHT) {
		for (int i = 0; i < bomberman.getVitesseDeplacement(); i++) {
			bomberman.deplacementDroite();
		}
	}

	glFlush();
}

void TraitementClavierASCII(unsigned char key, int x, int y)
{
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
	
			if (bomberman.bombes[i].Timer > 5 && !bomberman.bombes[i].explosion) {//creer explosion
				bomberman.declancherExplosion(i);
				bomberman.bombes[i].explosion = true;
			}

			if (bomberman.bombes[i].Timer > 7) {//effacer explosion		
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

	glutTimerFunc(1000, LabyTimerExplosion, 0); 
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

void main() {
	srand((unsigned)time(0));

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
	glutTimerFunc(1000, LabyTimerExplosion, 0);
	glutTimerFunc(500, LabyTimerEnnemi, 0);

	// Gestion des textures
	/* 0 */ LoadGLTextures("images/Test.png");
	/* 1 */ LoadGLTextures("images/Niveaux.png");
	/* 2 */ LoadGLTextures("images/Bombes&Bonus.png");
	/* 3 */ LoadGLTextures("images/Bomberman.png");
	/* 4 */ LoadGLTextures("images/EnnemiAllerRetour.png");
	/* 5 */ LoadGLTextures("images/EnnemiAleatoire.png");

	glutMainLoop();
}


