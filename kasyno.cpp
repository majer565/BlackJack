#include "kasyno.h"

Kasyno::Kasyno()
	: gracze(nullptr)
	, liczbaKartWTalii(0)
	, kartaDoWydania(0)
	, liczbaGraczy(0)
	, liczbaBotow(0)
{
	stworzTalie();
}

Kasyno::Kasyno(const Kasyno& _zrodlo) {
	liczbaKartWTalii = _zrodlo.liczbaKartWTalii;
	liczbaBotow = _zrodlo.liczbaBotow;
	liczbaGraczy = _zrodlo.liczbaGraczy;
	kartaDoWydania = _zrodlo.kartaDoWydania;
	for (int i = 0; i < _zrodlo.liczbaKartWTalii; i++) {
		taliaKart[i] = _zrodlo.taliaKart[i];
	}
	gracze = new Gracz[liczbaGraczy];
	for (int j = 0; j < liczbaGraczy; j++) {
		gracze[j] = _zrodlo.gracze[j];
	}
	for (int k = 0; k < liczbaBotow; k++) {
		boty[k] = _zrodlo.boty[k];
	}
}

Kasyno& Kasyno::operator=(const Kasyno& _zrodlo) {
	if (&_zrodlo == this) { return *this; }
	delete[] gracze;
	delete[] boty;
	liczbaKartWTalii = _zrodlo.liczbaKartWTalii;
	liczbaBotow = _zrodlo.liczbaBotow;
	liczbaGraczy = _zrodlo.liczbaGraczy;
	kartaDoWydania = _zrodlo.kartaDoWydania;
	for (int i = 0; i < _zrodlo.liczbaKartWTalii; i++) {
		taliaKart[i] = _zrodlo.taliaKart[i];
	}
	gracze = new Gracz[liczbaGraczy];
	for (int j = 0; j < liczbaGraczy; j++) {
		gracze[j] = _zrodlo.gracze[j];
	}
	for (int k = 0; k < liczbaBotow; k++) {
		boty[k] = _zrodlo.boty[k];
	}
}

Kasyno::~Kasyno() {
	delete[] gracze;
	delete[] boty;
}

void Kasyno::stworzTalie() {
	Karta tymczasowaKarta;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			tymczasowaKarta.setKolor(i);
			tymczasowaKarta.setWartosc(j);
			taliaKart[liczbaKartWTalii] = tymczasowaKarta;
			liczbaKartWTalii++;
		}
	}
}

Karta* Kasyno::dajKarte() {
	kartaDoWydania++;
	return &taliaKart[kartaDoWydania - 1];
}

int Kasyno::getIloscKart(int _ktoryGracz) {
	return gracze[_ktoryGracz - 1].wezIloscKart();
}

void Kasyno::tasujTalie() {
	int randomCard1, randomCard2;
	Karta tymczasowaKarta;
	for (int i = 0; i < 100; i++) {
		randomCard1 = rand() % 51 + 1;
		randomCard2 = rand() % 51 + 1;
		tymczasowaKarta = taliaKart[randomCard1];
		taliaKart[randomCard1] = taliaKart[randomCard2];
		taliaKart[randomCard2] = tymczasowaKarta;
	}
}

