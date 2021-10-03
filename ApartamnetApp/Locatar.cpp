#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Locatar.h"


void Locatar::set_nume_pr(string nume_proprietar) {
	this->nume_pr = nume_proprietar;
}

void Locatar::set_spr(int suprafata) noexcept{
	this->spr = suprafata;
}

void Locatar::set_tip(string tip_ap) {
	this->tip = tip_ap;
}

bool Locatar::operator ==(const Locatar& locatar) const noexcept {
	return (locatar.get_apart() == this->apart);
} 

ostream& operator<<(ostream& os, const Locatar& locatar) {
	os <<"/Apartament: " << locatar.apart << "/Suprafata: " << locatar.spr;
	os << "/Nume proprietar: " << locatar.nume_pr << "/Tip: " << locatar.tip;
	return os;
}