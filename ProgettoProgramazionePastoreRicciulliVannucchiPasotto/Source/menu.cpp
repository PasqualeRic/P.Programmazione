#include "menu.hpp"
#include "Score.hpp"

menu::menu() {

}

void menu::cord(int x, int y)  //funzione che muove il cursore in un punto tramite coordinate 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void menu::selector(unsigned short color){  //imposta la scrittura in un determinato colore

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);  //prendiamo ciò che sarà dato in output

	SetConsoleTextAttribute(hCon, color);
}

bool  menu::second_page() {  //gestione della pagina principale
	y_secInt=22;
	cord(x_secInt, y_secInt); // disegno il menu
	cout << " Gioca\n";
	cord(x_secInt, y_secInt + 1);
	cout << " Istruzioni\n";
	cord(x_secInt, y_secInt + 2);
	cout << " Best scores\n";
	cord(x_secInt, y_secInt + 3);
	cout << " Esci\n";
	cord(x_secInt, y_secInt + 4);
	cout << " Una volta fatta la selezione premere invio\n";
	back();

	sel = 0;
	while (sel != 13)	// controllo che l'utente non confermi la sua scelta
	{
		cord(x_secInt, y_secInt);
		cout << "[";
		interaction();
	}
	if (sel == 13)		// l'utente ha scelto cosa fare e tramite le coordinate porta l'utente sulla pagina scelta
	{
		if (y_secInt == 22)
		{
			system("cls");
			return true;
		}
		else if (y_secInt == 23)
		{
			system("cls");
			return istruction();
		}
		else if (y_secInt == 24)
		{
			system("cls");
			return best_scores();
		}
		else if (y_secInt == 25)
		{
			system("cls");
			cord(38, 15);
			cout << "Gioco terminato";
			exit(0);
		}
	}
	return false;
}

void menu::back() // funzione che mostra a video il logo del gioco
{
	selector(10);
	cord(xS, yS);
	cout << "	                                                    \n";
	cord(xS, yS+1);
	cout << "	                                    __        __    \n";
	cord(xS, yS+2);
	cout << "	    _______   ______    ______     /  |      /  |   \n";
	cord(xS, yS+3);
	cout << "	   /       | /      \  /      \    __$$ |__  __$$ |__ \n";
	cord(xS, yS+4);
	cout << "	  /$$$$$$$/  $$$$$$  |/$$$$$$  |/  $$    |/  $$    |\n";
	cord(xS, yS+5);
	cout << "	  $$ |       /    $$ |$$ |  $$/ $$$$$$$$/ $$$$$$$$/ \n";
	cord(xS, yS+6);
	cout << "	  $$ \_____ /$$$$$$$  |$$ |         $$ |      $$ |   \n";
	cord(xS, yS+7);
	cout << "	  $$       |$$    $$ |$$ |         $$/       $$/    \n";
	cord(xS, yS+8);
	cout << "	   $$$$$$$/  $$$$$$$/ $$/                           \n";
	selector(7);
}
void menu::interaction() // gestisce la navigazione nel menu della pagina principale
{
	sel = _getch();
	if (sel == 's' && y_secInt <= 24) // se l'utente preme s scende con il cursore
	{
		cord(x_secInt, y_secInt += 1);
		cout << "[";
		cord(x_secInt, y_secInt - 1);
		cout << " ";
	}
	else if (sel == 'w' && y_secInt >22 ) // altrimenti se preme w sale con il cursore
	{
		cord(x_secInt, y_secInt -= 1);
		cout << "[";
		cord(x_secInt, y_secInt +1);
		cout << " ";
	}
}

bool menu::istruction() { // pagina contenente le istruzioni del gioco
	back();
	cord(x_secInt, y_secInt);
	cout << "ISTRUZIONI DEL GIOCO\n";
	cout << "(1) Il tuo compito e' quello di schivare gli oggetti. Per fare cio', muovi la macchina in tempo. Piu' il punteggio sale, piu' aumenta la difficolta', ma occhio alla benzina! Se il punteggio scende a 0, hai perso.\n";
	cout << "(2) Comandi : \n'a' : Muovi a sinistra\n'd' : Muovi a destra\n";
	cout << "Per terminare il gioco in un qualunque momento, premere 'esc' - ATTENZIONE - USCENDO DAL GIOCO IL PUNTEGGIO VERRA' PERSO \n";
	cout << "Premere esc per tornare al menu\n";
	sel = _getch();
	if (sel ==  27) // se si preme esc si torna alla pagina principale
	{
		system("cls");
		return second_page();
	}
	else if (sel != 13)
	{
		system("cls");
		return istruction();
	}
}

bool menu::best_scores() { // pagina contenente i migliori punteggi ottenuti
	Score Score;
	back();
	cord(x_secInt, y_secInt);
	cord(x_secInt, y_secInt);
	cout << "\n";
	Score.PrintScore(); // richiamo della funzione che stampa a video i migliori punteggi
	cout << "Premere esc per tornare al menu\n";
	sel = _getch();
	if (sel == 27)
	{
		system("cls");
		return second_page();
	}
	else if (sel != 13)
	{
		system("cls");
		return best_scores();
	}
}

void menu::first_page() {	// pagina di avvio del gioco 
	back();
	cord(x_firstPage, y_firstPage);
	cout << "Premi invio per continuare...";
	
	char sel = _getch();
	if (sel == 13)
	{
		system("cls");
		second_page();
	}
	else if(sel != 13)
	{
		system("cls");
		first_page();
	}
}

