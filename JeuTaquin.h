#ifndef JEUTAQUIN_H
#define JEUTAQUIN_H

#include <iostream>
#include "Tableau.h"
using namespace std;

template<class T>
class JeuTaquin:public Tableau<T>
{
public:
	JeuTaquin(int t, int d, int jo, int mode);
	void updateCustom(char input);
	void computerTurn();
	int endTurn(Case<T> **&p);
	Case<T> emptyCase();
	Case<T>& getEmptyCase(Case<T> **&plateau);
	bool checkOrder(Case<T> **&plateau);
	Case<T>* neighboursOfEmptyCase(Case<T> **&plateau);
private:
	int x; //Cordonnées de la case vide du joueur humain et de l'ordinateur
	int y;
	int x2;
	int y2;
};

#endif