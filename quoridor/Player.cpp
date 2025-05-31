//plik zawierajacy ciala metod klasy Player oraz jej klas pochodnych: Human i Bot
#include"Player.h"

//KONSTRUKTORY:
Player::Player(char pawn_symbol, int pawn_coord_y, string nick_) :pawn(pawn_symbol, pawn_coord_y), nick(nick_) {}

Human::Human(char pawn_symbol, int pawn_coord_y, string nick_) :Player(pawn_symbol, pawn_coord_y, nick_) {}

Human::Human(int pawn_coord_y, int pawn_coord_x) :Player('t', pawn_coord_y, "tmp") { pawn.coord_x = pawn_coord_x; }

Bot::Bot() :Player('x', (BOARD_SIZE - 1) * 2, "BOT") {}


//GETERY I SETERY:
string Player::get_nick() { return nick; }

Pawn Player::get_pawn() { return pawn; }

void Player::set_pawn(int x, int y) { pawn.coord_x = x; pawn.coord_y = y; }


//METODY KLASY Player:
int Player::check_player_wall(int x, int y) {//przeszukiwanie kontenera ze sciankami konkretnego gracza
	for (auto it = walls_vec.begin(); it != walls_vec.end(); it++) {
		if (x == it->coord_x && y == it->coord_y) {
			return it->get_type();
		}
		else if (x == it->coord_x + 2 && y == it->coord_y && it->get_type() == 0) {
			return it->get_type();
		}
		else if (x == it->coord_x && y == it->coord_y + 2 && it->get_type() == 1) {
			return it->get_type();
		}
	}
	return 2;//zwracam typ 2, gdy scianka jest nieistniejaca
}

void Player::add_wall(int x, int y) {//dodawanie sciany do vektora scian
	Wall wall(x, y);
	walls_vec.push_back(wall);
}

void Player::move_pawn(int arrow) {//w zaleznosci od kierunku, trzymanego w zmiennej arrow, modyfikacja koordynatow pionka
	switch (arrow) {
	case 72:
		pawn.coord_y = pawn.coord_y - 2;
		break;
	case 80:
		pawn.coord_y = pawn.coord_y + 2;
		break;
	case 75:
		pawn.coord_x = pawn.coord_x - 2;
		break;
	case 77:
		pawn.coord_x = pawn.coord_x + 2;
		break;
	}
}


//METODY KLASY Human:
int Human::load_type_of_move() {//jesli gracz wcisnal strzalke, rozstrzygam, ze nastapi ruch pionkiem, dowolny inny klawisz - bedzie dodawal scianke
	int key = _getch();
	if (key == 0 || key == 224) {
		return _getch();
	}
	else return -1;
}

coords Human::load_wall_data() {//pobieranie wspolrzednych scianki z klawiatury, konwersja char na int dla wartosci odpowiadajacej za wiersz
	int column_num, row_num;
	char row_letter;
	cout << "\nPodaj litere wiersza (wielkosc litery nie ma znaczenia): ";
	cin >> row_letter;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cerr << ERROR_MSG;
	}
	row_letter = toupper(row_letter);
	row_num = row_letter - 'A';
	cout << "Podaj numer kolumny: ";
	while (getchar() != '\n') {}
	cin >> column_num;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << ERROR_MSG;
		column_num = -1;
	}
	while (getchar() != '\n') {}
	return { column_num, row_num };
}



int Human::load_diagonal_move(int direction) {//okreslenie kierunku ruchu skosnego, poprzez pobranie kierunku z klawiatury
	cerr << "Warunkowo pionek poruszy sie na skos (konflikt ze scianka), wcisnij strzalke: \n";
	int key = _getch();
	if (key == 0 || key == 224) {
		return _getch();
	}
	else return -1;
}


//METODY KLASY Bot
int Bot::load_type_of_move() {//losowanie wartosci (-1 - postawienie scianki, pozostale - poszczegolne kierunki)
	int key;//wartoœæ do której wpisze typ ruchu
	if (walls_vec.size() < VEC_SIZE) {
		int rd = rand() % 5;
		int tab[] = { 72, 75, 77, 80, -1 };
		key = tab[rd];
	}
	else {
		int rd = rand() % 4;
		int tab[] = { 72, 75, 77, 80 };
		key = tab[rd];
	}
	return key;
}

int Bot::load_diagonal_move(int direction) {//losowanie jednego z dwoch kierunkow w przypadku ruchu po skosie
	int rd = rand() % 2;
	int key = 0;//wartosc do ktorej wpisze kierunek ruchu na skos
	if (direction == UP || direction == DOWN) {
		int tab[] = { 75,77 };
		key = tab[rd];
	}
	if (direction == LEFT || direction == RIGHT) {
		int tab[] = { 72,80 };
		key = tab[rd];
	}
	return key;
}

coords Bot::load_wall_data() {//losowanie koordynatow scianki
	int first, sec;//wartosci do ktorych wylosuje koordynaty scianki
	coords ret;
	if (rand() % 2 == 0) {
		first = (rand() % BOARD_SIZE) * 2;
		sec = (rand() % BOARD_SIZE) * 2;
	}
	else {
		first = (rand() % (BOARD_SIZE - 1)) * 2 + 1;
		sec = (rand() % (BOARD_SIZE - 1)) * 2 + 1;
	}
	ret.x = first;
	ret.y = sec;
	return ret;
}