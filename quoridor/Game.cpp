//plik zawierajacy ciala metod klasy Game
#include"Game.h"

//KONSTRUKTORY:
Game::Game() :board(nullptr, nullptr) {}

Game::Game(Player* player1, Player* player2) :board(player1, player2) {}



void Game::play(string& winner_name) {//obsluga rozgrywki miedzy dwoma obiektami Player*, zwraca czas trwania gry
	int winner = 2;//zmienna pomocnicza do przekazywania zwyciezcy
	while (board.get_p2()->get_pawn().coord_y != 0) {
		board.print_board();
		cout << "\nPOZOSTALA LICZBA SCIANEK: " << VEC_SIZE - board.get_p1()->walls_vec.size();
		cout << "\nRUCH GRACZA: " << board.get_p1()->get_nick() << endl;
		make_move(board.get_p1());
		if (board.get_p1()->get_pawn().coord_y == (BOARD_SIZE - 1) * 2) { winner = 1; break; };
		board.print_board();
		cout << "\nPOZOSTALA LICZBA SCIANEK: " << VEC_SIZE - board.get_p2()->walls_vec.size();
		cout << "\nRUCH GRACZA: " << board.get_p2()->get_nick() << endl;
		make_move(board.get_p2());
	}
	system("cls");
	if (winner == 1) {
		winner_name = board.get_p1()->get_nick();
		cout << "\nWYGRANA GRACZA: " << board.get_p1()->get_nick() << endl;
	}
	else {
		winner_name = board.get_p2()->get_nick();
		cout << "\nWYGRANA GRACZA: " << board.get_p2()->get_nick() << endl;
	}
};

bool Game::pawn_check_legality(int direction, Player* p) {//sprawdzanie czy pionek nie napotyka krawedzi planszy lub scianki
	if (direction == UP) {
		if (p->get_pawn().coord_y > 0 && board.check_wall(p->get_pawn().coord_x, p->get_pawn().coord_y - 1) == 2) { return true; }
		return false;
	}
	else if (direction == DOWN) {
		if (p->get_pawn().coord_y < (BOARD_SIZE - 1) * 2 && board.check_wall(p->get_pawn().coord_x, p->get_pawn().coord_y + 1) == 2) { return true; }
		return false;
	}
	else if (direction == LEFT) {
		if (p->get_pawn().coord_x > 0 && board.check_wall(p->get_pawn().coord_x - 1, p->get_pawn().coord_y) == 2) { return true; }
		return false;
	}
	else if (direction == RIGHT) {
		if (p->get_pawn().coord_x < (BOARD_SIZE - 1) * 2 && board.check_wall(p->get_pawn().coord_x + 1, p->get_pawn().coord_y) == 2) { return true; }
		return false;
	}
}



bool Game::has_path(int x, int y, int destination) {//funkcja wywolywana przy sprawdzaniu "legalnosci" stawiania scianki (w func. wall_check_legality()), musi zwrocic true, aby uzytkownicy nie blokowali swoich pionkow sciankami
	vector<vector<bool>> vis(BOARD_SIZE * 2, vector<bool>(BOARD_SIZE * 2, false));//kontener 'sprawdzonych' koordynatow
	queue<coords> q;//przechowuje koordynaty x,y w kolejce ruchow czekajacych na sprawdzenie
	q.push({ x,y });
	vis[x][y] = true;
	while (!q.empty()) {
		coords p = q.front();
		q.pop();
		int row = p.x;
		int column = p.y;
		if (row == destination)
			return true;
		for (int dir = 0; dir < 4; ++dir) {
			Human sim_pawn(row, column);//obiekt powolany po to, aby symulowac poruszanie siê pionkiem, po potencjalnych sciezkach 
			Player* tmp = &sim_pawn;
			if (!pawn_check_legality(dir, tmp))
				continue;  // ruch zablokowany przez sciane lub krawedz planszy

			int new_x = row, new_y = column;
			switch (dir) {
			case LEFT:  new_y = column - 2; break;
			case RIGHT: new_y = column + 2; break;
			case DOWN:  new_x = row + 2; break;
			case UP:    new_x = row - 2; break;
			}

			if (new_x < 0 || new_x >= BOARD_SIZE * 2 || new_y < 0 || new_y >= BOARD_SIZE * 2) // sprawdzam czy nowe koordyanty nie wychodza poza tablice vis
				continue;
			if (vis[new_x][new_y])
				continue;

			vis[new_x][new_y] = true;
			q.push({ new_x, new_y });
		}
	}
	return false;
}

bool Game::wall_check_legality(Wall& back_on_vec) {//sprawdzanie czy mozna w tym miejscu postawic scianke
	if (board.check_wall(back_on_vec.coord_x + 1, back_on_vec.coord_y - 1) != 2 && back_on_vec.get_type() == 0) { return false; }//w zaleznosci od typu scianki, sprawdzam czy siê nie krzyzuje, dla scian poziomych i pionowych
	if (board.check_wall(back_on_vec.coord_x - 1, back_on_vec.coord_y + 1) != 2 && back_on_vec.get_type() == 1) { return false; }

	bool can_go_p1 = has_path(board.get_p1()->get_pawn().coord_x, board.get_p1()->get_pawn().coord_y, (BOARD_SIZE - 1) * 2);//sprawdzam czy pionki obydwu graczy maja dostepne sciezki
	bool can_go_p2 = has_path(board.get_p2()->get_pawn().coord_x, board.get_p2()->get_pawn().coord_y, 0);
	return can_go_p1 && can_go_p2;
}

