#pragma once
#include "Controller_Locatari.h"
#include <string>

class UI
{
private:
	Controller_Locatari& srv; 

public:

	UI(Controller_Locatari& srv) noexcept :srv{ srv } {

	}

	UI(UI& ui) = delete;

	void run();

	/*
	* Functia citeste un intreg de la tastura 
	* Date de intrare:o referinta constanta la un mesaj de tip string
	* Date de iesire:intregul citit 
	* Functia ridica exceptii de tip ValueError daca citirea esueaza
	*/
	int read_integer(const string& S) const;

	void meniu();

	void add_locatar(); 

	void delete_locatar();

	void update_locatar();

	void search();

	void get_all_locatari();

	void filtrebytype();

	void filtrebyspr();
	
	void sortbyname();

	void sortbyspr();

	void sortmp();

	void add_list();

	void golire();

	void add_random();

	void get_all_list();

	void export_file_list();

	int size_list() noexcept;

	void raport_tip();

	void undo();

};

