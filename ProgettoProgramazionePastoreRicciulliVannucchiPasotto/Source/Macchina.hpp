#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include "Map.hpp"
#include <stdio.h>



class Macchina {

public:

	Macchina();
	char car[3][3] = { {' ', '*', ' '},
					   {'*','M','*'},
					   {' ','*',' '} };
	int xM=30+MAP_OFFSET_X;
	int yM=30+MAP_OFFSET_Y;
	int Gas = 100;
	int punti = 0;
	char muovi = 'k';
	void cord(int x, int y);
	void moveCar(Map mappa, bool intermezzoLivello);
	void stampa(char car[3][3], int xM, int yM, char m);
	//void muoviCar(char car[3][3], float xM, float yM);
	void interaction(Map mappa, bool intermezzoLivello);
	int get_score();
	void reset();
	int get_petrol();
	void game_over();
};
