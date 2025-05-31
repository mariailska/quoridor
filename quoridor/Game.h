//plik zawierajacy deklaracje metod i pola klasy Game
#include"Board.h"
#include <chrono>
#include<queue>
#pragma once

#define WALL_ERR "\nNie mozna w tym miejscu postawic sciany (powod: konflikt z inna sciana lub odciecie drogi pionkowi)."
#define W_COORD_ERR "\nNie mozna postawic sciany w miejscu o podanych koordynatach, powtorz ruch. "
#define PAWN_ERR "\nW tym kierunku nie mozna przesunac pionka (powod: konflikt z pionkiem innego gracza, ze sciana lub krawedzia planszy)."

class Game {//klasa obslugujaca rozgrywke (kontrola legalnosci ruchow graczy, wykonywanie ruchu, liczenie czasu trwania rozgrywki)
public:
	Board board;
	void make_move(Player* p);
	bool pawn_check_legality(int direction, Player* p);
	bool wall_check_legality(Wall& back_on_vec); //sprawdza czy jest sciezka i czy mozna sciane wstawic, przekazujemy ostatnio dodana do vectora sciane
	bool has_path(int x, int y, int destination);//sprawdzanie, czy istnieja sciezka dla pionka, aby gracze nie mogli siê "blokowac" sciankami
	void play(string& winner_name);//funckja obslugujaca rozgrywke
	Game(Player* player1, Player* player2);
	Game();
};
