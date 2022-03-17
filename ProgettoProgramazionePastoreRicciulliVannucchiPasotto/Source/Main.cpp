#include "Game.hpp"
#include "Screen.hpp"
#include "Utilities.hpp"
#include "Score.hpp"

#include <cstdio>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;
int main() {
	menu mainMenu;
	Game mainGame;

	mainMenu.first_page();							//Chiama la funzione del menù che fa partire la stampa della prima pagina
	mainGame.StartGame();							//Appena first_page restituisce (cioè ho cliccato play) posso fare partire il game

	auto b = system_clock::now();						//Tengono traccia del tempo passato fra i vari frame
	auto a = system_clock::now();						//Le variabili le metto auto perchè senno avrebbero un tipo molto lungo da scrivere ogni volta
	float frameTimeDuration = 1000 / 60;				//velocità dei frame iniziali


	while (true) {
		if(mainGame.IsGameRunning())
			frameTimeDuration = 1000 / mainGame.GetGameSpeed();	//Se sta andando il gioco la velocità è data da questo
		else {
			float frameTimeDuration = 1000 / 60.0;				//Senno è costante 
		}

		a = system_clock::now();								//prendo il tempo attuale

		duration<double, milli> work_time = a - b;				//il tempo di lavoro del frame è dato dal tempo attuale meno il tempo di quando ha iniziato a fare il lavoro del frame
		if (work_time.count() < frameTimeDuration)				//Se non è ancora tempo di un nuovo frame 
		{
			duration<double, milli> delta_ms(frameTimeDuration - work_time.count());		//quanto tempo manca al nuovo frame
			milliseconds delta_ms_duration = duration_cast<milliseconds>(delta_ms);			//lo si cata a milliseconds
			this_thread::sleep_for(milliseconds(delta_ms_duration.count()));				//per poi poter fare thread::sleep_for(milliseconds), faccio dormire il thread per quanto tempo manca al prossimo frame
		}

		b = system_clock::now();

		if (IsKeyPressed(27)) {															//27 == 'ESC', se premo 'ESC' se sono in game esce dal gioco
			mainGame.TerminateGame();
		}

		if(mainGame.IsGameRunning())												//Se il gioco sta andando faccio andare il gameLoop
			mainGame.GameLoop();
		else {
			bool startNewGame = mainMenu.second_page();								//prendo una bool, second_page restituisce True se devo far partire il gioco false altrimenti
			if (startNewGame)
				mainGame.StartNewGame();

		}
	}
}
