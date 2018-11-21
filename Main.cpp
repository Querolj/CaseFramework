#include <iostream> 
using namespace std;

#include "Case.h"
#include "JeuTaquin.h"
#include "Jeu2048.h"
#include "Jeu2048V1.h"
#include "Jeu2048V2.h"

int main() 
{ 

	/*Jeu2048V2<int> t(10,1,1); //t, d, j, m
	t.Jeu2048V2::setRules(0,true);
	t.Jeu2048V2::start();*/
	JeuTaquin<int> t(3,1,2, 1); //t, d, j, m
	t.JeuTaquin::setRules(0,false);
	t.JeuTaquin::start();
	
}	