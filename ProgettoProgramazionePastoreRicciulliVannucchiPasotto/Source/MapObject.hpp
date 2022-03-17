#pragma once

#include <iostream>
using namespace std;
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */



enum ObjectType {
	air,
	wall,
	gas,
	obstacle,
	pit,
	nails
};

class Object {
protected:

	ObjectType type;
	char appearance; //carattere che definisce il tipo
	void ChangeAppearance(); // riassegna ad appearance il carattere di type

public:

	Object(); // costruttore default type air
	Object(ObjectType x);
	ObjectType GetType(); // ritorna il tipo dell'oggetto

	void PrintAppearance(); // stampa il carattere 
	void ChangeType(ObjectType new_ob); //cambia il tipo 
	char GetAppearance(); // ritorna il carattere appearence
};