void Game::make_move(Player* p) {//funkcja obslugujaca ruchy graczy
	while (true) {
		int arrow = p->load_type_of_move();//okreslam czy ruch nastapi pionem, czy bedzie dodawana sciana
		if (arrow != -1) {//ruch pionka
			if (arrow == 72 && !pawn_check_legality(UP, p)) { cerr << PAWN_ERR; continue; }
			else if (arrow == 80 && !pawn_check_legality(DOWN, p)) { cerr << PAWN_ERR; continue; }
			else if (arrow == 75 && !pawn_check_legality(LEFT, p)) { cerr << PAWN_ERR; continue; }
			else if (arrow == 77 && !pawn_check_legality(RIGHT, p)) { cerr << PAWN_ERR; continue; }
			p->move_pawn(arrow);
			Pawn tmp('t', 99);//pomocniczy pionek, aby okreslic czy w tym momencie ruch wykonuje gracz1, czy gracz2
			if (p->get_pawn() == board.get_p1()->get_pawn()) {
				tmp = board.get_p2()->get_pawn();
			}
			else {
				tmp = board.get_p1()->get_pawn();
			}
			if (p->get_pawn() == tmp) {//sytuacja gdy pionki musza przez siebie przeskoczyc
				if (arrow == 72 && board.check_wall(tmp.coord_x, tmp.coord_y - 1) == 2) {//prosty przeskok
					p->move_pawn(arrow);
				}
				else if (arrow == 72) {//przeskok na skos
					arrow = p->load_diagonal_move(UP);
					if (arrow == 75 && !pawn_check_legality(LEFT, p)) { cerr << PAWN_ERR; continue; }
					else if (arrow == 77 && !pawn_check_legality(RIGHT, p)) { cerr << PAWN_ERR; continue; }
					if (arrow != 75 && arrow != 77) { p->move_pawn(80); cerr << PAWN_ERR; continue; }
					p->move_pawn(arrow);
				}
				else if (arrow == 80 && board.check_wall(tmp.coord_x, tmp.coord_y + 1) == 2) {//prosty przeskok
					p->move_pawn(arrow);
				}
				else if (arrow == 80) {//przeskok na skos
					arrow = p->load_diagonal_move(DOWN);
					if (arrow == 75 && !pawn_check_legality(LEFT, p)) { cerr << PAWN_ERR; continue; }
					else if (arrow == 77 && !pawn_check_legality(RIGHT, p)) { cerr << PAWN_ERR; continue; }
					if (arrow != 75 && arrow != 77) { p->move_pawn(72); cerr << PAWN_ERR; continue; }
					p->move_pawn(arrow);
				}
				else if (arrow == 75 && board.check_wall(tmp.coord_x - 1, tmp.coord_y) == 2) {//prosty przeskok
					p->move_pawn(arrow);
				}
				else if (arrow == 75) {//przeskok na skos
					arrow = p->load_diagonal_move(LEFT);
					arrow = _getch();
					if (arrow == 72 && !pawn_check_legality(LEFT, p)) { cerr << PAWN_ERR; continue; }
					else if (arrow == 80 && !pawn_check_legality(RIGHT, p)) { cerr << PAWN_ERR; continue; }
					if (arrow != 72 && arrow != 80) { p->move_pawn(77); cerr << PAWN_ERR; continue; }
					p->move_pawn(arrow);
				}
				else if (arrow == 77 && board.check_wall(tmp.coord_x + 1, tmp.coord_y) == 2) {//prosty przeskok
					p->move_pawn(arrow);
				}
				else if (arrow == 77) {//przeskok na skos
					arrow = p->load_diagonal_move(RIGHT);
					arrow = _getch();
					if (arrow == 72 && !pawn_check_legality(LEFT, p)) { cerr << PAWN_ERR; continue; }
					else if (arrow == 80 && !pawn_check_legality(RIGHT, p)) { cerr << PAWN_ERR; continue; }
					if (arrow != 72 && arrow != 80) { p->move_pawn(75); cerr << PAWN_ERR; continue; }
					p->move_pawn(arrow);
				}
			}
			break;
		}
		else {//dostawianie sciany
			if (p->walls_vec.size() > VEC_SIZE) {
				cerr << "Wykorzystano wszystkie dostepne sciany, porusz pionkiem.\n";
				continue;
			}
			coords wall_data = p->load_wall_data();//pobranie koordynatow sciany
			int column_num = wall_data.x;
			int row_num = wall_data.y;
			if (row_num == 16 && column_num % 2 == 0) {//zapobieganie postaweiniu sciany w ostatnim wierszu tablicy Board, bo wstawiloby tylko polowe scianki
				cerr << W_COORD_ERR;
				continue;
			}
			if (column_num == 17 && row_num % 2 == 1) {//zapobieganie postaweiniu sciany w ostatniej kolumnie tablicy Board z tego samego powodu co powyzej
				cerr << W_COORD_ERR;
				continue;
			}
			if (board.check_wall(column_num - 1, row_num) == 2) {//zapobieganie calosciowemu i czesciowemu nachodzeniu na siebie scianek
				Wall tmp(column_num - 1, row_num);
				if (tmp.get_type() == 2) {
					cerr << W_COORD_ERR;
					continue;
				}
				p->walls_vec.push_back(Wall(column_num - 1, row_num));//roboczo dodaje sciane do vecotra scian, jesli wywolane ponizej wall_check_legality() zwroci true, sciana pozostanie w vectorze
			}
			else {
				cerr << WALL_ERR;
				continue;
			}
			if (!wall_check_legality(p->walls_vec.back())) {//jesli wall_check_legality() zwrocilo false pozbywam siê sciany z wektora scian 
				p->walls_vec.pop_back();
				cerr << WALL_ERR;
				continue;
			}
			break;
		}
	}
}