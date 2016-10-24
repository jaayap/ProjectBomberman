#pragma once
class Bombe
{
	int x, y; // position de la bombe dans la matrice
	int portee = 3; // 3 par defaut
	//int type;
public :bool posee; // true : la bombe est posée par terre, false : bomberman possede toujours la bombe 
		bool explosion; // true : explosion en cours, false : non explose
		double Timer=0;

public:
	Bombe();
	Bombe(int x,int y);
	void exploser();
	//void effacerExplosion();
	void dessinerExplosion();
	void dessinerExplosionHaut();
	void dessinerExplosionBas();
	void dessinerExplosionGauche();
	void dessinerExplosionDroite();
	~Bombe();
};

