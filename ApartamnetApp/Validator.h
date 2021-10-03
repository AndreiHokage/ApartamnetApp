#pragma once
#include "Locatar.h"

class Validator
{

public:

	Validator() = default;

	Validator(const Validator& ot) = delete;

	/*
	* Functia valideaza un locatar
	* Date de intrare:o referinta constanta la un locatar 
	* Date de iesire:-
	* Functia ridica exceptii de tip LocatarError daca locatarul este invalid
	*/
	void valideaza(const Locatar& locatar) const;

};

