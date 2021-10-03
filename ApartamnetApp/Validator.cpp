#include "Validator.h"
#include <string>
#include "Error.h"
using std::string;

void Validator::valideaza(const Locatar& locatar) const
{
	string erori=""; 
	if (locatar.get_spr() <= 0)
		erori += "Suprafata trebe sa fie pozitiva!\n";
	if (locatar.get_apart() <= 0)
		erori += "Apartament invalid!\n";
	if (locatar.get_nume_pr().compare("") == 0)
		erori += "Nume proprietar invalid!\n";
	if (locatar.get_tip().compare("") == 0)
		erori += "Tip apartamnet invalid!\n";
	if (erori.compare("") != 0)
		throw LocatarError{ erori };
}