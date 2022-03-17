#include "Game.hpp"
#include "Screen.hpp"
#include "Utilities.hpp"
#include "Score.hpp"

#include <cstdio>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

Game::Game() {
	Screen::InitScreen();								//Chiama la funzione che inizializza vari paremetri dello schermo, tipo colori, grandezza e fullscreen etc...
							
	this->InizializeGameVariable();

	for (int i = 0; i < LEVEL_WIDTH; i++) {				//é una linea tutta vuota che serve per la transizione fra livelli
		this->emptyLine[i] = Object(air);				//La creo qua cosi da non doverla creare ogni volta
	}
}

void Game::StartGame() {								//Funzione che viene chiamata quando si vuole far partire il gioco	
	this->map.StartMap();								//Fa partire la mappa, stampando i muri 
	this->macchina.reset();
	this->GameLoop();									//Fa partire il gameLoop
}

void Game::InizializeGameVariable() {
	this->currentLineAlreadyPushed = 0;					//Serve per rendere più "grandi" gli oggetti, dato che un oggetto è 3x3 la mappa mi trasforma la larghezza dell oggetto (da largo uno a 3), 
														//in Game vengono pushate 3 righe in più per ogni oggetto in modo tale da renderli 3x3. 
														//Non posso pusharli nello stesso frame sennò lo scorrimento andrebbe troppo veloce e a scatti, quindi mi prendo 3 frame consecutivi per fare il push
														//Questa variabile mi dice solamente quante righe ho gia pushato alla macchina.

	this->map = Map();									//Inizializza la variabile della mappa e della macchina,
	this->macchina;

	this->levels = NULL;								//All'inizio la lista di livelli è nulla e verrà popolata in seguito
	srand(time(NULL));
	this->currentLevelGenerator = LevelGenerator(RandomInt(0, MAXINT));		//Prendo il mio primo levelGenerator, con seed generato a caso
	this->levels = ListAddLevel(this->levels, this->currentLevelGenerator);	//e lo inserisco nella lista

	this->currentLevelIndex = 1;						//Tiene traccia del livello corrente, il primo livello = 0 viene subito saltato, ma è meglio così viene creato un momento in cui non ci sono subito ostacoli
	this->maxLevel = 1;									//Il livello massimo a cui si è arrivati
	this->frameToNextLevel = MAP_HEIGHT;				//Quanti frame di intermezzo vuoti mancano al prossimo livello
	this->maxScore = 0;									//il punteggio massimo raggiunto

	this->gameSpeed = START_GAME_SPEED;					

	this->gameIsRunning = true;
}

void Game::GameLoop() {
	Screen infoScreen = Screen(MAP_WIDTH + MAP_OFFSET_X, 0);		//Per stamparlo a sx dell'ultimo muro
	infoScreen.DrawStringAt("Livello attuale: " + to_string(this->currentLevelIndex), 0, 0, StandarWritePair);	//Mi stampa il livello attuale


	Interaction inter;
	inter.legend();													//stampa la legenda

	this->ManageMap();												//Gestisce mappa e macchina
	this->ManageCar();
}

void Game::ManageMap() {
	this->map.DrawMap();												//Stampa la mappa e poi cancella, creando un effetto scia perchè in un determinato momento c'è sia la "nuova mappa" sia la vecchia. 
																		//l'effetto scia non è visibile particolarmente, ma rende anche più fluido il gioco.
	this->map.ErasePreviousMap();										//Se mettessi prima Erase e poi Draw lampeggierebbe perchè dopo che cancello la vecchia mappa non c'è ancora quella nuova per un instante, dando effetto lampeggio.
	this->EraseNewLevelAlert();											//Cancella la scritta nuovo Livello 


	if (this->frameToNextLevel <= 0 && this->currentLineAlreadyPushed == 0)		//Se frameToNextLevel <= 0 vuol dire che non sono nel momento di transizione fra livelli e quindi devo stampare una riga del livello
		this->currentLine = this->currentLevelGenerator.GetRow();				//Se inoltre currentLineAlreadyPushed == 0 vuol dire che sono all'inizio di una riga, quindi prendo una riga dal levelGenerator
	else if (this->frameToNextLevel > 0)										//sono in una transizione fra livelli
		this->LevelTransition();
	
	this->map.PushNewRow(this->currentLine);									//Inserisco la riga da inserire


	if (this->frameToNextLevel <= 0 || this->currentLineAlreadyPushed != 0)		//Se sono nel livello, devo aumentare currentLineAlreadyPushed e fare mod 3, perchè cosi tengo traccia di quante righe "dello stesso tipo" vanno inserite
		this->currentLineAlreadyPushed = (this->currentLineAlreadyPushed + 1) % ENLARGE_FACTOR;

}

void Game::EraseNewLevelAlert() {												//Cancella la scritta del nuovo livello
	if (this->frameToNextLevel <= MAP_HEIGHT / 2 && this->frameToNextLevel > 0) {	//lo fa solamente se c'è la scritta, perchè se cancellasse sempre si creerebbe una zona in cui tutti gli oggetti vengono tagliati, frameToNextLevel > 0 cosi cancella anche l'ultima scritta
		string newLevelString = "Livello: " + to_string(this->currentLevelIndex);	//Cancella esattamente la scritta
		this->map.GetScreen().DrawStringAt(newLevelString, (MAP_WIDTH / 2) - (newLevelString.length() / 2), MAP_HEIGHT / 2, AllBlackPair); //(MAP_WIDTH / 2) - (newLevelString.length() / 2) mi serve per centrare la scritta dentro la mappa
	}
}

