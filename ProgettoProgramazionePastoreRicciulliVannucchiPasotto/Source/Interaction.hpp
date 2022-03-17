#pragma once

#include <iostream>
#include <Windows.h>
#include "menu.hpp"
#include <cstdlib>

using namespace std;
class Interaction {

public:
	Interaction();
	int score = 0;
	double petrol = 100.0;
	//coordinate scritta
	int xS = 5;
	int yS = 10;
	void cord(int x, int y);
	void do_petrol(int inc);
	void do_score(int inc);
	void selector(unsigned short color);
	void legend();
	void game_over();

};