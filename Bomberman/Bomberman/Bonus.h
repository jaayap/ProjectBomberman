#pragma once
class Bonus
{
	int x, y; // position du bonus a ramasser
	int type; // type du bonus : 1 -> + bombes, 2 -> + portee, 3 -> + vitesse
public:
	Bonus();
	~Bonus();
	void ramasser();
	void dessiner();
};

