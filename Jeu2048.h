#ifndef JEU2048_H
#define JEU2048_H

#include <iostream>
#include "Tableau.h"
using namespace std;

template<class T>
class Jeu2048:public Tableau<T>
{
public:
	Jeu2048<T>(int t, int d, int jo);
	void updateCustom(char input);
	void computerTurn();
	int endTurn(Case<T> **&p);
	bool checkVictory(Case<T> **&p);
	bool checkLoose(Case<T> **&p);
	virtual void collisionCase(Case<T> & c1, Case<T> & c2);
	virtual void BeginTurn(Case<T> **&p);
	
};

#endif