#pragma once
#include "Personnage.h"

class EnnemiAllerRetour : public Personnage
{
	int deplacement = 1;
	int deplacement_precedent = 1;
	bool traverseMurDestructible;
	int xDep;
	int yDep;
public:
	EnnemiAllerRetour(int x, int y, int direction, bool traverse);
	~EnnemiAllerRetour();
	void dessiner();
	void calculDeplacement();
	void Deplacer();
	void deplacementGauche();
	void deplacementDroite();
	void deplacementHaut();
	void deplacementBas();
	void retour();
};

