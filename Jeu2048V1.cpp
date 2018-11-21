#include "Jeu2048V1.h"
#include "Case.h"
#include <cmath>
#include <iostream>
using namespace std;


template<class T>
Jeu2048V1<T>::Jeu2048V1(int t, int d, int jo) : Jeu2048<T>(t, d, jo)
{
}

/*
	DEBUT DE TOUR
*/
template<class T>
	void Jeu2048V1<T>::BeginTurn(Case<T> **&p)
	{
		cout<<"BeginTurn"<<endl;
		int n = Tableau<T>::countValue(p, 0);

		cout<<"n : "<<n<<endl;

		int r1 = rand() % 3;
		int r2 = rand() % 3;
		Case<T> c2(2, "2");
		Case<T> c4(4, "4");
		Case<T> d(-1, "-1");
		if(r1 == 0)
		{
			Tableau<T>::addRandom(p, c2, 0);
		}
		else if(r1 == 1)
		{
			Tableau<T>::addRandom(p, c4, 0);
		}
		else
		{
			Tableau<T>::addRandom(p, d, 0);
		}
		if(r2 == 0 && n>1)
		{
			Tableau<T>::addRandom(p, c2, 0);
		}
		else if(r2 == 0 && n>1)
		{
			Tableau<T>::addRandom(p, c4, 0);
		}
		else if(n>1)
		{
			Tableau<T>::addRandom(p, d, 0);
		}

			
	}


/*
	COLLISION
*/

template<class T>
void Jeu2048V1<T>::collisionCase(Case<T> & c1, Case<T> & c2)
{
	//cout<<"COLLISION"<<endl;
	if(c1.getV() == c2.getV())
	{
		int n = c1.getV()+c2.getV();
		c2.setV(n);
		c2.setA(to_string(n));
		c1.setCase(0, " ");
	}
	if(c1.getV() == -1)
	{
		c1.setCase(0, " ");
		c2.setCase(0, " ");
	}
}


template class Jeu2048V1<int>;