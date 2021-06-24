#pragma once
#include <iostream>
#include <time.h>
#include <fstream>
#include <ostream>
#include <iomanip>
#include "karta.h"
#include "gracz.h"
#include "bot.h"

class Kasyno {
private:
	Gracz* gracze;
	Bot* boty;
	Karta taliaKart[52];
	int liczbaKartWTalii;
	int kartaDoWydania;
	int liczbaGraczy;
	int liczbaBotow;
public:
	Kasyno();
	Kasyno(const Kasyno& _zrodlo);
	Kasyno& operator=(const Kasyno& _zrodlo);
	~Kasyno();
	void stworzTalie();
	Karta* dajKarte();
	void tasujTalie();
	void stworzGraczy();
	void stworzBoty();
	void rozdajPoczatkowaIloscKart();
	void wyswietlTalie();
	int getIloscKart(int _ktoryGracz);
	void pokazReke();
	void ruchGracza(Gracz& _gracz);
	void ruchBota(Bot& _bot);
	bool czyWszyscySpasowali();
	void sprawdzZwyciezce();
	int podsumowanie();
	void zapiszStanGry();
	void rozgrywka();
	void graj();
};