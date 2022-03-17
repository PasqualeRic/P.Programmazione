#pragma once
#include "LevelGenerator.hpp"

struct levelListNode {		//nodo di una lista che contiene un levelGenerator e il puntatore al nodo successivo
	LevelGenerator gen;
	levelListNode* next;
};

typedef levelListNode* LevelList;		//il mio tipo LevelList

LevelList ListAddLevel(LevelList list, LevelGenerator level);	//Aggiunge un LevelGenerator alla lista passata

LevelGenerator ListAt(LevelList list, int index);		//Prende l'elemento in posizione index, restituisce NULL se è fuori dalla lista

void ListDeleteAll(LevelList list);						//Cancella tutta una lista

int mod(int a, int b);									//a modulo b però in modo tale che non ci siano valori negativi, dato che lo userò come indice di un array

int RandomInt(int min, int max);					

void FontSize(int a, int b);							//Setta il fontSize

bool IsKeyPressed(char key);							//Mi restituisce true se il carattere key è stato premuto

bool IsKeyPressed(int key);								//Uguale però con un intero.