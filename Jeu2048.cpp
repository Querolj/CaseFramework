#include "Jeu2048.h"
#include "Case.h"
#include <cmath>
#include <iostream>
using namespace std;

template<class T>
Jeu2048<T>::Jeu2048(int t, int d, int jo) : Tableau<T>(t, d, jo, 2)
{
}

/*
	DEBUT DE TOUR
*/
template<class T>
	void Jeu2048<T>::BeginTurn(Case<T> **&p)
	{
		cout<<"BeginTurn"<<endl;
		int n = Tableau<T>::countValue(p, 0);

		cout<<"n : "<<n<<endl;

		int r1 = rand() % 2;
		int r2 = rand() % 2;
		Case<T> c2(2, "2");
		Case<T> c4(4, "4");
		if(r1 == 0)
		{
			Tableau<T>::addRandom(p, c2, 0);
		}
		else
		{
			Tableau<T>::addRandom(p, c4, 0);
		}
		if(r2 == 0 && n>1)
		{
			Tableau<T>::addRandom(p, c2, 0);
		}
		else if(n>1)
		{
			Tableau<T>::addRandom(p, c4, 0);
		}
			
	}



template<class T>
	void Jeu2048<T>::updateCustom(char input)
	{
		Case<T> **&p = Tableau<T>::plateau1;
		while(true)
		{
			cout<<"updateCustom !"<<endl;
			if(Tableau<T>::moveAll(p, input, 0, 0))
			{

				cout<<"Ca bouge !"<<endl;
				break;
			}
			else
			{
				cout<<"Mouvement IMPOSSIBLE."<<endl;
				input = Tableau<T>::getInput();
			}
		}
		
		
			
	}

/*
	TOUR DU PC
*/
template<class T>
	void Jeu2048<T>::computerTurn()
	{
		Case<T> **&p = Tableau<T>::plateau2;
		bool didMove = false;
		for(int i=0; i<4;i++)
		{
			if(i==0&&(didMove = Tableau<T>::moveAll(p, 'z', 0, 0)))			
				break;
			else if(i==1&&(didMove =Tableau<T>::moveAll(p, 'q', 0, 0)))
				break;
			else if(i==2&&(didMove =Tableau<T>::moveAll(p, 's', 0, 0)))
				break;
			else if(i==3&&(didMove =Tableau<T>::moveAll(p, 'd', 0, 0)))
				break;
			
		}
		//Si didMove==false, le PC perd

	}


/*
	FIN DE TOUR (Vérification de l'état du jeu)
*/
template<class T>
	int Jeu2048<T>::endTurn(Case<T> **&p)
	{
			if(checkVictory(p))
			{
				cout<<"Victoire"<<endl;
				return 0; //Victoire
			}
			else if(checkLoose(p))
			{
				cout<<"Défaite"<<endl;
				return -1;
			}
			return 1;
			
	}

template<class T>
	bool Jeu2048<T>::checkVictory(Case<T> **&p)
	{
		int t = Tableau<T>::taille;
		for(int i=0; i<t;i++)
		{
			for(int j=0; j<t;j++)
			{
				if(p[i][j].getV() == 2048)
					return true;
			}
		}
		return false;
	}

template<class T>
	bool Jeu2048<T>::checkLoose(Case<T> **&p)
	{
		int c1 = Tableau<T>::countValue(p, 0);
		if(c1 == 0)
			return true;
		else
			return false;
	}


/*
	COLLISION
*/

template<class T>
void Jeu2048<T>::collisionCase(Case<T> & c1, Case<T> & c2)
{
	//cout<<"COLLISION"<<endl;
	if(c1.getV() == c2.getV())
	{
		int n = c1.getV()+c2.getV();
		c2.setV(n);
		c2.setA(to_string(n));
		c1.setCase(0, " ");
	}
}


template class Jeu2048<int>;