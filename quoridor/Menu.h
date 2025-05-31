//plik zawieraj¹cy deklaracje metod i pola klasy Menu
#pragma once
#include"Game.h"
#include<fstream>
#include<limits>
#include<cstdlib>

#define FILE_NAME "scores.txt"

class Menu {//klasa spinaj¹ca rozgrywkê z plikiem tekstowym wyników oraz obs³ug¹ menu
private:
	Game g;
public:
	int print_menu();
	void print_scores(const char file_name[]);//wypisanie wyników z pliku tekstowego na ekran
	void edit_file(const char file_name[], string winner_name, chrono::seconds game_time);//dopisywanie statystyk
	string take_nick(int i);//pobranie nicku od gracza
	Menu();
};