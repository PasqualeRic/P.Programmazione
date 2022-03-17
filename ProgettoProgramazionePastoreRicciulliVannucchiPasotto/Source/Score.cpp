#include "Score.hpp"

void Score::ReadFile() {
	ifstream Read_file("BestScore.txt");
	if (Read_file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			Read_file >> Name[i];
			Read_file >> BestScore[i];
		}
		Read_file.close();
	}
	else {
		for (int i = 0; i < 10; i++) // create a new file "BestScore.txt" 
		{
			Name[i] = "AAA";
			BestScore[i] = 0;
		}
	}
}

void Score::WriteFile() {
	ofstream Write_file("BestScore.txt");
	if (Write_file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			Write_file << Name[i] << " " << BestScore[i] << "\n";
		}
	}
	else
		cout << "ERROR:: Unable to open file";
}

Score::Score() {
	ReadFile();

}

void Score::PrintScore() {
	for (int i = 0; i < 10; i++)
	{
		cout << "Place: " << i + 1 << "\t Name: " << Name[i] << "\t Score: " << BestScore[i] << "\n";
	}
}

void Score::inserisci(int punteggio) {
	int i = 8;
	bool flag = true;
	if (punteggio > BestScore[9]) { // il punteggio è maggiore dell'ultima posizione quindi deve essere scritto nei BestScore
		while (flag == true) {
			if (punteggio > BestScore[i]) {
				BestScore[i + 1] = BestScore[i];
				Name[i + 1] = Name[i];
				if (i == 0) {
					cout << "SEI IN CIMA ALLA CLASSIFICA!!!  Inserisci il tuo Nome: ";
					cin >> Name[i];
					BestScore[i] = punteggio;
					flag = false;
				}
			}
			else {
				cout << "Ti sei piazzato " << i + 2 << " !!!" << "\t Inserisci il tuo Nome: ";
				cin >> Name[i + 1];
				BestScore[i + 1] = punteggio;
				flag = false;
			}
			i--;
		}
		WriteFile();
	}
}