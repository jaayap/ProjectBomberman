#pragma once
#include "Personnage.h"

class EnnemiAleatoire : public Personnage
{
	int deplacement= 1;
	int deplacement_precedent = 1;
	int xDep;
	int yDep;
public:
	EnnemiAleatoire(int xDepart, int yDepart);
	~EnnemiAleatoire();
	void dessiner();
	void calculDeplacement();
	void Deplacer();
	void retour();
};

