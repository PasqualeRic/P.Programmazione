#pragma once

#include <iostream> // cout/cin library 
using namespace std; 

#include <fstream> //file library

class Score {
protected:

	int BestScore[10]; // this array contains the best scores from the BestScore file
	string Name[10];  // this array contains the Name from the BestScore file

	void ReadFile(); // reads the file BestScore and insert values into the array BestScore and Name
	void WriteFile(); // writes into the file BestScore with the the values of array BestScore and Name

public:
	Score();
	void PrintScore();
	void inserisci(int punteggio);
};
