	# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++ -std=c++11 -Wall -Werror
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler. extra = unused param

all: main

main: Main.o Case.o Tableau.o JeuTaquin.o Jeu2048.o Jeu2048V1.o Jeu2048V2.o
	$(CC) -o main Tableau.o Case.o JeuTaquin.o Jeu2048.o Jeu2048V1.o Jeu2048V2.o Main.o


Main.o: Main.cpp JeuTaquin.o
	$(CC) -c Main.cpp

JeuTaquin.o: JeuTaquin.cpp Tableau.o
	$(CC) -c JeuTaquin.cpp

Jeu2048V2.o: Jeu2048V2.cpp Jeu2048.o
	$(CC) -c Jeu2048V2.cpp

Jeu2048V1.o: Jeu2048V1.cpp Jeu2048.o
	$(CC) -c Jeu2048V1.cpp

Jeu2048.o: Jeu2048.cpp Tableau.o
	$(CC) -c Jeu2048.cpp

Tableau.o: Tableau.cpp Case.o
	$(CC) -c Tableau.cpp

Case.o: Case.cpp Case.h
	$(CC) -c Case.cpp


clean:
	rm *.o *.gch