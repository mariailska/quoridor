//plik zawieraj¹cy deklaracje metod i pola klasy Board
#pragma once
#include"Player.h"
#include<iomanip>

class Board {//klasa obs³uguj¹ca planszê
	Player* p1;
	Player* p2;
public:
	char board[2 * BOARD_SIZE - 1][2 * BOARD_SIZE - 1]; //tablica reprezentuj¹ca plansze
	Board(Player* p1_, Player* p2_);
	void print_board();
	int check_wall(int x, int y);//funckja wywo³uj¹ca przeszukiwanie kontenerów obydwu graczy
	Player* get_p1();
	Player* get_p2();
};