#pragma once
class Bonus
{
	int x, y; // position du bonus a ramasser
	int type; // type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
	bool visible; // true : on peut le ramasser, false : il est derriere un mur
	bool utiliser; // true : l'objet a ete ramasser, false : l'objet n'a pas été ramasser
public:
	Bonus(int i, int j, int type);
	~Bonus();
	int getX();
	int getY();
	bool getVisible();
	bool getUtiliser();
	void setVisible(bool);
	void setUtiliser(bool utiliser);
	void ramasser();
	void dessiner();
};

