#include "Jeu2048V2.h"
#include "Case.h"
#include <cmath>
#include <iostream>
using namespace std;


template<class T>
Jeu2048V2<T>::Jeu2048V2(int t, int d, int jo) : Jeu2048<T>(t, d, jo)
{
}

/*
	DEBUT DE TOUR
*/
template<class T>
	void Jeu2048V2<T>::BeginTurn(Case<T> **&p)
	{
		cout<<"BeginTurn"<<endl;
		int n = Tableau<T>::countValue(p, 0);

		cout<<"n : "<<n<<endl;

		int r1 = rand() % 4;
		int r2 = rand() % 4;
		Case<T> c2(2, "2");
		Case<T> c4(4, "4");
		Case<T> m1(20, "*2");
		Case<T> m2(-20, "/2");
		if(r1 == 0)
		{
			Tableau<T>::addRandom(p, c2, 0);
		}
		else if(r1 == 1)
		{
			Tableau<T>::addRandom(p, c4, 0);
		}
		else if(r1 == 2)
		{
			Tableau<T>::addRandom(p, m1, 0);
		}
		else
		{
			Tableau<T>::addRandom(p, m2, 0);
		}


		if(r2 == 0 && n>1)
		{
			Tableau<T>::addRandom(p, c2, 0);
		}
		else if(r2 == 1 && n>1)
		{
			Tableau<T>::addRandom(p, c4, 0);
		}
		else if(r2 == 2 && n>1)
		{
			Tableau<T>::addRandom(p, m1, 0);
		}
		else if(n>1)
		{
			Tableau<T>::addRandom(p, m2, 0);
		}

			
	}


/*
	COLLISION
*/

template<class T>
void Jeu2048V2<T>::collisionCase(Case<T> & c1, Case<T> & c2)
{
	//cout<<"COLLISION"<<endl;
	if(c1.getV() == c2.getV())
	{
		int n = c1.getV()+c2.getV();
		c2.setV(n);
		c2.setA(to_string(n));
		c1.setCase(0, " ");
	}
	if(c1.getV() == 20 && !(c2.getV() == 20 && c2.getV() == -20))
	{
		int n = 2*c2.getV();
		c1.setCase(0, " ");
		c2.setCase(n, to_string(n));
	}
	else if(c1.getV() == -20 && !(c2.getV() == 20 && c2.getV() == -20 && c2.getV() == 0))
	{
		int n = c2.getV()/2;
		c1.setCase(0, " ");
		c2.setCase(n, to_string(n));
	}
}


template class Jeu2048V2<int>;