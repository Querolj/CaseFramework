#include "JeuTaquin.h"
#include <cmath>
#include <iostream>
using namespace std;

/*
TODO : Faire en fct du nombre de joueur
startcustom = remplacer une case au hasard par une case "vide"  OK
dans update custom, faire un swap en fonction de la direction choisit OK
computerTurn : bouger au hasard la case vide
getNeighbour inutilisable ? besoin des coordonnées des voisins, pas des cases en elles mêmes
Plus qu'à clean le update pour tester"
*/

template<class T>
JeuTaquin<T>::JeuTaquin(int t, int d, int jo, int mode) : Tableau<T>(t,d,jo, mode)
{
	//Tableau<T>::suffle(Tableau<T>::plateau1);
	Case<T> empty = JeuTaquin<T>::emptyCase();
	x = rand() % t;
	y = rand() % t;
	Tableau<T>::plateau1[x][y] = empty;
	if(Tableau<T>::joueur == 2)
	{
		//Tableau<T>::suffle(Tableau<T>::plateau2);
		x2 = rand() % t;
		y2 = rand() % t;
		Tableau<T>::plateau2[x2][y2] = empty;
	}
	
}


/*
	TOUR DU JOUEUR HUMAIN
*/

template<class T>
	void JeuTaquin<T>::updateCustom(char input)
	{
		Case<T> **&p = Tableau<T>::plateau1;
		bool *neighbours = Tableau<T>::checkNeighbours(p, x, y);
		while(true)
		{		
			if(input == 'z' && neighbours[0] == true)
			{
				swap(p[x][y],p[x-1][y]);
				x -= 1;
				cout<<"Mouvement OK."<<endl;
				break;
			}
			else if(input == 'd' && neighbours[1] == true)
			{
				swap(p[x][y],p[x][y+1]);
				y +=1;
				cout<<"Mouvement OK."<<endl;
				break;
			}
			else if(input == 's' && neighbours[2] == true)
			{
				swap(p[x][y],p[x+1][y]);
				x += 1;
				cout<<"Mouvement OK."<<endl;
				break;
			}
			else if(input == 'q' && neighbours[3] == true)
			{
				swap(p[x][y],p[x][y-1]);
				y -= 1;
				cout<<"Mouvement OK."<<endl;
				break;
			}


			cout<<"Mouvement "<<input<<" IMPOSSIBLE."<<endl;
			input = Tableau<T>::getInput();
		}
			
	}

template<>
	Case<int> JeuTaquin<int>::emptyCase()
	{
		Case<int> empty(-1, " ");
		return empty;
	}	

template<>
	Case<int>& JeuTaquin<int>::getEmptyCase(Case<int> **&plateau)
	{
		for(int i=0;i<this->taille;i++)
		{
			for(int j=0;j<this->taille;j++)
			{
				if(plateau[i][j].getV() == -1)
					return plateau[i][j];
			}
		}
		throw -1;
	}	

/*
	TOUR DE L'ORDINATEUR
*/


template<class T>
	void JeuTaquin<T>::computerTurn()
	{
		Case<T> **&p = Tableau<T>::plateau2;
		bool* neighbours;
		try
		{
			neighbours = Tableau<T>::checkNeighbours(Tableau<T>::plateau2, x2, y2);
		}
		catch(int code)
		{
			cerr << "Pas de case vide !" << endl;
		}

		for(int i=0;i<4;i++)
		{

			if(neighbours[i])
			{
				if(i==0)
				{
					swap(p[x2][y2], p[x2-1][y2]);
					x2 = x2-1;
				}
				else if(i==1)
				{
					swap(p[x2][y2], p[x2][y2+1]);
					y2 +=1;
				}
				else if(i==2)
				{
					swap(p[x2][y2], p[x2+1][y2]);
					x2 +=1;
				}
				else if(i==3)
				{
					swap(p[x2][y2], p[x2][y2-1]);
					y2 -=1;
				}

			}
		}

	}



/*
	FIN DE TOUR (Vérification de l'état du jeu)
*/
template<class T>
	int JeuTaquin<T>::endTurn(Case<T> **&p)
	{
		cout<<"endTurn"<<endl;
		if(checkOrder(p))
			return 0;
		else 
			return 1;
	}

template<class T>
bool JeuTaquin<T>::checkOrder(Case<T> **&plateau) // retourne vrai si le plateau est dans l'ordre
{
	int t = Tableau<T>::taille - 1;
	if(plateau[0][0].getV() == -1 || plateau[t][t].getV()) //Si la case vide est dans une position permettant un tableau dans l'ordre
	{
		for(int i=0; i<this->taille;i++)
		{
			for(int j=1;j<this->taille;j++)
			{
				if(plateau[i][j-1].getV()>plateau[i][j].getV())
					return false;
			}
		}
		return true;
	}
	
	return false;
}


template class JeuTaquin<int>;