//plik zawieraj¹cy cia³a metod klasy Board_Object oraz jej klas pochodnych: Pawn i Wall oraz cia³o przeci¹¿onego operatora==() strutury coords
#include "Board_Object.h"

//KONSTRUTORY:
Board_Object::Board_Object(char symbol_, int x, int y) :symbol(symbol_), coord_x(x), coord_y(y) {}

Board_Object::Board_Object(int x, int y) :coord_x(x), coord_y(y) {}

Pawn::Pawn(char symbol_, int y) :Board_Object(symbol_, BOARD_SIZE - 1, y) {}

Wall::Wall(int x, int y) : Board_Object(x, y) {
	set_type();
	set_symbol();
}

//PRZECI¥¯ONE OPERATORY:
bool coords::operator==(const coords& c) {//przeci¹¿ony operator==() dla struct'a coords
	if (x == c.x && y == c.y) return true;
	return false;
}

bool Board_Object::operator!=(const Board_Object& tmp) {//przeci¹¿one operatory != i == klasy Board_Object
	if (this->coord_x != tmp.coord_x || this->coord_y != tmp.coord_y) { return true; }
	return false;
}

bool Board_Object::operator==(const Board_Object& tmp) {
	if (this->coord_x == tmp.coord_x && this->coord_y == tmp.coord_y) { return true; }
	return false;
}

Pawn& Pawn::operator=(const Pawn& tmp) {//przeci¹¿ony operator=() klasy Pawn
	this->coord_x = tmp.coord_x;
	this->coord_y = tmp.coord_y;
	this->symbol = tmp.symbol;
	return *this;
}

//POZOSTA£E METODY:
char Board_Object::get_symbol() { return symbol; }

int Wall::get_type() { return type; }

bool Wall::check_coords() {//pomocnicza funkcja, sprawdzaj¹ca czy œcianka nie wystaje poza krawêdzie planszy
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
		type = 2; //typ trashowy, dla koordynatów na których nie ma œciany
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

