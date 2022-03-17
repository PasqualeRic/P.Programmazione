#pragma once

#include "Constant.hpp"
#include "MapObject.hpp"
#include <math.h>
#include <random>

class LevelGenerator {
protected:

	Object Row[LEVEL_WIDTH];
	int Seed; // seed che genera il livello
	Object* RowHeap = new Object[LEVEL_WIDTH];
	std::mt19937 generatore = std::mt19937(); // generatore speudo-casuale 
	int Level;  // variabile che mi indica il livello di difficoltà dell'oggetto
	int difficulty = 6; // percentuale di crescita della difficoltà

	void row_generator(); // funzione che genera una riga
	int N_obstacles_generator();  // funzione che ritorna il numero di ostacoli generati
	void GasGenerator();
	void insert_obstacles(int N_obstacles);
	void refresh();  // reimposta la riga in object air, è necessario per l'inserimento degli ostacoli 

public:

	LevelGenerator();  // Costruttore senza parametri  livello impostato ad 1 e seed 0
	LevelGenerator(int seed);  // Costruttore con parametro seed , livello impostato di default '1'
	LevelGenerator(int seed, int Level);  // Costruttore con parametri  livello e seed

	Object* GetRow();   // ritorna la riga informato oggetto  
	void PrintRow();   // ritorna la riga in formato testuale  
	void Restart();  // riporta il generatore allo stato iniziale ( permette di ricominciare il  livello )
};

