#pragma once
class Bonus
{
	int x, y; // position du bonus a ramasser
	int type; // type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
	bool visible; // true : on peut le ramasser, false : il est derriere un mur
public:
	Bonus(int i, int j, int type);
	~Bonus();
	int getX();
	int getY();
	bool getVisible();
	void setVisible(bool);

	void ramasser();
	void dessiner();
};

