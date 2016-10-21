#include "Animation.h"
#include <iostream>
#include <string>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>

using namespace std;

float X1, X2, Y1, Y2;

int spriteBombe = 0;


Animation::Animation()
{
}


Animation::~Animation()
{
}

void bombeAnimation(int x) {
	switch (spriteBombe)
	{
	case(0):
		X1 = 0.25f;
		X2 = 0.0f;
		Y1 = 0.875f;
		Y2 = 1.0f;
		spriteBombe = 1;
		break;
	case(1):
		X1 = 0.5f;
		X2 = 0.25f;
		Y1 = 0.875f;
		Y2 = 1.0f;
		spriteBombe = 2;
		break;
	case(2):
		X1 = 0.75f;
		X2 = 0.5f;
		Y1 = 0.875f;
		Y2 = 1.0f;
		spriteBombe = 3;
		break;
	case(3):
		X1 = 0.5f;
		X2 = 0.25f;
		Y1 = 0.875f;
		Y2 = 1.0f;
		spriteBombe = 0;
		break;
	}

	glutTimerFunc(200, bombeAnimation, 0);
}