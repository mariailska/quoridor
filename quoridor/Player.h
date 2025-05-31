//plik zawierajacy deklaracje pol i metod klasy Player oraz jej klas pochodnych: Human i Bot
#pragma once
#include"Board_Object.h"
#include<vector>
#include<string>
#include<conio.h>
#include<iostream>
#include <ctime>

#define VEC_SIZE 10 //ilosc scian dostepnych dla kazdego z graczy
#define ERROR_MSG "\nWprowadzono niemozliwe do obsluzenia dane.\n"

enum Direction { LEFT, RIGHT, DOWN, UP }; //kierunki w ktorych mozna siê poruszac za pomoca strzalek

using namespace std;

class Player {//abstrakcyjna klasa bazowa, reprezentujaca gracza
protected:
	Pawn pawn;
	string nick;
public:
	vector<Wall> walls_vec;//kontener do ktorego dodawane sa scianki konkretnego gracza, licz¹cy by nie przekroczyc ilosci postawionych scian, przeszukiwany przed dostawieniem kazdej kolejnej scianki, aby scianki nie byly stawiane wbrew zasadom gry Quoridor 
	virtual int load_type_of_move() = 0;//wczytanie wartosci rozstrzygajacej typu ruchu (ruch pionkiem lub dodanie scianki)
	virtual int load_diagonal_move(int direction) = 0; //wczytanie wartosci do okreslenia kierunku ruchu w przypadku, gdy warunkowo pionek musi isc diagonalnie
	virtual coords load_wall_data() = 0;//wczytanie koordynatow scianki
	void add_wall(int x, int y);
	void move_pawn(int arrow);
	string get_nick();
	Pawn get_pawn();
	void set_pawn(int x, int y);
	int check_player_wall(int x, int y);//przeszukiwanie kontenera walls_vec
	Player(char pawn_symbol, int pawn_coord_y, string nick_);
};

class Human :public Player {//pochodna klasy Player, reprezentujaca realnego gracza
public:
	Human(char pawn_symbol, int pawn_coord_y, string nick_);
	Human(int pawn_coord_y, int pawn_coord_x);
	int load_type_of_move();
	int load_diagonal_move(int direction);
	coords load_wall_data();
};

class Bot :public Player {//pochodna klasy Player, reprezentujaca gracza symulowanego przez komputer
public:
	Bot();
	int load_type_of_move();
	int load_diagonal_move(int direction);
	coords load_wall_data();
};
