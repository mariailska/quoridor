//plik zawierajacy deklaracje metod i pola klasy Menu
#pragma once
#include"Game.h"
#include<fstream>
#include<limits>
#include<cstdlib>

#define FILE_NAME "scores.txt"

class Menu {//klasa spinajaca rozgrywke z plikiem tekstowym wynikow oraz obsluga menu
private:
	Game g;
public:
	int menu_actions();//realizowanie wypisywania menu i zwracania decyzji o wybranej opcji programu
	void print_scores(const char file_name[]);//wypisanie wynikow z pliku tekstowego na ekran
	void edit_file(const char file_name[], string winner_name, chrono::seconds game_time);//dopisywanie statystyk
	string take_nick(int gamer_number);//pobranie nicku od gracza
	void gameplay();//wywolywanie (w zaleznosci od podanej w print_menu()) decyzji opcji rozgrywki
};