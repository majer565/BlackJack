#include "bot.h"

Bot::Bot() 
	: odwaga(0)
	, numerBota(0)
{}

int Bot::getNumerBota() {
	return numerBota;
}

int Bot::getOdwaga() {
	return odwaga;
}

void Bot::nadajOdwage(int _odwaga) {
	odwaga = _odwaga;
}

void Bot::nadajNumerBota(int _numer) {
	numerBota = _numer;
}