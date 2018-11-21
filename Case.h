#ifndef CASE_H
#define CASE_H

#include <iostream>
using namespace std;

template<class T>
class Case
{
private:
	T valeur; // Si valeur = 0, la case est vide
	string affichage;
	bool melange = false; //Si la case a été mélangée dans un tableau
public:
	//Constructeurs 
	Case();
	Case(T v, string s);
	//Surchage d'opérateur
	Case<T>& operator=(const Case<T>& c);
	nullptr_t operator=(nullptr_t null);
	Case<T> operator+(const Case<T> & c) const;
	Case<T> operator-(const Case<T> & c) const;
	Case<T> operator*(const Case<T> & c) const;
	bool operator==(const Case<T> & c) const;
	//Destructeur

	//Getter&Setter
	T getV() const;
	string getA() const;
	void setV(T i);
	void setA(string a);
	void setCase(T i, string s);
};

#endif
