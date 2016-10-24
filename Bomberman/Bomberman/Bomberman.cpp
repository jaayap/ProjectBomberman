#include <vector>
#include <iostream>
#include <chrono>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Bomberman.h"
#include "Niveau.h"
#include "Animation.h"
//#include "Main.cpp"

using namespace std;

float coordBomb[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };

extern int valueBomberman;

extern vector<GLuint> texture;
extern Niveau niveau;

Bomberman::Bomberman(int xDepart,int  yDepart) : Personnage(x,y)
{
	this->x = xDepart;
	this->y = yDepart;
	this->vivant = true;
}


Bomberman::~Bomberman()
{
}
//Setter
void Bomberman::setNbBombe(int nb) {
	this->nb_bombes = nb;
}


void Bomberman::lancerBombe() {

	if (nb_bombes > 0) {
		niveau.modifierCase(y, x, '8');
		
		Bombe bombe = Bombe(x, y);
		bombe.posee = true;

		bombes.push_back(bombe);
		nb_bombes--;
	}	
}

void Bomberman::declancherExplosion(int nb) {
	//bombes[nb].exploser();
	setNbBombe(1);
}

void Bomberman::eraseExplosion(int nb) {
	bombes[nb].effacerExplosion();
	bombes.erase(bombes.begin() + nb);
}

void Bomberman::dessiner() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(coordBomb[0 + valueBomberman], coordBomb[6]); glVertex2d(x + offsetX + 1, y + offsetY + 1);
	glTexCoord2f(coordBomb[1 + valueBomberman], coordBomb[6]); glVertex2d(x + offsetX, y + offsetY + 1);
	glTexCoord2f(coordBomb[1 + valueBomberman], coordBomb[8]); glVertex2d(x + offsetX, y + offsetY - 0.5);
	glTexCoord2f(coordBomb[0 + valueBomberman], coordBomb[8]); glVertex2d(x + offsetX + 1, y + offsetY - 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}