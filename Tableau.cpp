#include "Tableau.h"
#include <cmath>
#include <iostream>
#include <cstdlib> 
#include <algorithm>
using namespace std;
/*
TODO : 

*/
template<class T>
Tableau<T>::Tableau(int t, int d, int jo, int mode) : taille(t), dimension(d+2),joueur(jo)
{
	srand(time(0));
	initPlateau(plateau1);
	if(joueur==2)
		initPlateau(plateau2);
	if(mode==0) // Tableau avec Case aux valeurs dans l'ordre croissant (suite de nombre)
		initOrder();
	else if(mode==1) // Tableau avec Case aux valeurs aléatoire
		initRandom();
	else if(mode==2) // Tableau avec Case aux valeurs égales à 0 et affiche " "
		initEmpty();
	
}

template<class T>
void Tableau<T>::initEmpty() 
{
	for(int i=0; i<taille; i++)
	{
		for(int j=0; j<taille; j++)
		{
			plateau1[i][j].setCase(0, " ");
			if(joueur == 2)
				plateau2[i][j].setCase(0, " ");
		}

	}
}

template<class T>
void Tableau<T>::initPlateau(Case<T> **&plateau)
{
	plateau = new Case<T>* [taille];
	for(int i=0; i<taille; i++)
	{
		plateau[i] = new Case<T>[taille];
	}
}

template<class T>
void Tableau<T>::initOrder() 
{
	int r = 0;
	for(int i=0; i<taille; i++)
	{
		for(int j=0; j<taille; j++)
		{
			r += 1;
			plateau1[i][j].setCase(r, to_string(r));
			if(joueur == 2)
				plateau2[i][j].setCase(r, to_string(r));

		}

	}
}
template<class T>
void Tableau<T>::initRandom() 
{
	int r;
	for(int i=0; i<taille; i++)
	{
		for(int j=0; j<taille; j++)
		{
			r = rand() % 50;
			plateau1[i][j].setCase(r, to_string(r));
			if(joueur == 2)
			{
				r = rand() % 50;
				plateau2[i][j].setCase(r, to_string(r));
			}

		}

	}
}

/*
	REGLES DE 3
*/
//Constructeur de copie
template<class T>
	Tableau<T>::Tableau(const Tableau& s)
	{
		cout << "Constructeur de copie appelé" <<endl;
		taille = s.taille;
		dimension = s.dimension;

		alloc();
	}

template<class T>
	void Tableau<T>::alloc()
	{
		if(taille > 0)
		{
			plateau1 = new Case<T>*[taille];
			for(int i=0; i<taille;i++)
				plateau1[i] = new Case<T>[taille];
		}
		else
		{
			plateau1 = nullptr;
		}
	}
template<class T>
	Tableau<T>& Tableau<T>::operator=(const Tableau<T>& s)
	{
		cout << "assignement surchargé" <<endl;
	//Vérifie un assignement à lui même
		if(this == &s)
		return *this; //On ne retourne pas le pointeur en lui même
	taille = s.taille;
	dimension = s.dimension;

	for(int i=0; i<taille;i++)
		for(int j=0;j<taille;j++)
			plateau1[i][j] = s.plateau1[i][j];
		return *this;
	}

//Destructeur
template<class T>
	Tableau<T>::~Tableau()
	{
		cout << "Destructeur appelé";
		if(plateau1 != nullptr)
		{
			for(int i=0; i<taille;i++)
				if(plateau1[i] != nullptr)
					delete[] plateau1[i];
				delete[] plateau1;
			}
		}
/*
	Fin règle de 3
*/



//Fonctions de mouvements
template<class T>
void Tableau<T>::swap(Case<T> &c1, Case<T> &c2) // Intervertit Case[x][y] avec Case[x2][y2]
{
	Case<T> s;
	s=c1;
	c1=c2;
	c2=s;
}

