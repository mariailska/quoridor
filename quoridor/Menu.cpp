//plik zawieraj¹cy cia³a metod klasy Menu
#include"Menu.h"

int Menu::print_menu() {//wypisanie menu na ekran oraz pobranie decyzji
	int choice = 0;
	while (true) {
		cout << "\n1 Gra dla dwoch graczy" << endl << "2 Gra dla jednego gracza (z komputerem)" << endl << "3 Wyswietl statystyki" << endl << "4 Opusc gre" << endl;
		cout << "Wpisz numer decyzji, ktora chcesz wybrac: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("cls");
			cout << ERROR_MSG;
			continue;
		}
		if (choice > 0 && choice < 5) {
			break;
		}
		else {
			system("cls");
			cout << ERROR_MSG;
		}
	}
	system("cls");
	cout << "Wybrano: " << choice;
	while (getchar() != '\n') {}
	return choice;
}

string Menu::take_nick(int i) {//pobranie nicku od gracza
	string nick;
	cout << "\nPodaj nick dla gracza " << i << ": ";
	cin >> nick;
	while (getchar() != '\n') {}
	return nick;
}

void Menu::edit_file(const char file_name[], string winner_name, chrono::seconds game_time) {//dopisywanie statystyk do pliku tekstowego, jeœli plik nie istnieje, jest zak³adany
	if (g.board.get_p1() != NULL && g.board.get_p2() != NULL) {
		ofstream file(file_name, ios::app);
		file << "GRACZE ROZGRYWAJACY: " << g.board.get_p1()->get_nick() << ", " << g.board.get_p2()->get_nick() << "   ZWYCIEZCA: " << winner_name <<
			" CZAS ROZGRYWKI: " << game_time.count() << " s.\n";
		file.close();
	}
}

void Menu::print_scores(const char file_name[]) {//wypisywanie danych z pliku tekstowego na ekran
	ifstream file(file_name);
	string line;
	while (getline(file, line)) {
		cout << endl << line << endl;
	}
	file.close();
}

Menu::Menu() {//wywo³ywanie (w zale¿noœci od podanej w print_menu()) decyzji opcji rozgrywki
	while (true) {
		string nick1 = "Gracz1";
		string nick2 = "BOT";
		string winner_name;
		int choice = print_menu();
		if (choice == 1) {//rozgrywka miedzy dwoma obiektami typu Human
			nick1 = take_nick(1);
			nick2 = take_nick(2);
			while (nick1 == nick2) {
				cout << "Podaj inny nick niz przeciwnik!\n";
				nick2 = take_nick(2);
			}
			Player* p1 = new Human('o', 0, nick1);
			Player* p2 = new Human('x', (BOARD_SIZE - 1) * 2, nick2);
			g = Game(p1, p2);
			chrono::seconds game_time = g.play(winner_name);
			edit_file(FILE_NAME, winner_name, game_time);
			delete p1;
			delete p2;
		}
		else if (choice == 2) {//rozgrywka miedzy obiektem typu Human a obiektem typu Bot
			nick1 = take_nick(1);
			Player* p1 = new Human('o', 0, nick1);
			Player* p2 = new Bot;
			g = Game(p1, p2);
			chrono::seconds game_time = g.play(winner_name);
			edit_file(FILE_NAME, winner_name, game_time);
			delete p1;
			delete p2;
		}
		else if (choice == 3) {
			print_scores(FILE_NAME);
		}
		else break;
	}
}