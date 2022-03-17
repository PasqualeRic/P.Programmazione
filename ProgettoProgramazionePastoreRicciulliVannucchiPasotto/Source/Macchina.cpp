#include "Macchina.hpp"
#include "Map.hpp"
#include "Interaction.hpp"

Interaction inter;

Macchina::Macchina() {		// cotruttore

}

void Macchina::cord(int x, int y)		// Gestisce le coordinate
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Macchina::moveCar(Map mappa, bool intermezzoLivello) {	// come da nome permette il movimento della macchina


	if (_kbhit()) {											// _hbhit() controlla se è stato premuto un tasto o no
		muovi = _getch();									// getch mette in muovi il tasto premuto
		if (muovi == 'a')									// se viene premuto a la macchina viene spostata di uno a sinistra
		{
			if (xM > MAP_OFFSET_X + 1)						//questa if controlla che la macchina non esca fuori il muro sinistro
			{
				xM--;										//aggiorna la coordinata x
				stampa(car, xM, yM, muovi);					// stampa la macchina alle nuove coordinate
			}
			interaction(mappa, intermezzoLivello);			//controlla che non siano stati colpiti oggetti durante lo spostamento

		}
		else if (muovi == 'd') {						//come la if di a
			if (xM < MAP_OFFSET_X + 56) {
				xM++;
				stampa(car, xM, yM, muovi);
			}
			interaction(mappa, intermezzoLivello);

		}
	}
	else												// se non viene premuto nessun tasto la macchina viene stampata alle stesse coordinate
	{
		stampa(car, xM, yM, muovi);
		interaction(mappa, intermezzoLivello);			//controlla che non siano stati colpiti oggetti durante lo spostamento 
	}
}
void Macchina::stampa(char car[3][3], int xM, int yM, char m)	// stampa della macchina a video con le coordinate che vengono passate dalla funzione moveCar
{

	for (int e = 0; e < 3; e++)
	{
		cord(xM, yM);
		for (int j = 0; j < 3; j++)
		{
			cout << car[e][j];
		}
		yM++;

	}
	if (m == 'a')
	{
		cord(xM += 3, yM -= 2);

		cout << " ";
	}
	else if (m == 'd')
	{

		cord(xM -= 1, yM -= 2);
		cout << " ";
	}

}
void Macchina::interaction(Map mappa, bool intermezzoLivello) {	// interazione macchina oggetti
	if (intermezzoLivello)
		return;

	Object i = mappa.GetObjectAt(xM - MAP_OFFSET_X + 2, yM - MAP_OFFSET_Y + 2); // prende l'oggetto più a destra
	Object j = mappa.GetObjectAt(xM - MAP_OFFSET_X, yM - MAP_OFFSET_Y + 2);// prende l'oggetto più a sinistra
	Object k = mappa.GetObjectAt(xM - MAP_OFFSET_X + 1, yM - MAP_OFFSET_Y + 1);// prende l'oggetto più avanti

	if (i.GetType() == gas || j.GetType() == gas || k.GetType() == gas)
	{
		inter.do_petrol(40 / 3);												// aumenta la benzina
	}
	else if (i.GetType() == obstacle || j.GetType() == obstacle || k.GetType() == obstacle)
	{
		inter.do_score(200 / 3);												// diminuisce il punteggio se viene colpito l'ostacolo
	}
	else if (i.GetType() == nails || j.GetType() == nails || k.GetType() == nails)
	{
		inter.do_score(1000 / 3);												// diminuisce il punteggio se vengono presi i chiodi
	}
	else if (i.GetType() == pit || j.GetType() == pit || k.GetType() == pit)
	{
		inter.do_score(300 / 3);												// diminuisce il punteggio se viene presa una buca
	}
	else {
		inter.do_score(0);														//se non viene colpito nessuno ostacolo il punteggio aumenta normalmente
		inter.do_petrol(0);														// se non viene presa la benzina diminuisce normalmente
	}
}

int Macchina::get_score()		// ritorna lo score
{
	return inter.score;
}

void Macchina::reset() {	// ripristina il punteggio e la benzina
	inter.score = 0;
	inter.petrol = 100;
	this->xM = 30 + MAP_OFFSET_X;
	this->yM = 30 + MAP_OFFSET_Y;
}

int Macchina::get_petrol() {		// ritorna la benzina
	return inter.petrol;
}

void Macchina::game_over() {	// fa comparire a video la scritta game over
	inter.game_over();
}