template<class T>
bool Tableau<T>::move(Case<T> **&plateau, char direction, int d, int x, int y, T t) //t = la valeur de la case sur laquelle on peut bouger
{
	int distance;
	bool didMove = false;
	if(d==0 || d>taille - 1)
		distance = taille-1;
	else
		distance = d;

	try{
		for(int i = 0; i<distance;i++)
		{
			if(direction == 'd' && y != taille -1) 
			{
				if(plateau1[x][y+1].getV() == t)
				{
					swap(plateau[x][y+1],plateau[x][y]);
					didMove = true;
					if(y != taille-1)
						y += 1;
					else
						break;
				}
				else if(col)
				{
					collisionCase(plateau[x][y], plateau[x][y+1]);
					return true;
				}

			}
			else if(direction == 'q' && y != 0)
			{
				if(plateau1[x][y-1].getV() == t)
				{
					swap(plateau[x][y-1],plateau[x][y]);
					didMove = true;
					if(y!=0)
						y -= 1;
					else
						break;
				}
				else if(col)
				{
					collisionCase(plateau[x][y], plateau[x][y-1]);
					return true;
				}
			}
			else if(direction == 'z' && x != 0)
			{
				if(plateau1[x-1][y].getV() == t)
				{
					swap(plateau[x-1][y],plateau[x][y]);
					didMove = true;
					if(x != 0)
						x -= 1;
					else
						break;
				}
				else if(col)
				{
					collisionCase(plateau[x][y], plateau[x-1][y]);
					return true;
				}
			}
			else if(direction == 's' && x != taille-1)
			{
				if(plateau1[x+1][y].getV() == t)
				{
					swap(plateau[x+1][y],plateau[x][y]);
					didMove = true;
					if(x != taille - 1)
						x += 1;
					else
						break;
				}
				else if(col)
				{
					collisionCase(plateau[x][y], plateau[x+1][y]);
					return true;
				}
			}
			else
			{ 

				break; //Fin du mouvement
			}
		}
	}
	catch(int code)
	{
		cerr << "On dépasse la taille du plateau1 !" << endl;
	}
	return didMove;
}
template<class T>
bool Tableau<T>::moveAll(Case<T> **&plateau, char direction, int d, T t) // d = distance, t = valeur sur laquelle on peut bouger
{
	bool didMove = false;
	bool b = false;
	if(direction == 's')
	{
		for(int i=taille -2; i>=0; i--)
		{
			for(int j=0; j<taille; j++)
			{
				if(plateau[i][j].getV() !=0)
				{
					b = move(plateau,direction, d, i, j, t);
					didMove = didMove || b;
				}
				
			}
		}
	}
	else if(direction == 'z')
	{
		for(int i=1; i<taille; i++)
		{
			for(int j=0; j<taille; j++)
			{
				if(plateau[i][j].getV() !=0)
				{
					b = move(plateau,direction, d, i, j, t);
					didMove = b||didMove;
				}
			}
		}
	}
	else if(direction == 'd')
	{
		for(int j=taille -2; j>=0; j--)
		{
			for(int i=0; i<taille; i++)
			{
				if(plateau[i][j].getV() !=0)
				{
					b = move(plateau,direction, d, i, j, t);
					didMove = b||didMove;
				}
			}
		}
	}
	else if(direction == 'q')
	{
		for(int j=1; j<taille; j++)
		{
			for(int i=0; i<taille; i++)
			{
				if(plateau[i][j].getV() !=0)
				{
					b = move(plateau,direction, d, i, j, t);
					didMove = b||didMove;
				}
			}
		}
	}
	else
	{
		cerr<<"direction inconnue"<<endl;
	}
	return didMove;
}
template<class T>
void Tableau<T>::random()
{
	for(int i=0; i<taille;i++)
	{
		for(int j=0; j<taille;j++)
		{
			plateau1[i][j].setV(rand() % 100); 
		}
	}
}
template<class T>
void Tableau<T>::setCase(int i, int j, Case<T> c)
{
	plateau1[i][j] = c;
}
template<class T>
T Tableau<T>::getCase(int i, int j)
{
	return plateau1[i][j].getV();
}
template<class T>
void Tableau<T>::createRandomPlateau(int taille)
{
	plateau1 = new Case<T>* [taille];
	for(int i=0; i<taille; i++)
	{
		plateau1[i] = new Case<T>[taille];
	}
	int r;
	for(int i=0; i<taille; i++)
	{
		for(int j=0; j<taille; j++)
		{
			r = rand() % 100;
			plateau1[i][j].setCase(r, to_string(r));
		}
		
	}
}

template<class T>
void Tableau<T>::addRandom(Case<T> **&plateau, Case<T> c, T v)
{
	int n = 0; // Nombre de v 
	for(int i=0; i<taille;i++)
	{
		for(int j=0; j<taille; j++)
		{
			if(plateau[i][j].getV() == v)
				n++;
		}
	}
	int r = rand() % n + 1;
	n=1; 
	for(int i=0; i<taille;i++)
	{
		for(int j=0; j<taille; j++)
		{
			if(plateau[i][j].getV() == v && n==r)
			{
				plateau[i][j].setCase(c.getV(), c.getA());
				return;
			}
			else if(plateau[i][j].getV() == v)
			{
				n++;
			}
		}
	}


}

