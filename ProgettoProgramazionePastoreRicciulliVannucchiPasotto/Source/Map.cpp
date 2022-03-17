#include <iostream>
#include "Map.hpp"
#include "Constant.hpp"
#include "Screen.hpp"
#include "Utilities.hpp"

Map::Map() {
	//INIZIALIZZA LA MAPPA 
	this->StartLine = 0;									//La mappa viene inizializzata con StartLine = 0 e Endline = altezza - 1
	this->EndLine = MAP_HEIGHT - 1;
	for (int y = 0; y < MAP_HEIGHT; y++) {				//Inizializzazione della mappa iniziale (si può cambiare): è una mappa con solo muri esterni e il resto vuota.
		for (int x = 0; x < MAP_WIDTH; x++) {
			this->mapGrid[y][x] = Object(air);
		}
	}
	this->mapScreen = Screen(MAP_OFFSET_X, MAP_OFFSET_Y);	//Inizializza lo schermo della mappa con l'offset che deve avere la mappa rispetto al punto del terminale in alto a sx.
}

void Map::StartMap() {
	this->DrawWall();
}

void Map::DrawWall() {
	for (int y = 0; y < MAP_HEIGHT - 1; y++) {								//Mi stampa il muro sx e dx della mappa, nota i muri non sono memorizzati dentro la matrice
		this->mapScreen.DrawObjectAt(Object(wall), 0, y);
		this->mapScreen.DrawObjectAt(Object(wall), MAP_WIDTH - 1, y);
	}
}

void Map::DrawLine(int y) {
	int realLineIndex = mod(this->StartLine + y, MAP_HEIGHT);			//Volendo prendere la riga y-esima e sapendo che non è in realtà la riga y-esima della matrice devo trasformare l'indice y in quello "interno" della matrice																		//Nota uso mod() definito da me perchè si comporta come voglio io per i numeri negativi.
	for (int i = 0; i < MAP_WIDTH; i++) {
		Object obj = this->mapGrid[realLineIndex][i];
		if (obj.GetType() != air && obj.GetType() != wall)				//Se non è un oggetto vuoto o un muro lo stampo l'oggeto
			this->mapScreen.DrawObjectAt(obj, i, y);
	}
}

void Map::DrawMap() {									//Semplicemente stampa ogni riga della mappa, Nota: non aggiungo un clear del terminale perchè magari altri elementi che non si vuole cancellare vengono cancellati. Va aggiunto nel file main
	for (int y = 0; y < MAP_HEIGHT; y++) {
		this->DrawLine(y);
	}
}

void Map::ErasePreviousMap() {
	//Primo ciclo per cancellare le traccie degli oggetti in mezzo alla mappa
	for (int y = 1; y < MAP_HEIGHT; y++) {									//Parte da y=1 perchè nel caso y=0 l'oggetto è appena "entrato" nella mappa quindi non devo cancellare una traccia
		int realLineIndex = mod(this->StartLine + y, MAP_HEIGHT);			//Serve per prendere l'oggetto nella riga giusta, dato che la y della matrice non corrisponde alla y vera
		int realLineIndexUpper = mod(this->StartLine + y - 1, MAP_HEIGHT);
		for (int x = 0; x < MAP_WIDTH; x++) {
			Object objectToDraw = this->mapGrid[realLineIndex][x];			//Prendo l'oggetto [y_vero][x]
			Object upperObject = this->mapGrid[realLineIndexUpper][x];
			if (objectToDraw.GetType() != air && objectToDraw.GetType() != wall && upperObject.GetType() == air) {		//Se è aria o un muro non devo cancellare niente, nel primo caso è ovvio, nel secondo cosi non devo ristampare tutti i muri ad ogni frame
																														//Verifico anche se l'oggetto di sopra sia aria, se è aria vuol dire che è l'ultimo oggetto del blocco 3x3, se non è aria è un blocco in mezzo e quindi non devo cancellare la scia
				this->mapScreen.DrawCharAt(' ', x, y - 1);																//Stampo sul terminale uno spazio così che si cancella la traccia				
			}
		}
	}

	//Secondo ciclo per cancellare gli oggetti a fine mappa
	for (int i = 0; i < MAP_WIDTH; i++) {
		Object obj = this->mapGrid[this->EndLine][i];	//Scorro l'ultima riga della mappa
		if (obj.GetType() != air && obj.GetType() != wall) {	//Se è aria e muro di nuovo non faccio niente
			this->mapScreen.DrawCharAt(' ', i, MAP_HEIGHT - 1);	//Se è un oggetto lo cancello
		}
	}

}

Screen Map::GetScreen() {
	return this->mapScreen;
}

void Map::PushNewRow(Object line[]) {								//Per inserire una nuova riga all'inizio (in alto) della mappa.
	Object* enlargedLine = this->EnlargeRow(line);					//prende la riga passata da un levelGenerator e poi lo allarga
	for (int i = 0; i < MAP_WIDTH; i++) {				
		this->mapGrid[this->EndLine][i] = enlargedLine[i];			//La endLine sarà la riga che viene sostituita essendo l'ultima (quella più in basso)
	}
	this->StartLine = mod(this->StartLine - 1, MAP_HEIGHT);			//decremento gli indici in modo tale da "fare andare avanti" la mappa
	this->EndLine = mod(this->EndLine - 1, MAP_HEIGHT);
}

Object Map::GetObjectAt(int x, int y) {								//Funzione che serve se si vuole prendere un oggetto in una posizione specifica. Le coordinate vanno date "normalmente", l'indice viene poi trasformato
	int realLineIndex = mod(this->StartLine + y, MAP_HEIGHT);
	return this->mapGrid[realLineIndex][x];
}

Object* Map::EnlargeRow(Object line[]) {
	Object enlargedLine[MAP_WIDTH];							//Questo è l'oggetto finale, i levelGenerator passano una riga di dimensione MAP_WIDTH/ENLARGE_FACTOR

	for (int i = 0; i < LEVEL_WIDTH; i++) {					//Scorro line
		Object obj = line[i];					
		for (int j = 0; j < ENLARGE_FACTOR; j++) {			//Per ogni oggetto di line ne metto ENLARGE_FACTOR volte in enlargedLine
			int index = j + i * ENLARGE_FACTOR;			
			enlargedLine[index] = obj;
		}
	}

	return enlargedLine;
}