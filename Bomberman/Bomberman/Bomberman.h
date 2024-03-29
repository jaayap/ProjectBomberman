#pragma once
#include <vector>
#include <iostream>
#include "Bombe.h"
#include "Personnage.h"

//cette classe represente le joueur.
class Bomberman : public Personnage
{
	int score;
public:int nb_bombes = 1;
public:int portee_bombe = 3;
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
	void ramasserBonus(int);
	void retour(int);
	void dessiner();
	void dessiner2();

};