template<class T>
void Tableau<T>::suffle(Case<T> **&plateau)
{
	T t[taille*taille];

	for(int i=0; i<taille;i++)
	{
		for(int j=0; j<taille; j++)
		{
			t[i * taille +j] = plateau[i][j].getV();
		}
		
	}
	random_shuffle(&t[0], &t[taille*taille]);

	for(int i=0; i<taille;i++)
	{
		for(int j=0; j<taille; j++)
		{
			plateau[i / taille][i % taille].setCase(t[i], "");
		}
		
	}
}


template<class T>
void Tableau<T>::start()
{
	if(ready)
	{
		update();
	}
	else
	{
		cout<<"Veuillez utiliser la fonction setRules"<<endl;
	}
}
template<class T>
void Tableau<T>::update()
{
	int p1 = 1, p2 = 1;
	int currentTurn = 1;
	while(currentTurn!=tour || tour == 0){

		BeginTurn(plateau1);
		if(p2 == 1 && joueur ==2)
			BeginTurn(plateau2);

		cout<<*this<<endl;

		updateCustom(getInput());
		
		if(p2 == 1 && joueur ==2)
		{
			cout<<"le PC commence son tour"<<endl;
			computerTurn();
		} //Si le PC n'a pas gagné ni perdu (quand endTurn retourne 1), le PC continue ses tours
		else if(p2 == -1)
		{
			cout<<"Le joueur 2 a finit sa partie, il a perdu"<<endl;
		}
		else if(p2 == 0)
		{
			cout<<"Le joueur 2 a finit sa partie, il a gagné"<<endl;
		}
		cout<<"DEBUG"<<endl;
		p1 = endTurn(plateau1);
		if(p2 == 1 && joueur ==2)
			p2 = endTurn(plateau2);
		if(endCheck(p1)) // Vérifie si la partie se termine
			break;
		currentTurn++;
	}
	cout<<"fin de la partie"<<endl;
}

template<class T>
char Tableau<T>::getInput()
{
	char input;
	while(true)
	{
		cout<<"zqsd pour la direction, echape pour terminer l'application"<<endl;
		cin>>input;
		if(input=='z'||input=='q'||input=='s'||input=='d')
			return input;
		cout<<"Entrée mauvaise ! zqsd pour la direction, echape pour terminer l'application"<<endl;
	}

}

template<class T>
bool Tableau<T>::endCheck(int p)
{
	if(p==0)
	{
		cout<<"le joueur 1 a gagné"<<endl;
		return true;
	}	
	if(p==-1)
	{
		cout<<"le joueur 1 a perdu"<<endl;
		return true;
	}
	return false;
}

//Fonctions à redéfinir ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class T>
void Tableau<T>::updateCustom(char input){
	cerr<<"updateCustom VIDE !, Veuillez redéfinir la fonction avant de l'utiliser"<<endl;
}

template<class T>
void Tableau<T>::BeginTurn(Case<T> **&p){
	cerr<<"BeginTurn VIDE !, Veuillez redéfinir la fonction avant de l'utiliser"<<endl;
}

template<class T>
int Tableau<T>::endTurn(Case<T> **&p)
{
	plateau1 = p;
	return 0;
}

template<class T>
void Tableau<T>::computerTurn(){
	cerr<<"computerTurn VIDE !, Veuillez redéfinir la fonction avant de l'utiliser"<<endl;
}

template<class T>
void Tableau<T>::collisionCase(Case<T> & c1, Case<T> & c2)
{
	cerr<<"COLLISION DANS TABLEAU !, Veuillez redéfinir la fonction avant de l'utiliser"<<endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



template<class T>
void Tableau<T>::setRules(int t, bool c)
{
	tour = t;
	col = c;
	ready = true;
}



template<class T>
bool* Tableau<T>::checkNeighbours(Case<T> **&plateau, int i, int j) 
{ //0 = droit, 1 = bas, 2 = gauche, 3 = haut
	bool *neighbours;
	neighbours = new bool[4];
	for(int n = 0; n<taille;n++)
		neighbours[n] = false;
	if(j!=taille - 1)
		neighbours[0] = true;
	if(i!=taille - 1)
		neighbours[1] = true;
	if(j!=0)
		neighbours[2] = true;
	if(i!=0)
		neighbours[3] = true;

	return neighbours;
}



template<class T>
int Tableau<T>::countValue(Case<T> **&plateau, T t)
{
	int c = 0;
	for(int i=0;i<taille;i++)
	{
		for(int j=0;j<taille;j++)
		{
			if(plateau[i][j].getV() == t)
				c++;
		}
	}
	return c;
}

template class Tableau<int>;