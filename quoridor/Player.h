//plik zawieraj�cy deklaracje p�l i metod klasy Player oraz jej klas pochodnych: Human i Bot
#pragma once
#include"Board_Object.h"
#include<vector>
#include<string>
#include<conio.h>
#include<iostream>
#include <ctime>

#define VEC_SIZE 10 //ilo�� �cian dost�pnych dla ka�dego z graczy
#define ERROR_MSG "\nWprowadzono niemozliwe do obsluzenia dane.\n"

enum Direction { LEFT, RIGHT, DOWN, UP }; //kierunki w kt�rych mo�na si� porusza� za pomoc� strze�ek

using namespace std;

class Player {//abstrakcyjna klasa bazowa, reprezentuj�ca gracza
protected:
	Pawn pawn;
	string nick;
public:
	vector<Wall> walls_vec;//kontener do kt�rego dodawane s� �cianki konkretnego gracza, licz�cy by nie przekroczy� ilo�ci postawionych �cian, przeszukiwany przed dostawieniem ka�dej kolejnej �cianki, aby �cianki nie by�y stawiane wbrew zasadom gry Quoridor 
	virtual int load_type_of_move() = 0;//wczytanie warto�ci rozstrzygaj�cej typu ruchu (ruch pionkiem lub dodanie �cianki)
	virtual int load_diagonal_move(int direction) = 0; //wczytanie warto�ci do okreslenia kierunku ruchu w przypadku, gdy warunkowo pionek musi i�� diagonalnie
	virtual coords load_wall_data() = 0;//wczytanie koordynat�w �cianki
	void add_wall(int x, int y);
	void move_pawn(int arrow);
	string get_nick();
	Pawn get_pawn();
	void set_pawn(int x, int y);
	int check_player_wall(int x, int y);//przeszukiwanie kontenera walls_vec
	Player(char pawn_symbol, int pawn_coord_y, string nick_);
};

class Human :public Player {//pochodna klasy Player, reprezentuj�ca realnego gracza
public:
	Human(char pawn_symbol, int pawn_coord_y, string nick_);
	Human(int pawn_coord_y, int pawn_coord_x);
	int load_type_of_move();
	int load_diagonal_move(int direction);
	coords load_wall_data();
};

class Bot :public Player {//pochodna klasy Player, reprezentuj�ca gracza symulowanego przez komputer
public:
	Bot();
	int load_type_of_move();
	int load_diagonal_move(int direction);
	coords load_wall_data();
};
