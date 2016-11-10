#pragma once
class Bombe
{
	int x, y; // position de la bombe dans la matrice.
	int portee; // 3 par defaut.
	//Variable pour l'affichage de l'explosion.
	int nbCaseHaut = 0;
	int nbCaseBas = 0;
	int nbCaseGauche = 0;
	int nbCaseDroite = 0;

	bool arretExplosionHaut = false;
	bool arretExplosionBas = false;
	bool arretExplosionGauche = false;
	bool arretExplosionDroite = false;

	bool afficherExtremHaut = false;
	bool afficherExtremBas = false;
	bool afficherExtremGauche = false;
	bool afficherExtremDroite = false;

public :bool posee; //true : la bombe est posee par terre, false : bomberman possede toujours la bombe.
		bool explosion; //true : explosion en cours, false : non explose.
		double Timer=0;//timer qui gére le temps avant et pendant l'explosion 

public:
	Bombe();
	Bombe(int x,int y, int portee);
	int getX();
	int getY();
	void exploser();
	void explosionHaut();
	void explosionBas();
	void explosionGauche();
	void explosionDroite();
	void effacerExplosion();
	void dessinerExplosion();
	void dessinerExplosionHaut();
	void dessinerExplosionBas();
	void dessinerExplosionGauche();
	void dessinerExplosionDroite();
	void effacerBombes();
	~Bombe();
};

