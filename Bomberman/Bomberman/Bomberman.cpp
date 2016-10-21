#include <vector>
#include <iostream>
#include <chrono>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Bomberman.h"
#include "Niveau.h"
//#include "Main.cpp"

using namespace std;

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
	bombes[nb].exploser();
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
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x + offsetX + 1, y + offsetY + 1);//top left
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x + offsetX, y + offsetY + 1);//bottom left	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x + offsetX, y + offsetY);//bottom right	
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x + offsetX + 1, y + offsetY);	//top right	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}