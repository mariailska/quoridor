#include "Menu.h"

int main() {
	srand(static_cast<unsigned>(std::time(nullptr)));
	Menu menu;
	menu.gameplay();
	return 0;
}