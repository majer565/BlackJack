#include "gracz.h"

Gracz::Gracz()
	: iloscKart(0)
	, sumaKart(0)
	, kartyGracza()
	, kasyno(nullptr)
	, czyPas(false)
	, stan(false)
	, nickname()
{}

void Gracz::wyswietlKartyGracza() {
	for (int i = 0; i < iloscKart; i++) {
		kartyGracza[i].wypisz();
	}
}

int Gracz::wezIloscKart() {
	return iloscKart;
}

void Gracz::wezKarte(Karta* _karta) {
	iloscKart++;
	kartyGracza[iloscKart - 1] = *_karta;
	sumaKart = kartyGracza[iloscKart - 1].getWartosc() + sumaKart;
}

void Gracz::ustawKasyno(Kasyno* _kasyno) {
	kasyno = _kasyno;
}

int Gracz::sprawdzIloscKart() {
	return iloscKart;
}

int Gracz::sprawdzSumeKart() {
	return sumaKart;
}

bool Gracz::sprawdzCzyPas() {
	return czyPas;
}

void Gracz::dobierzKarte(Karta* _karta) {
	wezKarte(_karta);
}

void Gracz::pasuj() {
	czyPas = true;
}

void Gracz::ustawStan(bool _stan) {
	stan = _stan;
}

bool Gracz::sprawdzStan() {
	return stan;
}

void Gracz::ustawNickname(int _numer) {
	std::cout << "Wprowadz nick gracza " << _numer << ": ";
	do {
		std::cin.getline(nickname, 20, '\n');
	} while (nickname[0] == '\0');
	if (std::cin.fail() == true) { 
		std::cin.clear();    
		std::cin.ignore(256, '\n'); 
	}
}

char* Gracz::sprawdzNickname() {
	return nickname;
}

char Gracz::sprawdzFigure(int _numer) {
	return kartyGracza[_numer].getFigura();
}

char Gracz::sprawdzKolor(int _numer) {
	return kartyGracza[_numer].getKolor();
}

char* Gracz::sprawdzKartyGracza() {
	char* karty = new char[iloscKart*2+1];
	int zmiennaPomoc = 0;
	for (int i = 0; i < iloscKart; i++) {
		karty[zmiennaPomoc] = kartyGracza[i].getFigura();
		//Próbowa³em zrobiæ normalny zapis do pliku z symbolami przez unicode itd
		//niestety siê nie uda³o, nie znalaz³em na to rozwi¹zania
		switch (kartyGracza[i].getKolor()) {
		case 3:
			karty[zmiennaPomoc + 1] = 'H';
			break;
		case 4:
			karty[zmiennaPomoc + 1] = 'D';
			break;
		case 5:
			karty[zmiennaPomoc + 1] = 'C';
			break;
		case 6:
			karty[zmiennaPomoc + 1] = 'S';
			break;
		}
		zmiennaPomoc = zmiennaPomoc + 2;
	}
	karty[iloscKart * 2] = '\0';
	return karty;
}