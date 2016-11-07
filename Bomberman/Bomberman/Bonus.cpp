#include "Bonus.h"
#include "Bomberman.h"
#include <vector>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Animation.h"

using namespace std;

extern vector<GLuint> texture;
extern Bomberman bomberman;
extern int valueBonus;
extern int score;

float coordBonus[5] = { 0.0f, 0.25f, 0.5f, 0.75f, 1.0f };

Bonus::Bonus(int x, int y,int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	visible = false;
	utiliser = false;
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
bool Bonus::getUtiliser()
{
	return utiliser;
}
void Bonus::setVisible(bool valeur)
{
	visible = valeur;
}

void Bonus::setUtiliser(bool utiliser)
{
	this->utiliser = utiliser;
}

void Bonus::ramasser()
{
	switch (type) {
		//type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
	case 1:
		if(bomberman.getNbBombe() <= 8) bomberman.setNbBombe(bomberman.getNbBombe() + 1);
		score += 50;
		break;
	case 2:
		if (bomberman.getPorteeBombe() <= 8) bomberman.setPorteeBombe(bomberman.getPorteeBombe() + 1);
		score += 50;
		break;
	case 3:
		if (bomberman.getVitesseDeplacement() <= 0.125f) bomberman.setVitesseDeplacement(bomberman.getVitesseDeplacement() + 0.025f);
		score += 50;
		break;
	}

	visible = false;
	utiliser = true;
}

void Bonus::dessiner()
{
	switch (type) {//type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
	case 1 :
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(coordBonus[1 + valueBonus], 0.375f); glVertex2d(x + 1, y + 1);
		glTexCoord2f(coordBonus[1 + valueBonus], 0.5f);  glVertex2d(x + 1, y);
		glTexCoord2f(coordBonus[0 + valueBonus], 0.5f);  glVertex2d(x, y);
		glTexCoord2f(coordBonus[0 + valueBonus], 0.375f); glVertex2d(x, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		break;
	case 2 :
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(coordBonus[1 + valueBonus], 0.25f); glVertex2d(x + 1, y + 1);
		glTexCoord2f(coordBonus[1 + valueBonus], 0.375f);  glVertex2d(x + 1, y);
		glTexCoord2f(coordBonus[0 + valueBonus], 0.375f);  glVertex2d(x, y);
		glTexCoord2f(coordBonus[0 + valueBonus], 0.25f); glVertex2d(x, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		break;
	case 3 :
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glColor3d(1.0, 1.0, 1.0);
		glTexCoord2f(coordBonus[1 + valueBonus], 0.125f); glVertex2d(x + 1, y + 1);
		glTexCoord2f(coordBonus[1 + valueBonus], 0.25f);  glVertex2d(x + 1, y);
		glTexCoord2f(coordBonus[0 + valueBonus], 0.25f);  glVertex2d(x, y);
		glTexCoord2f(coordBonus[0 + valueBonus], 0.125f); glVertex2d(x, y + 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		break;
	}
	
}
