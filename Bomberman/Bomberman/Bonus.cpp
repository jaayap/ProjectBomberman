#include "Bonus.h"
#include "Bomberman.h"
#include <vector>
#include "GL/glut.h"
#include "SOIL/SOIL.h"

using namespace std;

extern vector<GLuint> texture;
extern Bomberman bomberman;

Bonus::Bonus()
{
}


Bonus::~Bonus()
{
}

void Bonus::ramasser()
{
	switch (type) {
		//type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
	case 1 : 
		//bomberman.setNbBombe(bomberman.getNbBombe + 1)
		break;
	case 2 : 
		break;
	case 3 : 
		break;
	}
}

void Bonus::dessiner()
{
}
