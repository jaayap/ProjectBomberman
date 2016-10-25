#pragma once
class Personnage
{
public: int x, y; // coordonnées
	float offsetX  = 0, offsetY = 0;
	int direction; //1 : gauche; 2 : droite; 3 : haut; 4 : bas
	float vitesseDeplacement = 1;
	int nb_vies;
	bool vivant; // true : vivant, false : mort

public:
	Personnage(int x, int y);
	~Personnage();
	//Getter
	int getX();
	int getY();
	bool getVivant();
	float getVitesseDeplacement();
	//Setter
	void setVivant(bool vivant);
	void setVitesseDeplacement(float vitesse);
	void deplacementHaut();
	void deplacementBas();
	void deplacementGauche();
	void deplacementDroite();
};

