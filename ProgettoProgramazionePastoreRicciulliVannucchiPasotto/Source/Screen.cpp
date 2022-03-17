#include "Screen.hpp"
#include <iostream>
#include <string>
#include <windows.h>
#include "Utilities.hpp"

using  namespace std;
const int numberOfColorPair = 8;
int colorPairArray[numberOfColorPair];

void  Screen::InitScreen() {			// Funzione chiamata una singola volta all'inizio di tutto il programma che serve per inizilizzare vari valori e chiamare funzioni di inizializzazione relative alla libreria dello schermo
										//Seguono poi comandi per settare la grandezza della schermata
	Screen::SetWindowSize(CONSOLE_SIZE_X, CONSOLE_SIZE_Y);					//Setta la grandezza della console a i due valori passatti
	Screen::SetCursorOff();													//Disabilita il cursore
	Screen::DefineColorPair(StandarWritePair, WHITE, BLACK, 1, 0);			//Qui dichiaro varie coppie di colori per i vari tipi di ostacoli
	Screen::DefineColorPair(WallPair, WHITE, WHITE, 1, 1);					//Ad esempio questo vuol dire che il WallPair adesso avrà colore Bianco di Font e bianco di background, con intensità del font e del background a 1
	Screen::DefineColorPair(AirPair, BLACK, BLACK, 0, 0);
	Screen::DefineColorPair(GasPair, BLUE, BLUE, 1, 1);				
	Screen::DefineColorPair(ObstaclePair, RED, RED, 1, 1);
	Screen::DefineColorPair(NailsPair, GRAY, GREEN, 1, 0);
	Screen::DefineColorPair(PitPair, YELLOW, YELLOW, 1, 1);
	Screen::DefineColorPair(AllBlackPair, BLACK, BLACK, 0, 0);

	FontSize(20, 20);														//aumento la dimensione del font
}

Screen::Screen() {
	this->xOffset = 0;												//In caso di inizializzazione base dello Screen viene preso come offset 0 in tutte le direzione
	this->yOffset = 0;
	this->MoveCursor(0, 0);											//MoveCursor(0,0) fa in modo di settare un cursore virtuale nella posizione 0,0 relativa all'offset
	this->scHandle = GetStdHandle(STD_OUTPUT_HANDLE);				//Servirà poi per varie operazioni
}

Screen::Screen(int xOffset, int yOffset) {
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->MoveCursor(0, 0);											
	this->scHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Screen::DrawObjectAt(Object obj, int x, int y) {				//Prende un oggetto di tipo Object e due coordinate e stampa l'oggetto in quel determinato punto
	this->MoveCursor(x, y);
	switch (obj.GetType())											//In base al tipo sceglie che caso fare, serve per la gestione dei colori 
	{
	case wall:													
		Screen::SetColorPair(WallPair);
		printf("%c", obj.GetAppearance());							//Potrei non mettere il printf dentro ad ogni case, però per me è più leggibile cosi e poi evito di dover stampare il carattere vuoto dell'aria
		break;
	case obstacle:
		Screen::SetColorPair(ObstaclePair);
		printf("%c", obj.GetAppearance());
		break;
	case air:
		break;
	case pit:
		Screen::SetColorPair(PitPair);
		printf("%c", obj.GetAppearance());
		break;
	case nails:
		Screen::SetColorPair(NailsPair);
		printf("%c", obj.GetAppearance());
		break;
	case gas:
		Screen::SetColorPair(GasPair);
		printf("%c", obj.GetAppearance());
		break;
	default:													//Magari può aver senso mettere un default? in teoria non ci dovrebbe mai andare, in caso genera un eccezione
		break;
	}
	Screen::SetColorPair(StandarWritePair);
}

void Screen::DrawStringAt(string st, int x, int y, int colorPair) {		//data una stringa, due coordinate, e un intero che rappresenta un colorPair stampa la stringa con quel determinato colore
	this->MoveCursor(x, y);												//Serve per attivare la coppia di colori, se metto un color pair che è maggiore di 7 dovrebbe dare errore dato che non c'è (ho solo 7 paia di colori definiti, ma faccio che mette il colore normale.
	if (colorPair < numberOfColorPair)
		Screen::SetColorPair(colorPair);
	else
		Screen::SetColorPair(StandarWritePair);

	printf("%s", st.c_str());									
	Screen::SetColorPair(StandarWritePair);								//Disattiva la coppia di colori
}

void Screen::DrawCharAt(char c, int x, int y) {		//dato un carattere, due coordinate stampa il carattere in quella posizione
	this->MoveCursor(x, y);
	printf("%c", c);
}

void Screen::MoveCursor(int x, int y) {						//Funzione che muove il cursore in un determinato punto
	COORD coord = {x + this->xOffset, y + this->yOffset };
	SetConsoleCursorPosition(this->scHandle, coord);		//Il nome della funzione dice già tutto
}

void Screen::ResetCursorPosition() {									//Il nome dice tutto
	this->MoveCursor(0, 0);
}

void Screen::ScreenClear() {			
	system("cls");
}

void Screen::SetCursorOff() {							//disabilita la "visione" del cursore
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO info; // Funzione che gestisce le proprietà di un cursore, da poi settarle sul nostro cursore
	info.dwSize = 100;		  // La percentuale di una casella di schermo occupata dal colore del cursore, può in teoria essere quel che si vuole dato che dopo lo disattivo proprio
	info.bVisible = 0;		  // Disattiva la visibilità del cursore
	SetConsoleCursorInfo(consoleHandle, &info); //Imposta le nostre impostazioni
	
}

void Screen::SetFullScreen() { // Mette fullScreen, alla fine non la abbiamo usata ma per completezza la lascio dentro
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, 0);

}

void Screen::SetWindowSize(int width, int height) {
	HWND consoleHandle = GetConsoleWindow();
	MoveWindow(consoleHandle, 0, 0, width, height, TRUE); // Imposta la nuova dimensione della console
}

void Screen::SetColorPair(int colorPair) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, colorPairArray[colorPair] );			//Attiva un colorpair, lo prende dall'array di color pair
}

void Screen::DefineColorPair(int colorPair, int fontColor, int backgroundColor, int fontIntensity, int backgroundIntensity) { //Per definire una nuova coppia di colori, si passa l'intero che rappresenta la coppia dei colori, e i vari parametri della coppia
	if (colorPair > numberOfColorPair)			
		return;

	colorPairArray[colorPair] = fontColor | fontIntensity << 3 | backgroundColor << 4 | backgroundIntensity << 7;	// primi quattro bit sono il fontColor, i quattro bit dopo sono quelli del backgroundColor, 
																												   //quindi moltiplicando per 16 (2^4) sposto i bit di backgroundColor di 4 bit
}

