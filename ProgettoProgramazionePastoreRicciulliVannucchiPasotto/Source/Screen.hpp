#pragma once
#include <string>
#include "Constant.hpp"
#include "MapObject.hpp"
#include <windows.h>
using  namespace std;


class Screen {
protected:
	int xOffset;			//Mantiene l'offset della schermata rispetto all'asse x e quello sotto rispetto all'asse y
	int yOffset;
	HANDLE scHandle;

public:
	Screen();

	Screen(int xOffset, int yOffset);

	void DrawObjectAt(Object obj, int x, int y);		//Prende un oggetto e lo stampa col colore relativo a quel oggetto nella posizione giusta

	void DrawStringAt(string st, int x, int y, int colorPair = StandarWritePair);	//Prende un stringa e lo stampa nella posizione giusta con il colore passato

	void DrawCharAt(char c, int x, int y);

	void MoveCursor(int x, int y);				//Muove il cursore, cosi la prossima scritta verrà scritta in (x,y)

	void ResetCursorPosition();

	static void ScreenClear();					//Cancella tutto sullo schermo

	static void SetCursorOff();					//Spegne il cursore

	static void InitScreen();					//Inizializza varie cose dello schermo, va chiamata solo una volta all'inizio

	static void SetFullScreen();				//Mette in full Screen

	static void SetWindowSize(int width, int heigth);	//Mette le dimensioni del terminale

	static void SetColorPair(int colorPair);			//Se faccio SetColorPair dopo scrivo con questo colore

	static void DefineColorPair(int colorPair, int fontColor, int backgroundColor, int fontIntensity, int backgroundIntensity); // Aggiunge un nuovo colorPair
};