void Game::LevelTransition() {
	if (this->frameToNextLevel <= MAP_HEIGHT / 2 && this->frameToNextLevel > 1) {	//Stessa cosa di sopra
		string newLevelString = "Livello: " + to_string(this->currentLevelIndex);
		this->map.GetScreen().DrawStringAt(newLevelString, (MAP_WIDTH / 2) - (newLevelString.length() / 2), MAP_HEIGHT / 2, StandarWritePair);
	}

	if (this->currentLineAlreadyPushed == 0) {
		this->frameToNextLevel = this->frameToNextLevel - 1;					//Quanti frame mancano alla fine della transizione diminuisce di uno
		this->currentLine = this->emptyLine;									//La riga da inserire è quella vuota
	}
}

void Game::ManageCar() {
	bool intermezzo = this->frameToNextLevel > 0;								//mi dice se sono in un intermezzo
	this->macchina.moveCar(this->map, intermezzo);								//Muove la macchina, il bool serve per fare che quando sia in un intermezzo non guadagno punteggio

	int score = this->macchina.get_score();										//Prende lo score della macchina;
	int petrol = this->macchina.get_petrol();									

	this->maxScore = max(score, maxScore);	

	if (score < 0 || petrol <= 0) {												//se Score < 0 o petrol < 0 vuol dire che ho perso
		this->LoseGame();
	}
	else if (score >= this->currentLevelIndex * POINT_PER_LEVEL) {						//Serve per avere un range, mettiamo di essere al livello X, per salire di livello devi avere almeno uno score di scorePerLevel * X													
		this->StartNextLevel();
	}
	else if (score < (this->currentLevelIndex - 1) * POINT_PER_LEVEL - POINT_TO_GO_DOWN_LEVEL) {			//Per scendere di livello devi avere uno score di scorePerLevel * (X - 1) - un po di punti per lasciare dello spazio: se prendi un ostacolo 
		this->StartPreviousLevel();																								//poco dopo l'inizo del nuovo livello non torni indietro perforza
	}
}

void Game::StartPreviousLevel() {
	if (this->currentLevelIndex == 1) {			//Non capiterà mai, per sicurezza però lo metto. Non capita mai perchè dovrebbe essere score <= 0, però score <= 0 chiama LoseGame e non StartPreviousLevel
		return;
	}

	this->currentLevelIndex = this->currentLevelIndex - 1;					//Il livello diventa quello precendente
	LevelGenerator level = ListAt(this->levels, this->currentLevelIndex);	//Prende il generatore dalla lista

	this->StartLevel(level);												//e fa partire il livello
}

void Game::StartNextLevel() {
	this->currentLevelIndex = this->currentLevelIndex + 1;					//Il livello diventa quello successivo
	LevelGenerator level;

	if (this->currentLevelIndex > this->maxLevel) {							//Se è il livello massimo raggiunto vuol dire che ne devo creare uno nuovo						
		level = LevelGenerator(RandomInt(0, MAXINT), this->currentLevelIndex);//Prendo un generatore con quella difficoltà e con quel seed
		this->levels = ListAddLevel(this->levels, level);			//Lo aggiungo alla lista
		this->maxLevel = this->maxLevel + 1;
	}
	else {
		level = ListAt(this->levels, this->currentLevelIndex);				//Sennò lo ho già in memoria e prendo quello
	}

	this->StartLevel(level);												//e faccio partire
}

void Game::StartLevel(LevelGenerator level) {
	this->gameSpeed = START_GAME_SPEED + SPEED_DIFFERENCE_BETWEEN_LEVEL * sqrt(this->currentLevelIndex);	//aumento la velocità
	level.Restart();																						//faccio restartare il livello, cosi se è un livello gia giocato non riinizio da dove ero ma dall'inizio
	this->currentLevelGenerator = level;
	this->frameToNextLevel = MAP_HEIGHT;											//Serve per avere un momento di pausa fa frame 
}

void Game::ResetGame() {
	ListDeleteAll(this->levels);					//mi cancella tutti i dati nella lista
	this->InizializeGameVariable();					//mi reinizializza le variabili
}	

void Game::LoseGame() {	
	this->macchina.game_over();					//Chiamo il game_over nella macchina che crea la scritta GameOver
	system("cls");						
	Score score = Score();					
	score.inserisci(this->maxScore);			//Inserisco lo score se è nella TOP 10
	this->TerminateGame();						//termino il gioco
}

void Game::TerminateGame() {
	system("cls");
	this->ResetGame();							//resetta il gioco
	this->gameIsRunning = false;				
}

void Game::StartNewGame() {
	if (this->gameIsRunning)					//se lo chiamo quando il gioco stava andando termino quello precedente e ne faccio partire uno nuovos
		this->TerminateGame();
	this->InizializeGameVariable();
	this->StartGame();
}

bool Game::IsGameRunning() {
	return this->gameIsRunning;
}

int Game::GetGameSpeed() {
	return this->gameSpeed;
}