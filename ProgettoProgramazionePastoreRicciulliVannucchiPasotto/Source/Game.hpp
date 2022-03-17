#pragma once
#include "Constant.hpp"
#include "MapObject.hpp"
#include "LevelGenerator.hpp"
#include "Utilities.hpp"
#include "Map.hpp"
#include "Macchina.hpp"
#include "Interaction.hpp"

class Game {
protected:
	LevelList levels;					//Mantiene in memoria varie cose, come la lista dei livelli, la macchina, la mappa, e il levelgeneratorAttuale
	Macchina macchina;
	Map map;
	LevelGenerator currentLevelGenerator;

	Object emptyLine[LEVEL_WIDTH];		//Per non doverla creare ogni volta, serve per l'intermezzo fra i vari livelli
	Object* currentLine;				//La linea da pushare nella mappa
	int currentLineAlreadyPushed;		//Quante righe dello stesso tipo sono state pushate, se devo fare oggetti 3x3 prima di prendere una nuova riga aspetto che questo sia = 3

	int currentLevelIndex;				//l'indice del livello attuale
	int maxLevel;						//il livello massimo a cui si è arrivato
	int frameToNextLevel;				//quanti frame mancano al prossimo livello (nell'intermezzo)
	int maxScore;						//lo score massimo raggiunto

	int gameSpeed;						//la velocità del gioco

	bool gameIsRunning;					//se il gioco sta andando, viene usato nel main per decidere se si è in un menu o nel gioco

	void ManageMap();					//funzione che gestisce la mappa
	void ManageCar();					//funzione che gestisce la macchina


	void InizializeGameVariable();		//Inizializza tutte le variabili, viene chiamata sia ad inizio gioco sia quando si resetta o si perde una partita

	void ResetGame();					

	void LoseGame();				

	void LevelTransition();				//funzione chiamata durante la transizione fra livelli, serve per scrivere la scritta del nuovo livello 

	void EraseNewLevelAlert();			//cancella la scritta del nuovo livello.

	void StartPreviousLevel();			//Fa partire il livello precedente (uno di quelli che si era gia incontrato)

	void StartNextLevel();				//Fa partire il livello successivo: se è il maxLevel ne genero uno nuovo senno faccio partire il livello gia visto

	void StartLevel(LevelGenerator level);

public:
	Game();

	void GameLoop();					//il loop principale che viene chiamato nel main, verrà chiamato con una frequenza stabilita nel main. (1000/gameSpeed volte al secondo)

	void StartGame();

	void TerminateGame();

	void StartNewGame();

	bool IsGameRunning();

	int GetGameSpeed();
};