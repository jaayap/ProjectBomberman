#include "Animation.h"
#include <iostream>
#include <string>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>

using namespace std;

int spriteBombe = 0, valueBombe = 0;
int spriteExplo = 0, valueExplo = 0;
int spriteBomberman = 0, valueBomberman = 0;
int spriteEnnemi1 = 0, valueEnnemi1 = 0;
int spriteEnnemi2 = 0, valueEnnemi2 = 0;


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

void BombermanAnimation(int x) {
	switch (spriteBomberman)
	{
	case(0):
		spriteBomberman = 1;
		valueBomberman = 0;
		break;
	case(1):
		spriteBomberman = 2;
		valueBomberman = 1;
		break;
	case(2):
		spriteBomberman = 3;
		valueBomberman = 2;
		break;
	case(3):
		spriteBomberman = 4;
		valueBomberman = 3;
		break;
	case(4):
		spriteBomberman = 5;
		valueBomberman = 4;
		break;
	case(5):
		spriteBomberman = 6;
		valueBomberman = 5;
		break;
	case(6):
		spriteBomberman = 7;
		valueBomberman = 6;
		break;
	case(7):
		spriteBomberman = 0;
		valueBomberman = 7;
		break;
	}

	glutTimerFunc(100, BombermanAnimation, 0);
}

void ennemi1Animation(int x) {
	switch (spriteEnnemi1)
	{
	case(0):
		spriteEnnemi1 = 1;
		valueEnnemi1 = 0;
		break;
	case(1):
		spriteEnnemi1 = 2;
		valueEnnemi1 = 2;
		break;
	case(2):
		spriteEnnemi1 = 3;
		valueEnnemi1 = 4;
		break;
	case(3):
		spriteEnnemi1 = 0;
		valueEnnemi1 = 6;
		break;
	}

	glutTimerFunc(20, ennemi1Animation, 0);
}

void ennemi2Animation(int x) {
	switch (spriteEnnemi2)
	{
	case(0):
		spriteEnnemi2 = 1;
		valueEnnemi2 = 0;
		break;
	case(1):
		spriteEnnemi2 = 2;
		valueEnnemi2 = 1;
		break;
	case(2):
		spriteEnnemi2 = 3;
		valueEnnemi2 = 2;
		break;
	case(3):
		spriteEnnemi2 = 4;
		valueEnnemi2 = 3;
		break;
	case(4):
		spriteEnnemi2 = 5;
		valueEnnemi2 = 4;
		break;
	case(5):
		spriteEnnemi2 = 6;
		valueEnnemi2 = 5;
		break;
	case(6):
		spriteEnnemi2 = 7;
		valueEnnemi2 = 6;
		break;
	case(7):
		spriteEnnemi2 = 8;
		valueEnnemi2 = 7;
		break;
	case(8):
		spriteEnnemi2 = 9;
		valueEnnemi2 = 8;
		break;
	case(9):
		spriteEnnemi2 = 10;
		valueEnnemi2 = 9;
		break;
	case(10):
		spriteEnnemi2 = 11;
		valueEnnemi2 = 10;
		break;
	case(11):
		spriteEnnemi2 = 12;
		valueEnnemi2 = 11;
		break;
	case(12):
		spriteEnnemi2 = 13;
		valueEnnemi2 = 12;
		break;
	case(13):
		spriteEnnemi2 = 14;
		valueEnnemi2 = 13;
		break;
	case(14):
		spriteEnnemi2 = 15;
		valueEnnemi2 = 14;
		break;
	case(15):
		spriteEnnemi2 = 0;
		valueEnnemi2 = 15;
		break;
	}

	glutTimerFunc(50, ennemi2Animation, 0);
}


Animation::Animation()
{
	glutTimerFunc(200, bombeAnimation, 0);
	glutTimerFunc(100, exploAnimation, 0);
	glutTimerFunc(100, BombermanAnimation, 0);
	glutTimerFunc(20, ennemi1Animation, 0);
	glutTimerFunc(50, ennemi1Animation, 0);
}


Animation::~Animation()
{
}