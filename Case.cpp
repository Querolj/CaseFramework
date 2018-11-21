#include "Case.h"
#include <cmath>
#include <iostream>
using namespace std;


template<class T>
Case<T>::Case()
{}
template<class T>
Case<T>::Case(T v, string s) : valeur(v), affichage(s)
{
	valeur = v;
	affichage = s;
}

template<class T>
Case<T>& Case<T>::operator=(const Case<T>& c)
{
    //Vérifie un assignement à lui même
    if(this == &c)
        return *this; //On ne retourne pas le pointeur en lui même
    valeur = c.valeur;
    affichage = c.affichage;

    return *this;
}
template<class T>
nullptr_t Case<T>::operator=(nullptr_t null)
{
    cout << "assignement nul" <<endl;   

    return null;
}


template<class T>
Case<T> Case<T>::operator+(const Case<T> & c) const
{
    Case<T> r;
    r.valeur = c.valeur+valeur;
    
    return r;
}
template<class T>
Case<T> Case<T>::operator-(const Case<T> & c) const
{
    Case<T> r;
    r.valeur = valeur-c.valeur;
    
    return r;
} 
template<class T>
Case<T> Case<T>::operator*(const Case<T> & c) const
{
    Case<T> r;
    r.valeur = c.valeur*valeur;
    
    return r;
} 
template<class T>
bool Case<T>::operator==(const Case<T> & c) const
{
	return valeur==c.valeur; //Comparer éventuellement les strings ??
}

template<class T>
T Case<T>::getV() const
{
    return this->valeur;
}
template<class T>
string Case<T>::getA() const
{
    return this->affichage;
}
template<class T>
void Case<T>::setV(T i)
{
	valeur = i;
}
template<class T>
void Case<T>::setA(string a)
{
	affichage = a;
}
template<class T>
void Case<T>::setCase(T i, string s)
{
    valeur = i;
    affichage = s;
}
template class Case<float>;
template class Case<int>;