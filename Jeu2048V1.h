#ifndef JEU2048V1_H
#define JEU2048V1_H

#include <iostream>
#include "Tableau.h"
#include "Jeu2048.h"
using namespace std;

template<class T>
class Jeu2048V1:public Jeu2048<T>
{
public:
	Jeu2048V1<T>(int t, int d, int jo);
	void collisionCase(Case<T> & c1, Case<T> & c2);
	void BeginTurn(Case<T> **&p);
	
};

#endif