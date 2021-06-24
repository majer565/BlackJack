#include "karta.h"
#include "gracz.h"
#include "kasyno.h"
#include "bot.h"

int main() {
	srand(time(NULL));
	Kasyno jeden;
	int wybor = -1;
	while (1) {
		jeden.graj();
		std::cout << std::endl;
		std::cout << "Czy zaczac kolejna rozgrywke(1 - TAK | x - NIE): ";
		std::cin >> wybor;
		if (wybor == 1) { system("cls"); }
		else { break; }
	}
}