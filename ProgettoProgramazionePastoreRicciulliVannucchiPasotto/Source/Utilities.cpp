#include "Utilities.hpp"
#include <iostream>
#include <windows.h>
using namespace std;

LevelList ListAddLevel(LevelList list, LevelGenerator level) {//Inserimento in coda
	if (list == NULL) {				//Se la lista è nulla crea una nuova con il primo elemento 
		list = new levelListNode;
		list->gen = level;
		list->next = NULL;
		return list;
	}

	LevelList iterator = list;
	while (iterator->next != NULL){		//trovo l'ultimo elemento
		iterator = iterator->next;
	}
		
	iterator->next = new levelListNode;		//ci inserisco il LevelGenerator
	iterator = iterator->next;
	iterator->gen = level;
	iterator->next = NULL;
	return list;
}

LevelGenerator ListAt(LevelList list, int index) {
	int i = 1;			//Parto da i = 1 perchè quando cerco il primo livello sto passando un indice di 1, e quindi il primo elemento nella lista è 1

	bool found = false;
	while ((list != NULL) && (!found)) {	//finche ho elementi e non ho trovato l'elemento continuo
		if (i == index) found = true;		//trovo l'elemento se i == index
		else {
			list = list->next;
			i++;
		}
	}


	if (list == NULL){						//Non ho trovato l'elemento perchè la lista è troppo corta
		return NULL;  // ERRORE
	}
	return list->gen;						//Se lo ho trovato restituisco il generatore
}

void ListDeleteAll(LevelList list) {
	if (list == NULL) {						//Se la lista è vuota non faccio niente
		return;
	}
	if (list->next == NULL) {				//Se la lista ha un solo elemento cancello quell'elemento
		delete list;
		list = NULL;
	}
	else {	
		LevelList iterator = list->next;		//puntatore davanti
		LevelList iteratorBefore = list;		//puntatore dietro
		while (iterator != NULL) {				//finche il puntatore davanti non è nullo continuo
			delete iteratorBefore;				//cancello il puntatore dietro
			iteratorBefore = NULL;				//e lo setto a nullo
			iteratorBefore = iterator;			//vado avanti con il puntatore dietro
			iterator = iterator->next;
		}
		delete iteratorBefore;					//alla fine dovrò cancellare l'ultimo elemento 
		iteratorBefore = NULL;
		
	}
}

int mod(int a, int b) {
	return (a % b + b) % b;						//modulo che fa in modo che se a è negativo il suo modulo è positivo
}

int RandomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void FontSize(int a, int b) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX CurrentFontInfo = new CONSOLE_FONT_INFOEX();	//Creo una nuova variabile da caricare in seguito
	CurrentFontInfo->cbSize = sizeof(CONSOLE_FONT_INFOEX);				
	GetCurrentConsoleFontEx(out, 0, CurrentFontInfo);					//carico le informazioni
	CurrentFontInfo->dwFontSize.X = a;									//Imposto le nuove larghezze
	CurrentFontInfo->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(out, 0, CurrentFontInfo);					//Le inserisco
}

bool IsKeyPressed(char key) {
	int k = int(key) - 0x20;					//per trasformare il codice di un carattere nel suo codice del tasto
	return GetAsyncKeyState(k) & 0x8000;		//nota 0x8000 = 010000000 più tanti zeri, faccio questo perchè voglio prendere solo un valore di un bit, dato che altri bit mi dicono se il tasto era stato premuto in passato
												//prendendo solo quel bit prendo il bit che mi dice se è stato premuto in questo istante
}

bool IsKeyPressed(int key) {
	return GetAsyncKeyState(key) & 0x8000;
}