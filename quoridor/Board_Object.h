//plik zawieraj¹cy deklaracje pól strutury coords, pól i metod klasy Board_Object oraz jej klas pochodnych: Pawn i Wall 
#pragma once
#define BOARD_SIZE 9

struct coords {//pomocnicza struktura do przechowywania par int'ów jako pary koordynatów
	int x;
	int y;
	bool operator==(const coords& c);
};

class Board_Object {//klasa bazowa reprezentuj¹ca obiekty na planszy, które s¹ modyfikowalne (czyli w trakcie gry dopiero pojawiaj¹ siê na planszy lub zmieniaj¹ po³o¿enie)
protected:
	char symbol;//symbol 'o', 'x' dla pionków, '-', '|' dla œcianek
public:
	int coord_x;
	int coord_y;
	Board_Object(char symbol_, int x, int y);
	Board_Object(int x, int y);
	char get_symbol();
	bool operator!=(const Board_Object& tmp);
	bool operator==(const Board_Object& tmp);
};

class Pawn :public Board_Object {//klasa dziedzicz¹ca po Board_Object reprezentuj¹ca pionek na planszy
public:
	Pawn& operator=(const Pawn& tmp);
	Pawn(char symbol_, int y);
};

class Wall :public Board_Object {//klasa dziedzicz¹ca po Board_Object reprezentuj¹ca œciankê na planszy
private:
	int type;//pole okreslaj¹ce, czy œcianka jest pionowa, pozioma czy nieistniej¹ca
public:
	Wall(int x, int y);
	bool check_coords();
	int get_type();
	void set_type();
	void set_symbol();
};
