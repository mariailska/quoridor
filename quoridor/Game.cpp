//plik zawieraj¹cy cia³a metod klasy Game
#include"Game.h"

//KONSTRUKTORY:
Game::Game() :board(NULL, NULL) {}

Game::Game(Player* player1, Player* player2) :board(player1, player2) {}



chrono::seconds Game::play(string& winner_name) {//obs³uga rozgrywki miêdzy dwoma obiektami Player*, zwraca czas trwania gry
	int winner = 2;//zmienna pomocnicza do przekazywania zwyciêzcy
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
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
	chrono::steady_clock::time_point stop = chrono::high_resolution_clock::now();
	chrono::seconds elapsed = chrono::duration_cast<chrono::seconds>(stop - start);
	system("cls");
	if (winner == 1) {
		winner_name = board.get_p1()->get_nick();
		cout << "\nWYGRANA GRACZA: " << board.get_p1()->get_nick() << endl;
	}
	else {
		winner_name = board.get_p2()->get_nick();
		cout << "\nWYGRANA GRACZA: " << board.get_p2()->get_nick() << endl;
	}
	return elapsed;
};

bool Game::pawn_check_legality(int direction, Player* p) {//sprawdzanie czy pionek nie napotyka krawêdzi planszy lub œcianki
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



bool Game::has_path(int x, int y, int destination) {//funkcja wywo³ywana przy sprawdzaniu "legalnoœci" stawiania œcianki (w func. wall_check_legality()), musi zwróciæ true, aby u¿ytkownicy nie blokowali swoich pionków œciankami
	vector<vector<bool>> vis(BOARD_SIZE * 2, vector<bool>(BOARD_SIZE * 2, false));//kontener 'sprawdzonych' koordynatów
	queue<coords> q;//przechowujê koordynaty x,y w kolejce ruchów czekaj¹cych na sprawdzenie
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
			Human sim_pawn(row, column);//obiekt powo³any po to, aby symulowaæ poruszanie siê pionkiem, po potencjalnych œcie¿kach 
			Player* tmp = &sim_pawn;
			if (!pawn_check_legality(dir, tmp))
				continue;  // ruch zablokowany przez œcianê lub krawêdŸ planszy

			int new_x = row, new_y = column;
			switch (dir) {
			case LEFT:  new_y = column - 2; break;
			case RIGHT: new_y = column + 2; break;
			case DOWN:  new_x = row + 2; break;
			case UP:    new_x = row - 2; break;
			}

			if (new_x < 0 || new_x >= BOARD_SIZE * 2 || new_y < 0 || new_y >= BOARD_SIZE * 2) // sprawdzam czy nowe koordyanty nie wychodz¹ poza tablicê vis
				continue;
			if (vis[new_x][new_y])
				continue;

			vis[new_x][new_y] = true;
			q.push({ new_x, new_y });
		}
	}
	return false;
}

bool Game::wall_check_legality(Wall& back_on_vec) {//sprawdzanie czy mo¿na w tym miejscu postawic œciankê
	if (board.check_wall(back_on_vec.coord_x + 1, back_on_vec.coord_y - 1) != 2 && back_on_vec.get_type() == 0) { return false; }//w zale¿noœci od typu œcianki, sprawdzam czy siê nie krzy¿uje, dla scian poziomych i pionowych
	if (board.check_wall(back_on_vec.coord_x - 1, back_on_vec.coord_y + 1) != 2 && back_on_vec.get_type() == 1) { return false; }

	bool can_go_p1 = has_path(board.get_p1()->get_pawn().coord_x, board.get_p1()->get_pawn().coord_y, (BOARD_SIZE - 1) * 2);//sprawdzam czy pionki obydwu graczy maj¹ dostêpne œcie¿ki
	bool can_go_p2 = has_path(board.get_p2()->get_pawn().coord_x, board.get_p2()->get_pawn().coord_y, 0);
	return can_go_p1 && can_go_p2;
}

void Game::make_move(Player* p) {//funkcja obs³uguj¹ca ruchy graczy
	while (true) {
		int arrow = p->load_type_of_move();//okreœlam czy ruch nastapi pionem, czy bêdzie dodawana œciana
		if (arrow != -1) {//ruch pionka
			if (arrow == 72 && !pawn_check_legality(UP, p)) { cerr << PAWN_ERR; continue; }
			else if (arrow == 80 && !pawn_check_legality(DOWN, p)) { cerr << PAWN_ERR; continue; }
			else if (arrow == 75 && !pawn_check_legality(LEFT, p)) { cerr << PAWN_ERR; continue; }
			else if (arrow == 77 && !pawn_check_legality(RIGHT, p)) { cerr << PAWN_ERR; continue; }
			p->move_pawn(arrow);
			Pawn tmp('t', 99);//pomocniczy pionek, aby okreœliæ czy w tym momencie ruch wykonuje gracz1, czy gracz2
			if (p->get_pawn() == board.get_p1()->get_pawn()) {
				tmp = board.get_p2()->get_pawn();
			}
			else {
				tmp = board.get_p1()->get_pawn();
			}
			if (p->get_pawn() == tmp) {//sytuacja gdy pionki musz¹ przez siebie przeskoczyæ
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
		else {//dostawianie œciany
			if (p->walls_vec.size() > VEC_SIZE) {
				cerr << "Wykorzystano wszystkie dostepne sciany, porusz pionkiem.\n";
				continue;
			}
			coords wall_data = p->load_wall_data();//pobranie koordynatów œciany
			int column_num = wall_data.x;
			int row_num = wall_data.y;
			if (row_num == 16 && column_num % 2 == 0) {//zapobieganie postaweiniu œciany w ostatnim wierszu tablicy Board, bo wstawi³oby tylko po³owê œcianki
				cerr << W_COORD_ERR;
				continue;
			}
			if (column_num == 17 && row_num % 2 == 1) {//zapobieganie postaweiniu œciany w ostatniej kolumnie tablicy Board z tego samego powodu co powy¿ej
				cerr << W_COORD_ERR;
				continue;
			}
			if (board.check_wall(column_num - 1, row_num) == 2) {//zapobieganie ca³oœciowemu i czêœciowemu nachodzeniu na siebie œcianek
				Wall tmp(column_num - 1, row_num);
				if (tmp.get_type() == 2) {
					cerr << W_COORD_ERR;
					continue;
				}
				p->walls_vec.push_back(Wall(column_num - 1, row_num));//roboczo dodajê œcianê do vecotra œcian, jeœli wywo³ane poni¿ej wall_check_legality() zwróci true, œciana pozostanie w vectorze
			}
			else {
				cerr << WALL_ERR;
				continue;
			}
			if (!wall_check_legality(p->walls_vec.back())) {//jeœli wall_check_legality() zwróci³o false pozbywam siê œciany z wektora œcian 
				p->walls_vec.pop_back();
				cerr << WALL_ERR;
				continue;
			}
			break;
		}
	}
}