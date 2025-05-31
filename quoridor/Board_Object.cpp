//plik zawierajacy ciala metod klasy Board_Object oraz jej klas pochodnych: Pawn i Wall oraz cialo przeciazonego operatora==() strutury coords
#include "Board_Object.h"

//KONSTRUTORY:
Board_Object::Board_Object(char symbol_, int x, int y) :symbol(symbol_), coord_x(x), coord_y(y) {}

Board_Object::Board_Object(int x, int y) :coord_x(x), coord_y(y) {}

Pawn::Pawn(char symbol_, int y) :Board_Object(symbol_, BOARD_SIZE - 1, y) {}

Wall::Wall(int x, int y) : Board_Object(x, y) {
	set_type();
	set_symbol();
}

//PRZECIAZONE OPERATORY:
bool coords::operator==(const coords& c) {//przeciazony operator==() dla struct'a coords
	if (x == c.x && y == c.y) return true;
	return false;
}

bool Board_Object::operator!=(const Board_Object& tmp) {//przeciazone operatory != i == klasy Board_Object
	if (this->coord_x != tmp.coord_x || this->coord_y != tmp.coord_y) { return true; }
	return false;
}

bool Board_Object::operator==(const Board_Object& tmp) {
	if (this->coord_x == tmp.coord_x && this->coord_y == tmp.coord_y) { return true; }
	return false;
}

Pawn& Pawn::operator=(const Pawn& tmp) {//przeciazony operator=() klasy Pawn
	this->coord_x = tmp.coord_x;
	this->coord_y = tmp.coord_y;
	this->symbol = tmp.symbol;
	return *this;
}

//POZOSTALE METODY:
char Board_Object::get_symbol() { return symbol; }

int Wall::get_type() { return type; }

bool Wall::check_coords() {//pomocnicza funkcja, sprawdzajaca czy scianka nie wystaje poza krawedzie planszy
	return (coord_x >= 0 && coord_x <= (BOARD_SIZE - 1) * 2 && coord_y >= 0 && coord_y <= (BOARD_SIZE - 1) * 2);
}

void Wall::set_type() {
	if (coord_x % 2 == 0 && coord_y % 2 != 0 && check_coords()) {
		type = 0; //typ poziomy
	}
	else if (coord_x % 2 != 0 && coord_y % 2 == 0 && check_coords()) {
		type = 1; //typ pionowy
	}
	else {
		type = 2; //typ trashowy, dla koordynatow na ktorych nie ma sciany
	}
}

void Wall::set_symbol() {
	if (type == 0) {
		symbol = '-';
	}
	else {
		symbol = '|';
	}
}

