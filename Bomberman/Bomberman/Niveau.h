#pragma once
#include <vector>
#include <iostream>
#include "Bonus.h"
class Niveau
{
	char matrice[13][17]; //matrice representant le niveau.
	int nbColonnes;
	int nbLignes;
	bool PlacerBonus = false;// true : bonus place dans le niveau, false : bonus non initialiser.
public:std::vector<Bonus> bonusTab;

public:
	Niveau();
	~Niveau();
	void initialiserMatrice();
	void dessinerNiveau();
	bool caseLibre(int x,int y);
	bool caseMurDestructible(int x, int y);
	bool caseLibreBombe(int x, int y);
	void modifierCase(int x, int y, char valeur);
	char getCase(int x, int y);
	void definirBonus(int i, int j);
};
