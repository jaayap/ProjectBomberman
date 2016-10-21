#include "Bombe.h"
#include "Niveau.h"
#include <iostream>
#include "Bomberman.h"

using namespace std; 

extern Niveau niveau;
extern Bomberman bomberman;


Bombe::Bombe()
{
}

Bombe::Bombe(int x, int y) {
	this->x = x;
	this->y = y;
	posee = false;
	explosion = false;
}

Bombe::~Bombe()
{
}

void Bombe::exploser() {

	bool arretExplosionHaut = false;
	bool arretExplosionBas = false;
	bool arretExplosionGauche = false;
	bool arretExplosionDroite = false;

	niveau.modifierCase(y, x, '4');

		for (int i = 1; i < portee - 1; i++) {
			//dessin de l'explosion : 4 milieu de la bombe, 5 suite, 6 fin explosion

			if (niveau.caseLibre(y, x - i)) { //A gauche
					
				if (niveau.caseMurDestructible(y, x - i)) {
					niveau.modifierCase(y, x - i, '3');
					arretExplosionGauche = true;
				}
				else {
					niveau.modifierCase(y, x - i, '5');
				}

				//Test si il y a des mort
				if ((x - i) == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);

			}
			else {
				arretExplosionGauche = true;
			}
			if (niveau.caseLibre(y, x + i)) { //A droite
				
				if (niveau.caseMurDestructible(y, x + i)) {
					niveau.modifierCase(y, x + i, '3');
					arretExplosionDroite = true;
				}
				else niveau.modifierCase(y, x + i, '5');

				//Test si il y a des mort
				if (x+i == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
			}
			else {
				arretExplosionDroite = true;
			}
			if (niveau.caseLibre(y - i, x)) { //En haut
			
				if (niveau.caseMurDestructible(y - i, x)) {
					niveau.modifierCase(y - i, x, '3');
					arretExplosionHaut = true;
				}
				else 	niveau.modifierCase(y - i, x, '5');

				//Test si il y a des mort
				if (x == bomberman.getX() && y-i == bomberman.getY()) bomberman.setVivant(false);
			}
			else {
				arretExplosionHaut = true;
			}
			if (niveau.caseLibre(y + i, x)) { //En bas
				
				if (niveau.caseMurDestructible(y + i, x)) {
					niveau.modifierCase(y + i, x, '3');
					arretExplosionBas = true;
				} else niveau.modifierCase(y + i, x, '5');
				//Test si il y a des mort
				if (x == bomberman.getX() && y+i == bomberman.getY()) bomberman.setVivant(false);

			}
			else {
				arretExplosionBas = true;
			}

			//Test si il y a des mort
			if (x == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);

		}

		//extremité de l'explosion
		if (niveau.caseLibre(y, x - portee+1) && !arretExplosionGauche) { //A gauche
			niveau.modifierCase(y, x - portee+1, '6');

			//Test si il y a des mort
			if (x - portee + 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		}
		if (niveau.caseLibre(y, x + portee-1) && !arretExplosionDroite) { //A droite
			niveau.modifierCase(y, x + portee-1, '6');
			if (x + portee - 1 == bomberman.getX() && y == bomberman.getY()) bomberman.setVivant(false);
		}
		if (niveau.caseLibre(y - portee+1, x) && !arretExplosionHaut) { //En haut
			niveau.modifierCase(y - portee+1, x, '6');
			if (x == bomberman.getX() && y - portee + 1 == bomberman.getY()) bomberman.setVivant(false);
		}
		if (niveau.caseLibre(y + portee - 1, x) && !arretExplosionBas) { //En bas
			niveau.modifierCase(y + portee-1, x, '6');
			if (x == bomberman.getX() && y + portee - 1 == bomberman.getY()) bomberman.setVivant(false);
		}
}

void Bombe::effacerExplosion() {
	for (int i = 1; i < portee - 1; i++) {
		//dessin de l'explosion : 4 milieu de la bombe, 5 suite, 6 fin explosion

		if (niveau.caseLibre(y, x - i) && !niveau.caseMurDestructible(y,x-i)) { //A gauche
			niveau.modifierCase(y, x - i, '0');
		}
		if (niveau.caseLibre(y, x + i) && !niveau.caseMurDestructible(y, x + i)) { //A droite
			niveau.modifierCase(y, x + i, '0');
		}
		if (niveau.caseLibre(y - i, x) && !niveau.caseMurDestructible(y - i, x)) { //En haut
			niveau.modifierCase(y - i, x, '0');
		}
		if (niveau.caseLibre(y + i, x) && !niveau.caseMurDestructible(y + i,x)) { //En bas
			niveau.modifierCase(y + i, x, '0');
		}
	}

	//extremité de l'explosion
	if (niveau.caseLibre(y, x - portee + 1) && !niveau.caseMurDestructible(y, x - portee + 1)) { //A gauche
		niveau.modifierCase(y, x - portee + 1, '0');
	}
	if (niveau.caseLibre(y, x + portee - 1) && !niveau.caseMurDestructible(y, x + portee - 1)) { //A droite
		niveau.modifierCase(y, x + portee - 1, '0');
	}
	if (niveau.caseLibre(y - portee + 1, x) && !niveau.caseMurDestructible(y - portee + 1, x)) { //En haut
		niveau.modifierCase(y - portee + 1, x, '0');
	}
	if (niveau.caseLibre(y + portee - 1, x) && !niveau.caseMurDestructible(y + portee -1, x)) { //En bas
		niveau.modifierCase(y + portee - 1, x, '0');
	}

	niveau.modifierCase(y, x, '0');

}