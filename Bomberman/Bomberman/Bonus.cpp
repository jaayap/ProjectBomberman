#include "Bonus.h"
#include "Bomberman.h"
#include <vector>
#include "GL/glut.h"
#include "SOIL/SOIL.h"

using namespace std;

extern vector<GLuint> texture;
extern Bomberman bomberman;

Bonus::Bonus(int x, int y,int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	visible = false;
}


Bonus::~Bonus()
{
}

int Bonus::getX()
{
	return x;
}

int Bonus::getY()
{
	return y;
}

bool Bonus::getVisible() {
	return visible;
}
void Bonus::setVisible(bool valeur)
{
	visible = valeur;
}

void Bonus::ramasser()
{
	switch (type) {
		//type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
	case 1:
		bomberman.setNbBombe(bomberman.getNbBombe() + 1);
		break;
	case 2:
		break;
	case 3:
		bomberman.setVitesseDeplacement(bomberman.getVitesseDeplacement() + 1);
		break;
	}
}

void Bonus::dessiner()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.25f, 0.875f); glVertex2d(x + 1, y + 1);
	glTexCoord2f(0.5f, 0.875f);  glVertex2d(x + 1, y );
	glTexCoord2f(0.25f, 0.75f);  glVertex2d(x, y);
	glTexCoord2f(0.5f, 0.75f); glVertex2d(x, y + 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
