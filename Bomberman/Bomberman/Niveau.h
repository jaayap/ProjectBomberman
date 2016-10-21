#pragma once
class Niveau
{
	char matrice[13][17];
	int nbColonnes;
	int nbLignes;

public:
	Niveau();
	~Niveau();
	void initialiserMatrice();
	void dessinerNiveau();
	bool caseLibre(int x,int y);
	bool caseMurDestructible(int x, int y);
	void modifierCase(int x, int y, char valeur);
};
