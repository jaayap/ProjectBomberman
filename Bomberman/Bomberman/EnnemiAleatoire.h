#pragma once
#include "Personnage.h"

class EnnemiAleatoire : public Personnage
{
	int deplacement= 1;
	int deplacement_precedent = 1;
public:
	EnnemiAleatoire(int xDepart, int yDepart);
	~EnnemiAleatoire();
	void dessiner();
	void calculDeplacement();
	void Deplacer();
	void retour(int, int);
};

