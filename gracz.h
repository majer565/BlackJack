#pragma once
#include <iostream>
#include <string>
#include "karta.h"

class Kasyno;
class Gracz {
private:
	Kasyno* kasyno;
	Karta kartyGracza[10];
	int iloscKart;
	int sumaKart;
	bool czyPas;
	bool stan;
	char nickname[20];
public:
	Gracz();
	void wyswietlKartyGracza();
	int wezIloscKart();
	void wezKarte(Karta* _karta);
	int sprawdzIloscKart();
	int sprawdzSumeKart();
	void ustawKasyno(Kasyno* _kasyno);
	bool sprawdzCzyPas();
	void dobierzKarte(Karta* _karta);
	void pasuj();
	void ustawStan(bool _stan);
	bool sprawdzStan();
	void ustawNickname(int _numer);
	char* sprawdzNickname();
	char* sprawdzKartyGracza();
	char sprawdzFigure(int _numer);
	char sprawdzKolor(int _numer);
};