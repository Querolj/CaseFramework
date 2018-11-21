#ifndef TABLEAU_H
#define TABLEAU_H

#include <iostream>
#include "Case.h"
using namespace std;

template<class T>
class Tableau
{
	friend ostream & operator<<(ostream & out, const Tableau<T> & t)
	{
		cout<<endl<<"  ";	
		for(int k=0; k<t.taille;k++)
			cout<<" "<<k<<" "; 
		cout<<endl;
		for(int i=0; i<t.taille;i++)
		{
			cout<<"  ";
			for(int k=0; k<t.dimension*t.taille;k++)
				cout<<"_"; 
			cout<<endl;		
			cout<<i<<" ";
			for(int j=0; j<t.taille; j++)
			{
				cout<<"|"<<t.plateau1[i][j].getA()<<"|";
			}
			cout<<endl;	
		}
		if(t.joueur==2)
		{
			cout<<endl<<"  ";	
			for(int k=0; k<t.taille;k++)
				cout<<" "<<k<<" "; 
			cout<<endl;
			for(int i=0; i<t.taille;i++)
			{
				cout<<"  ";
				for(int k=0; k<t.dimension*t.taille;k++)
					cout<<"_"; 
				cout<<endl;		
				cout<<i<<" ";
				for(int j=0; j<t.taille; j++)
				{
					cout<<"|"<<t.plateau2[i][j].getA()<<"|";
				}
				cout<<endl;	
			}
		}
		return out;
	}
public:
	//Constructeurs
	Tableau<T>(int t, int d, int jo, int mode); //taille, dimension, joueur (1 ou 2), mode d'initialisation des plateaux
	Tableau<T>(const Tableau& s);

	//Surcharge d'opérateur 
	Tableau<T>& operator=(const Tableau<T> & s);

	//Destructeur
	virtual ~Tableau<T>();
	//Fonctions pour initialisation
	void alloc();
	void initPlateau(Case<T> **&plateau);
	void initRandom(); //Remplie le tableau avec des valeurs aléatoire de 0 à 49
	void initOrder(); //Remplie le tableau avec des valeurs croissantes
	void initEmpty(); //Remplie le tableau avec des case vides
	//Getter/Setter
	void setCase(int i, int j, Case<T> c); // Modifie une case à la position i j
	T getCase(int i, int j);

	//Fonctions pour algorithme
	void swap(Case<T> &c1, Case<T> &c2); // 0 si ok, -1 sinon
	bool moveAll(Case<T> **&plateau, char direction, int d, T t); // d = distance de mouvement, direction = 'u', 'd', 'l' ou 'r', t = la valeur de la case vide
	bool move(Case<T> **&plateau, char direction, int d, int i, int j, T t); //i et j = la case concernée, retourne 1 si la case bouge de c case. Si la case est stoppé avant, retourne 0
	void random(); // Créer des valeurs random pour le tableau
	void addRandom(Case<T> **&plateau, Case<T> c, T v); // Sélectionne une case au hasard ayant la valeur v et remplace cette case par c
	void suffle(Case<T> **&plateau); //mélange les cases du plateau sélectionné
	bool* checkNeighbours(Case<T> **&plateau, int i, int j);
	char getInput();
	int countValue(Case<T> **&plateau, T t);

	//Création du plateau
	void createRandomPlateau(int taille);

	//Mise en route du jeu 
	void start();
	void setRules(int t, bool c);

	
	//Fonctions à surcharger
	virtual void BeginTurn(Case<T> **&p);
	virtual void updateCustom(char input);
	virtual void collisionCase(Case<T> & c1, Case<T> & c2); //c1 rentre dans c2
	virtual void computerTurn();
	virtual int endTurn(Case<T> **&p); 
	
private:
	void update();
	bool endCheck(int);
	

protected:	
	int taille; //Taille des cases du tableau
	int dimension; //Dimension du tableau de jeu, doit être égale à la plus grande valeur de la taille parmis les éléments à afficher
	int joueur;
	int tour = 0; // tour max, 0 si une infinité de tour
	bool col = false; //CollisionCase activé ou pas
	bool ready = false; //Si on peut commencer le jeu ou pas (fonction start)


	Case<T> **plateau1;
	Case<T> **plateau2;
};

#endif
