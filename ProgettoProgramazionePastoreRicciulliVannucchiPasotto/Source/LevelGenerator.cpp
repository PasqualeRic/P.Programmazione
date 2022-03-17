#include "LevelGenerator.hpp"


void LevelGenerator::row_generator() {

	Row[0].ChangeType(wall);      // inserisci il tipo muro nella mappa
	Row[LEVEL_WIDTH - 1].ChangeType(wall);

	GasGenerator(); // inserisce l'ogggetto gas nella mappa 

	int N_obstacles = N_obstacles_generator();  // ritorna il numero di ostacoli generati
	insert_obstacles(N_obstacles); // inserisci ostacoli casuali nella mappa 
}

int LevelGenerator::N_obstacles_generator() {     // funzione che ritorna il numero di ostacoli generati
	int Probability = generatore() % 100 + 1; // valore generato casualmente 
	int N_obstacles = 0; // valore di ritorno  
	int rowProbability = difficulty; // serve per creare più di un oggetto per riga 

	while (rowProbability >= 100) {  // se la difficoltà supera il cento verrà generato almeno un'ostacolo a riga  
		N_obstacles++;
		rowProbability -= 100;
	}

	// il primo rand serve per avere la percentuale che esca un'ostacolo 
	if (Probability < rowProbability) { // il ragionamento usato è: se il numero generato tra 0 e 100 è < della difficoltà allora si genererà un ostacolo
								// il parametro rowProbability non è altro che la probalità di generazione del ostacolo  
		N_obstacles++;
	}

	return  N_obstacles;
}

void LevelGenerator::GasGenerator()
{
	int Probability = generatore() % 70 + 1; // parametro che indica la possibilità che esca  un oggetto gas la percentuale è 1 ogni 150;
	if (Probability == 1) {
		bool flag;
		int n = generatore() % (LEVEL_WIDTH - 2) + 1;   //  serve per mettere il gas in un punto casuale della mappa
		do {
			ObjectType maptype = Row[n].GetType();
			if (maptype != 0) // se non è aria non posizionare l'oggetto qui
				flag = true;
			else
				flag = false;
		} while (flag == true);

		Row[n].ChangeType(gas);
	}
}

void LevelGenerator::insert_obstacles(int N_obstacles) {
	bool flag = true;
	int n; // numero casuale serve per generare una probailità
	while (N_obstacles > 0) // cicla finchè ci sono ostacoli da generare
	{
		n = generatore() % 3 + 3; // genera un numero compreso tra 3 e 4 indica quale ostacolo malus verrà generato
		ObjectType val = static_cast<ObjectType>(n);

		do {		// questo ciclo serve per verificare che non vengano sovrapposti due oggetti ( diversi da air )
			n = generatore() % (LEVEL_WIDTH - 2) + 1; // numero casuale evito di calcolare giri extra nel caso esca il primo o l'ultimo numero, ovvero i due muri 

			ObjectType maptype = Row[n].GetType();

			if (maptype != 0) // se non è aria non posizionare l'oggetto qui
				flag = true;
			else
				flag = false;

		} while (flag == true);

		Row[n].ChangeType(val);

		N_obstacles--;
	}

}

void LevelGenerator::refresh() { // reimposta la riga in object air, è necessario per l'inserimento degli ostacoli 
	ObjectType air = static_cast<ObjectType>(0);
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		Row[i].ChangeType(air);
	}
}

LevelGenerator::LevelGenerator() {          // Costruttore senza parametri  livello impostato ad 1 e seed 0
	Level = 1;
	Seed = 0;
	generatore.seed(Seed);
	//15 corrisponde al 15% che venga generato un ostacolo sulla riga, man mano che si sale di livello sale anche la probabilità
	int i = 0;

}

LevelGenerator::LevelGenerator(int seed) {	// Costruttore con parametro seed , livello impostato di default 0
	Seed = seed;
	generatore.seed(Seed);
	int i = 0;

}

LevelGenerator::LevelGenerator(int seed, int Level) {	// Costruttore con parametri  livello e seed
	Seed = seed;
	generatore.seed(Seed);
	difficulty = int((log2(Level) + 1) * difficulty);
	int i = 0;
}

Object* LevelGenerator::GetRow() {     // ritorna la riga informato oggetto  
	refresh();
	row_generator();

	
	RowHeap = NULL;
	RowHeap = new Object[LEVEL_WIDTH];
	for (int i = 0; i < LEVEL_WIDTH; i++) {
		RowHeap[i] = Row[i];
	}

	return RowHeap;
}

void LevelGenerator::PrintRow() {   // ritorna la riga in formato testuale 
	refresh();
	row_generator();

	for (int i = 0; i < LEVEL_WIDTH; i++)
	{
		Row[i].PrintAppearance();
	}
}

void LevelGenerator::Restart() { // riporta il generatore allo stato iniziale ( permette di ricominciare il  livello )
	generatore = std::mt19937(Seed);
}