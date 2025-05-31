//plik zawierajacy ciala metod klasy Board
#include"Board.h"

//KONSTRUKTOR:
Board::Board(Player* p1_, Player* p2_) {
	p1 = p1_;
	p2 = p2_;
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++) {
		for (int j = 0; j < 2 * BOARD_SIZE - 1; j++) {
			if (i % 2 != 0 && j % 2 != 0) {
				board[i][j] = '+';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}
}

//GETERY:
Player* Board::get_p1() { return p1; }
Player* Board::get_p2() { return p2; }

void Board::print_board(){//wypisywanie planszy po kazdym ruchu
	system("cls");
	cout << "Poruszaj sie strzalkami, aby postawic scianke wcisnij dodwolny inny przycisk,\na nastepnie podaj koordyanaty zgodne z oznaczeniami na planszy.\n";
	cout << "W przypadku stawiania scianki podawaj koordynat jej gornej lub lewej krawedzi. \n\n";
	cout << "  ";
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++) {
		cout << " " << setfill(' ') << setw(2) << i + 1;
	}
	cout << endl;
	cout << "   ";
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++) {
		cout << "---";
	}
	cout << endl;
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++) {
		cout << (char)('A' + i) << " |";
		for (int j = 0; j < 2 * BOARD_SIZE - 1; j++) {//umieszczanie na planszy Object_Board'ow
			if (i == 1) {
				int x = 0;
			}

			if (p1->get_pawn().coord_x == j && p1->get_pawn().coord_y == i) {
				cout << " " << p1->get_pawn().get_symbol() << " ";
			}
			else if (p2->get_pawn().coord_x == j && p2->get_pawn().coord_y == i) {
				cout << " " << p2->get_pawn().get_symbol() << " ";
			}
			else if (check_wall(j, i) == 0) {
				cout << " - ";
			}
			else if (check_wall(j, i) == 1) {
				cout << " | ";
			}
			else {
				cout << " " << board[i][j] << " ";
			}
		}
		cout << "|" << endl;
	}
	cout << "   ";
	for (int i = 0; i < 2 * BOARD_SIZE - 1; i++) {
		cout << "---";
	}
}

int Board::check_wall(int x, int y) {//sprawdzanie, czy scianka, ktora gracz chce postawic znalazla sie juz w zbiorze scian 
	int type = p1->check_player_wall(x, y); //(najpierw przeszukuje kontener jednego gracza, jesli takiej scianki nie ma, przeszukujê kontener drugiego gracza)
	if (type != 2) {
		return type;
	}
	return p2->check_player_wall(x, y);
}