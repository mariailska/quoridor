//plik zawierajacy deklaracje pol strutury coords, pol i metod klasy Board_Object oraz jej klas pochodnych: Pawn i Wall 
#pragma once
#define BOARD_SIZE 9

struct coords {//pomocnicza struktura do przechowywania par int'ow jako pary koordynatow
	int x;
	int y;
	bool operator==(const coords& c);
};

class Board_Object {//klasa bazowa reprezentujaca obiekty na planszy, ktore sa modyfikowalne (czyli w trakcie gry dopiero pojawiaja sie na planszy lub zmieniaja polozenie)
protected:
	char symbol;//symbol 'o', 'x' dla pionkow, '-', '|' dla scianek
public:
	int coord_x;
	int coord_y;
	Board_Object(char symbol_, int x, int y);
	Board_Object(int x, int y);
	char get_symbol();
	bool operator!=(const Board_Object& tmp);
	bool operator==(const Board_Object& tmp);
};

class Pawn :public Board_Object {//klasa dziedziczaca po Board_Object reprezentujaca pionek na planszy
public:
	Pawn& operator=(const Pawn& tmp);
	Pawn(char symbol_, int y);
};

class Wall :public Board_Object {//klasa dziedziczaca po Board_Object reprezentujaca scianke na planszy
private:
	int type;//pole okreslajace, czy scianka jest pionowa, pozioma czy nieistniejaca
public:
	Wall(int x, int y);
	bool check_coords();
	int get_type();
	void set_type();
	void set_symbol();
};
