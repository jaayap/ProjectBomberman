#pragma once
#include <vector>
#include <iostream>
#include "Bombe.h"
#include "Personnage.h"


class Bomberman : public Personnage
{
	int score;
	int nb_bombes = 1;
public:std::vector<Bombe> bombes;

public:
	Bomberman(int xDepart, int yDepart);
	~Bomberman();
	void setNbBombe(int nb);
	void lancerBombe();
	void declancherExplosion(int);
	void eraseExplosion(int);
	void collisionEnnemi();
	void dessiner();
	
};

