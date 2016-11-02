#pragma once
#include <vector>
#include <iostream>
#include "Bombe.h"
#include "Personnage.h"


class Bomberman : public Personnage
{
	int score;
	int nb_bombes = 1;
	int portee_bombe = 3;
public:std::vector<Bombe> bombes;

public:
	Bomberman(int xDepart, int yDepart);
	~Bomberman();
	int getNbBombe();
	int getPorteeBombe();
	void setNbBombe(int nb);
	void setPorteeBombe(int portee);
	void lancerBombe();
	void declancherExplosion(int);
	void eraseExplosion(int);
	void collisionEnnemi();
	void ramasserBonus();
	void retour();
	void dessiner();

};

