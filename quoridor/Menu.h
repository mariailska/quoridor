//plik zawieraj�cy deklaracje metod i pola klasy Menu
#pragma once
#include"Game.h"
#include<fstream>
#include<limits>
#include<cstdlib>

#define FILE_NAME "scores.txt"

class Menu {//klasa spinaj�ca rozgrywk� z plikiem tekstowym wynik�w oraz obs�ug� menu
private:
	Game g;
public:
	int print_menu();
	void print_scores(const char file_name[]);//wypisanie wynik�w z pliku tekstowego na ekran
	void edit_file(const char file_name[], string winner_name, chrono::seconds game_time);//dopisywanie statystyk
	string take_nick(int i);//pobranie nicku od gracza
	Menu();
};