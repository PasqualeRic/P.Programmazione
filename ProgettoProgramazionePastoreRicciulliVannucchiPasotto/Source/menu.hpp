#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include "Constant.hpp"
using namespace std;
class menu
{
public:
	menu();
	char sel = 'z';
	//coordinate prima pagina
	int x_firstPage = CONSOLE_SIZE_X / 25;
	int y_firstPage = CONSOLE_SIZE_Y / 30;
	//coordinate interazione e seconda pagina
	int x_secInt = CONSOLE_SIZE_X / 25;
	int y_secInt = CONSOLE_SIZE_Y / 30;
	//coordinate scritta
	int xS = CONSOLE_SIZE_X / 35;
	int yS = CONSOLE_SIZE_Y / 80;
	void cord(int x, int y);
	void first_page();
	bool second_page();
	bool best_scores();
	bool istruction();
	void interaction();
	void back();
	void selector(unsigned short color);
};