void Kasyno::stworzGraczy() {
	std::cout << "Ilosc graczy na start (1-3): ";
	while (liczbaGraczy < 1 || liczbaGraczy > 3) {
		while (1) {
			std::cin >> liczbaGraczy;
			if (std::cin.fail()) {
				std::cout << "Blad. Sprobuj ponownie." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else break;
		}
	}
	gracze = new Gracz[liczbaGraczy];
	for (int l = 0; l < liczbaGraczy; l++) {
		gracze[l].ustawNickname(l+1);
		gracze[l].ustawKasyno(this);
	}
}

void Kasyno::stworzBoty() {
	std::cout << "Ilosc graczy wirtualnych na start (1-3): ";
	while (liczbaBotow < 1 || liczbaBotow > 3) {
		while (1) {
			std::cin >> liczbaBotow;
			if (std::cin.fail()) {
				std::cout << "Blad. Sprobuj ponownie." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else break;
		}
	}
	boty = new Bot[liczbaBotow];
	for (int l = 0; l < liczbaBotow; l++) {
		boty[l].nadajOdwage(rand()%3);
		boty[l].nadajNumerBota(l+1);
		boty[l].ustawKasyno(this);
	}
}

void Kasyno::rozdajPoczatkowaIloscKart() {
	for (int j = 0; j < liczbaGraczy; j++) {
		for (int k = 0; k < 2; k++) {
			gracze[j].wezKarte(dajKarte());
		}
	}
	for (int i = 0; i < liczbaBotow; i++) {
		for (int l = 0; l < 2; l++) {
			boty[i].wezKarte(dajKarte());
		}
	}
}

void Kasyno::pokazReke() {
	for (int i = 0; i < 2; i++) {
		gracze[i].wyswietlKartyGracza();
	}
}

void Kasyno::wyswietlTalie() {
	for (int i = 0; i < liczbaKartWTalii; i++) {
		taliaKart[i].wypisz();
		std::cout << " ";
	}
}

void Kasyno::ruchGracza(Gracz& _gracz) {
	int wybor = -1;

	if (_gracz.sprawdzSumeKart() >= 21) {
		_gracz.pasuj();
	}
	else {
		while (wybor < 0 || wybor > 1) {
			std::cout << "Twoj ruch (0 - pasuj | 1 - dobierz): ";
			while (1) {
				std::cin >> wybor;
				if (std::cin.fail()) {
					std::cout << "Blad. Sprobuj ponownie." << std::endl;
					std::cin.clear();
					std::cin.ignore(256, '\n');
				}
				else break;
			}
		}
		if (wybor == 0) {
			_gracz.pasuj();
			std::cout << _gracz.sprawdzNickname() << " pasuje." << std::endl;
		}
		else {
			_gracz.dobierzKarte(dajKarte());
		}
	}
}

void Kasyno::ruchBota(Bot& _bot) {
	switch (_bot.getOdwaga()) {
	case 0:
		if (_bot.sprawdzSumeKart() <= 12) {
			_bot.dobierzKarte(dajKarte());
			std::cout << "Bot " << _bot.getNumerBota() << " dobiera." << std::endl;
		}
		else {
			_bot.pasuj();
			std::cout << "Bot " << _bot.getNumerBota() << " pasuje." << std::endl;
		}
		break;
	case 1:
		if (_bot.sprawdzSumeKart() <= 15) {
			_bot.dobierzKarte(dajKarte());
			std::cout << "Bot " << _bot.getNumerBota() << " dobiera." << std::endl;
		}
		else {
			_bot.pasuj();
			std::cout << "Bot " << _bot.getNumerBota() << " pasuje." << std::endl;
		}
		break;
	case 2:
		if (_bot.sprawdzSumeKart() <= 17) {
			_bot.dobierzKarte(dajKarte());
			std::cout << "Bot " << _bot.getNumerBota() << " dobiera." << std::endl;
		}
		else {
			_bot.pasuj();
			std::cout << "Bot " << _bot.getNumerBota() << " pasuje." << std::endl;
		}
		break;
	}
}

bool Kasyno::czyWszyscySpasowali() {
	int zmiennaPomocnicza = 0;
	for (int i = 0; i < liczbaGraczy; i++) {
		if (gracze[i].sprawdzCzyPas()) {
			zmiennaPomocnicza++;
		}
	}
	for (int j = 0; j < liczbaBotow; j++) {
		if (boty[j].sprawdzCzyPas()) {
			zmiennaPomocnicza++;
		}
	}
	return zmiennaPomocnicza == (liczbaGraczy + liczbaBotow);
}

void Kasyno::sprawdzZwyciezce() {
	std::cout << "wygrywa: ";
	for (int j = 0; j < liczbaGraczy; j++) {
		if (gracze[j].sprawdzStan()) {
			std::cout << gracze[j].sprawdzNickname() << " ";
		}
	}
	for (int i = 0; i < liczbaBotow; i++) {
		if (boty[i].sprawdzStan()) {
			std::cout << "Bot" << boty[i].getNumerBota() << " ";
		}
	}
}

int Kasyno::podsumowanie() {
	int suma = 0;
	int wygrany = 0;
	std::cout << "--------------------------------------" << std::endl;
	for (int z = 0; z < liczbaGraczy; z++) {
		std::cout << gracze[z].sprawdzNickname() << " | Ilosc kart: " << gracze[z].sprawdzIloscKart() << " | Suma kart: " << gracze[z].sprawdzSumeKart() << " | ";
		gracze[z].wyswietlKartyGracza();
		std::cout << std::endl;
	}
	for (int x = 0; x < liczbaBotow; x++) {
		std::cout << "Bot " << boty[x].getNumerBota() << " | Ilosc kart: " << boty[x].sprawdzIloscKart() << " | Suma kart: " << boty[x].sprawdzSumeKart() << " | ";
		boty[x].wyswietlKartyGracza();
		std::cout << std::endl;
	}
	std::cout << "Podsumowanie - ";
	//Jesli kazdy przegral
	for (int l = 0; l < liczbaGraczy; l++) {
		if (gracze[l].sprawdzSumeKart() > 21) {
			wygrany++;
		}
	}
	for (int m = 0; m < liczbaBotow; m++) {
		if (boty[m].sprawdzSumeKart() > 21) {
			wygrany++;
		}
	}
	if (wygrany == (liczbaGraczy+liczbaBotow)) {
		std::cout << "zaden gracz nie wygral";
		return 0;
	}
	//Jesli gracz uzyska blackjacka
	wygrany = 0;
	for (int i = 0; i < liczbaGraczy; i++) {
		if (gracze[i].sprawdzSumeKart() == 21) {
			gracze[i].ustawStan(true);
			wygrany++;
		}
	}
	for (int n = 0; n < liczbaBotow; n++) {
		if (boty[n].sprawdzSumeKart() == 21) {
			boty[n].ustawStan(true);
			wygrany++;
		}
	}
	if (wygrany != 0) { 
		sprawdzZwyciezce();
		return 0; 
	}
	//Normalne zliczanie
	for (int j = 0; j < liczbaGraczy; j++) {
		if (gracze[j].sprawdzSumeKart() < 21) {
			if (gracze[j].sprawdzSumeKart() > suma) {
				suma = gracze[j].sprawdzSumeKart();
			}
		}
	}
	for (int o = 0; o < liczbaBotow; o++) {
		if (boty[o].sprawdzSumeKart() < 21) {
			if (boty[o].sprawdzSumeKart() > suma) {
				suma = boty[o].sprawdzSumeKart();
			}
		}
	}
	for (int k = 0; k < liczbaGraczy; k++) {
		if (gracze[k].sprawdzSumeKart() == suma) {
			gracze[k].ustawStan(true);
		}
	}
	for (int p = 0; p < liczbaBotow; p++) {
		if (boty[p].sprawdzSumeKart() == suma) {
			boty[p].ustawStan(true);
		}
	}
	sprawdzZwyciezce();
}

void Kasyno::zapiszStanGry() {
	std::ofstream plik;
	plik.open("stanGry.txt", std::ifstream::out);
	for (int i = 0; i < liczbaGraczy; i++) {
		plik << std::left << std::setw(25) << gracze[i].sprawdzNickname()
			 << std::left << std::setw(15)<< std::setfill(' ') << gracze[i].sprawdzKartyGracza();
		plik << std::right << std::setw(4) << gracze[i].sprawdzSumeKart() << std::endl;
	}
	for (int j = 0; j < liczbaBotow; j++) {
		plik << std::left << "Bot" << j+1 << std::setw(21) << " "
			 << std::left << std::setw(15) << std::setfill(' ') << boty[j].sprawdzKartyGracza();
		plik << std::right << std::setw(4) << boty[j].sprawdzSumeKart() << std::endl;
	}
	plik.close();
}

void Kasyno::rozgrywka() {
	for (int i = 0; i < liczbaGraczy; i++) {
		if (!gracze[i].sprawdzCzyPas()) {
			std::cout << gracze[i].sprawdzNickname() << " | Ilosc kart: " << gracze[i].sprawdzIloscKart() << " | Suma kart: " << gracze[i].sprawdzSumeKart() << " | ";
			gracze[i].wyswietlKartyGracza();
			std::cout << std::endl;
			ruchGracza(gracze[i]);
		}
		else {
			std::cout << gracze[i].sprawdzNickname() << " pasuje." << std::endl;
		}
	}
	for (int j = 0; j < liczbaBotow; j++) {
		if (!boty[j].sprawdzCzyPas()) {
			std::cout << "Bot " << boty[j].getNumerBota() << " | Ilosc kart: " << boty[j].sprawdzIloscKart() << " | Suma kart: " << boty[j].sprawdzSumeKart() << " | ";
			boty[j].wyswietlKartyGracza();
			std::cout << std::endl;
			ruchBota(boty[j]);
		}
		else {
			std::cout << "Bot " << boty[j].getNumerBota() << " pasuje." << std::endl;
		}
	}
}

void Kasyno::graj() {
	//Przydzielenie ilosci graczy
	stworzGraczy();
	stworzBoty();
	//Przetasowanie talii
	tasujTalie();
	//Rozdanie pierwszych kart graczom
	rozdajPoczatkowaIloscKart();
	//Rozgrywka
	system("cls");
	while (1) {
		rozgrywka();
		if (czyWszyscySpasowali()) {
			podsumowanie();
			//Zapisanie stanu gry
			zapiszStanGry();
			//Przygotowanie pod nowa gre
			kartaDoWydania = 0;
			liczbaGraczy = 0;
			liczbaBotow = 0;
			break;
		}
	}
}