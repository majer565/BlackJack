#pragma once
#include "gracz.h"

class Bot : public Gracz {
	int odwaga;
	int numerBota;
public:
	Bot();
	void nadajOdwage(int _odwaga);
	void nadajNumerBota(int _numer);
	int getNumerBota();
	int getOdwaga();
};