//plik zawieraj�cy deklaracje p�l strutury coords, p�l i metod klasy Board_Object oraz jej klas pochodnych: Pawn i Wall 
#pragma once
#define BOARD_SIZE 9

struct coords {//pomocnicza struktura do przechowywania par int'�w jako pary koordynat�w
	int x;
	int y;
	bool operator==(const coords& c);
};

class Board_Object {//klasa bazowa reprezentuj�ca obiekty na planszy, kt�re s� modyfikowalne (czyli w trakcie gry dopiero pojawiaj� si� na planszy lub zmieniaj� po�o�enie)
protected:
	char symbol;//symbol 'o', 'x' dla pionk�w, '-', '|' dla �cianek
public:
	int coord_x;
	int coord_y;
	Board_Object(char symbol_, int x, int y);
	Board_Object(int x, int y);
	char get_symbol();
	bool operator!=(const Board_Object& tmp);
	bool operator==(const Board_Object& tmp);
};

class Pawn :public Board_Object {//klasa dziedzicz�ca po Board_Object reprezentuj�ca pionek na planszy
public:
	Pawn& operator=(const Pawn& tmp);
	Pawn(char symbol_, int y);
};

class Wall :public Board_Object {//klasa dziedzicz�ca po Board_Object reprezentuj�ca �ciank� na planszy
private:
	int type;//pole okreslaj�ce, czy �cianka jest pionowa, pozioma czy nieistniej�ca
public:
	Wall(int x, int y);
	bool check_coords();
	int get_type();
	void set_type();
	void set_symbol();
};
