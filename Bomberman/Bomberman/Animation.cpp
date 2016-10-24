#include "Animation.h"
#include <iostream>
#include <string>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>

using namespace std;

int spriteBombe = 0, valueBombe = 0;
int spriteExplo = 0, valueExplo = 0;
int spriteMur = 0, valueMur = 0;


void bombeAnimation(int x) {
	switch (spriteBombe)
	{
	case(0):
		spriteBombe = 1;
		valueBombe = 0;
		break;
	case(1):
		spriteBombe = 2;
		valueBombe = 2;
		break;
	case(2):
		spriteBombe = 3;
		valueBombe = 4;
		break;
	case(3):
		spriteBombe = 0;
		valueBombe = 2;
		break;
	}

	glutTimerFunc(200, bombeAnimation, 0);
}

void exploAnimation(int x) {
	switch (spriteExplo)
	{
	case(0):
		spriteExplo = 1;
		valueExplo = 0;
		break;
	case(1):
		spriteExplo = 2;
		valueExplo = 1;
		break;
	case(2):
		spriteExplo = 3;
		valueExplo = 2;
		break;
	case(3):
		spriteExplo = 0;
		valueExplo = 1;
		break;
	}

	glutTimerFunc(100, exploAnimation, 0);
}

void MurAnimation(int x) {

}


Animation::Animation()
{
	glutTimerFunc(100, bombeAnimation, 0);
	glutTimerFunc(100, exploAnimation, 0);
	glutTimerFunc(100, MurAnimation, 0);
}


Animation::~Animation()
{
}