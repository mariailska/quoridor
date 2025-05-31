//plik zawierajacy deklaracje metod i pola klasy Board
#pragma once
#include"Player.h"
#include<iomanip>

class Board {//klasa obslugujaca plansze
	Player* p1;
	Player* p2;
public:
	char board[2 * BOARD_SIZE - 1][2 * BOARD_SIZE - 1]; //tablica reprezentujaca plansze
	Board(Player* p1_, Player* p2_);
	void print_board();
	int check_wall(int x, int y);//funckja wywolujaca przeszukiwanie kontenerow obydwu graczy
	Player* get_p1();
	Player* get_p2();
};