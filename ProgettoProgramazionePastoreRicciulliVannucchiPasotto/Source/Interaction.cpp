#include "Interaction.hpp"
#include "Constant.hpp"

Interaction::Interaction(){

}

void Interaction::cord(int x, int y) //funzione che muove il cursore in un punto tramite coordinate 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Interaction::selector(unsigned short color) // funzione che colora una determinata porzione di codice

{

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hCon, color);

}
void Interaction::do_score(int x) // gestione dello score 
{
	cord(11, 3);
	cout << "       "; // per evitare sovrapposizioni nella stampa dello score
	if (x != 0) // se il valore inviato da macchina::interaction è diverso da 0, decrementa lo score di quel valore (l'utente ha colpito un ostacolo)
	{
		score -= x;
	}
	else { // altrimenti lo score viene incrementato normalmente
		score += 3;
	}
	cord(3, 3);
	cout << "Score : ";
	cord(11, 3);
	cout << score;
}

void Interaction::game_over() { // gestisce la comunicazione del game over
	system("cls");
	selector(10);
	cord(xS, yS);
	cout << "  ______                                            _______\n";
	cord(xS, yS + 1);
	cout << " /     /\\                                          /       \\ \n";
	cord(xS, yS + 2);
	cout << "/$$$$$$  \\  ______   _____  ____    ______        /$$$$$$  | __     __  ______    ______  \n";
	cord(xS, yS + 3);
	cout << "$$ | _$$/  /     /\\ /    / \/   /\   /      \\       $$ |  $$ |/\ /    / / /     \ / /        \\ \n";
	cord(xS, yS + 4);
	cout << "$$ |/    | $$$$$$  |$$$$$$ $$$$  |/$$$$$$  |      $$ |  $$ |$$  \  /$$//$$$$$$  |/$$$$$$  |\n";
	cord(xS, yS + 5);
	cout << "$$ |$$$$ | /    $$ |$$ | $$ | $$ |$$    $$ |      $$ |  $$ | $$  /$$/ $$    $$ |$$ |  $$/ \n";
	cord(xS, yS + 6);
	cout << "$$ \__ $$ |/$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/       $$ \__ $$ |  $$ $$/  $$$$$$$$/ $$ |      \n";
	cord(xS, yS + 7);
	cout << "$$    $$/ $$    $$ |$$ | $$ | $$ |$$       |      $$    $$/    $$$/   $$       |$$ |      \n";
	cord(xS, yS + 8);
	cout << " $$$$$$/   $$$$$$$/ $$/  $$/  $$/  $$$$$$$/        $$$$$$/      $/     $$$$$$$/ $$/        \n";
	selector(7);
	cord(xS+15, yS + 15);

	cout << "\t\tPremi invio per continuare...";


	
	char sel = _getch();
	
	while (sel != 13) { // fino a quando l'utente non preme invio, la scritta verrà visualizzata a video
		sel = _getch();
	}
	
	system("cls");

}
void Interaction::do_petrol(int x) // gestisce la benzina
{
	cord(3, 4);
		if (x != 0) // se il valore inviato da macchina::interaction() è diverso da 0, la benzina viene incrementata di quel valore (l'utente ha preso l'oggetto gas)
		{
			if ((petrol + x) > 100) // controlla che la benzina non vada oltre il massimo
			{
				petrol = petrol + x - ((petrol + x) - 100);
			}
			else {
				petrol += x;
			}
		}
		else { // altrimenti la benzina viene decrementata normalmente
			petrol -= 0.08;
		}
		cout << "Petrol :";
		if (petrol <= 100 && petrol >= 80) // mostra a video la quantità di benzina rimanente tramite uno schema a "batteria" 
		{
			selector(10);
			cout << " " << char(254) << char(254) << char(254) << char(254) << "  ";
			selector(7);
		}

		else if (petrol < 80 && petrol >= 60)
		{
			selector(8);
			cout << " " << char(254) << char(254) << char(254) <<  "  ";
			selector(7);
		}

		else if (petrol < 60 && petrol >= 40)
		{
			selector(6);
			cout << " " << char(254) << char(254) << "  ";
			selector(7);
		}

		else if (petrol < 40 && petrol >= 20)
		{
			selector(14);
			cout << char(254) << "    ";
			selector(7);
		}

		else if (petrol < 20) {
			selector(12);
			cout << " !    ";
			selector(7);
		}
	
}

void Interaction::legend() // mostra a video una legenda per avere sempre davanti le specifiche dei vari oggetti
{
	cord(MAP_WIDTH + MAP_OFFSET_X + 1, 3);
	selector(4);
	cout << char(254);
	selector(7);
	cout << " : Obstacle";
	cord(MAP_WIDTH + MAP_OFFSET_X + 1, 4);
	selector(9);
	cout << char(254);
	selector(7);
	cout << " : Gas";
	cord(MAP_WIDTH + MAP_OFFSET_X + 1, 5);
	selector(2);
	cout << char(254);
	selector(7);
	cout << " : Nails";
	cord(MAP_WIDTH + MAP_OFFSET_X + 1, 6);
	selector(14);
	cout << char(254);
	selector(7);
	cout << " : Pit";
}