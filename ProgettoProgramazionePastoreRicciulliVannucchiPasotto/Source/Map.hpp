#pragma once
#include "Constant.hpp"
#include "MapObject.hpp"
#include "Screen.hpp"


//Classe che gestisce la mappa, mantenendo in memoria tutti vari oggetti contenuti nella mappa.
/*in modo da impedire che ad ogni frames debba riaggiornare tutta la matrice degli oggetti, tengo in memoria due indici
  l'indice di inizio (startLine) e l'indice di fine (endLine) che mi rappresentano come devono essere considerate le posizioni degli oggetti nella matrice.
  Ad esempio se StartLine = 5 la quinta riga della matrice sarà in realtà la prima riga (dall'alto) che viene stampata, quindi l'ultima aggiunta.
*/
class Map {
protected:
	Object mapGrid[MAP_HEIGHT][MAP_WIDTH];	//Tengo una matrice di oggetti
	Screen mapScreen;						//Lo schermo su cui stampo
	int StartLine;
	int EndLine;

	void DrawLine(int y);			//Mi stampa una riga
	void DrawWall();				//Stampa tutti i muri della mappa
	Object* EnlargeRow(Object line[]);	//Ingrandisce una riga passata da un levelGenerator
public:
	Map();
	void StartMap();				//Fa partire la mappa

	void DrawMap();					
	void ErasePreviousMap();		//Cancella il precedente frame della mappa

	Screen GetScreen();			

	void PushNewRow(Object line[]);		//Inserisce una nuova riga dentro la mappa
	Object GetObjectAt(int x, int y);
};