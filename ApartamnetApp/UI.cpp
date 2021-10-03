#include "UI.h"
#include <iostream> 
#include <limits>
#include "Error.h"
#include "Locatar.h"
#include "Myvector.h"
#include "DTO_tip_locatar.h"

using std::cout;
using std::cin;

int UI::read_integer(const string& S) const
{
	int a=0;
	cout << S;
	cin >> a;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw ValueError("Valoarea trebuie sa fie numerica!\n");
	}
	return a;
}

void UI::add_locatar()
{
	try {
		int apart = read_integer("Introdu numarul de apartament: ");
		int spr = read_integer("Introdu suprafata locuintei: ");
		string nume_pr,tip;
		cout << "Introdu numele proprietarului: ";
		cin >> nume_pr; 
		cout << "Introdu tipul locuintei: ";
		cin >> tip; 
		srv.add_locatari(apart, spr, nume_pr, tip);
		cout << "Locatar introdus cu succes!\n";
	}
	catch (const ValueError& e)
	{
		cout << e.get_msg();
	}
	catch (const RepoError& e)
	{
		cout << e.get_msg();
	}
	catch (const LocatarError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::get_all_locatari()
{	
	try {
		const Myvector< Locatar >& v = srv.get_all();
		if (!v.size())
			cout << "Lista de locatari este vida" << '\n';
		else
		{
			cout << "Lista de locatari este: " << '\n';
			for (const Locatar& locatar : v)
				cout << locatar << '\n';
		}
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::update_locatar()
{
	try {
		int apart = read_integer("Introdu numarul de apartament: ");
		int spr = read_integer("Introdu suprafata locuintei: ");
		string nume_pr, tip;
		cout << "Introdu numele proprietarului: ";
		cin >> nume_pr;
		cout << "Introdu tipul locuintei: ";
		cin >> tip;
		srv.update_locatari(apart, spr, nume_pr, tip);
		cout << "Locatar updatat cu succes!\n";
	}
	catch (const ValueError& e)
	{
		cout << e.get_msg();
	}
	catch (const RepoError& e)
	{
		cout << e.get_msg();
	}
	catch (const LocatarError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::delete_locatar()
{
	try {
		int id = read_integer("Dati id ul locatarului de sters:");
		srv.delete_locatari(id);
		cout << "Locatarul a fost sters cu succes!\n";
	}
	catch (const ValueError& e)
	{
		cout << e.get_msg();
	}
	catch (const RepoError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::search()
{
	try {
		int id = read_integer("Introdu nr apartamentului de cautat: ");
		const Locatar& rez=srv.search(id);
		cout << rez << '\n';
	}
	catch (const ValueError& e)
	{
		cout << e.get_msg();
	}
	catch (const RepoError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::filtrebytype()
{
	try {
		string tip;
		cout << "Da un tip pentru a filtra:";
		cin >> tip;
		Myvector < Locatar > rez = srv.filtrebytype(tip);
		cout << "Lista locatarilor filtrati este:" << '\n';
		for (const Locatar& x : rez)
			cout << x << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::filtrebyspr()
{
	try {
		int spr = read_integer("Introduceti suprafata: ");
		Myvector < Locatar > rez = srv.filtrebyspr(spr);
		cout << "Lista locatarilor filtrati este:" << '\n';
		for (const Locatar& x : rez)
			cout << x << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::sortbyname()
{
	try {
		Myvector < Locatar > rez = srv.sortbyname();
		cout << "Lista locatarilor sortati dupa nume este: " << '\n';
		for (const Locatar& x : rez)
			cout << x << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::sortbyspr()
{
	try {
		Myvector < Locatar > rez = srv.sortbyspr();
		cout << "Lista locatarilor sortati dupa nume este: " << '\n';
		for (const Locatar& x : rez)
			cout << x << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::sortmp()
{
	try {
		Myvector < Locatar > rez = srv.sortbytypespr();
		cout << "Lista locatarilor sortati este: " << '\n';
		for (const Locatar& x : rez)
			cout << x << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::add_list()
{
	try {
		int id = read_integer("Introdu nr de aparatament al locuintei de adaugat: ");
		srv.get_coscurent().add_list(id);
		cout << "Adaugare cu succes" << '\n';
	}
	catch (const RepoError& e)
	{
		cout << e.get_msg();
	}
	catch (const ValueError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::golire()
{
	try {
		srv.get_coscurent().goleste();
		cout << "Lista de notificare s a golit cu succes!\n";
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::add_random()
{
	try {
		int numar = read_integer("Inroduceti nr de apartamente de generat: ");
		srv.get_coscurent().random_list(numar);
		cout << "Locatarii s au aduagat cu succes" << '\n';
	}
	catch (const ValueError& e)
	{
		cout << e.get_msg();
	}
	catch (const ListError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::get_all_list()
{
	try {
		const Myvector < Locatar > rez = srv.get_coscurent().get_all_list();
		for (const Locatar& x : rez)
			cout << x << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

int UI::size_list() noexcept
{

		return srv.get_coscurent().size_list();

}

void UI::export_file_list() {
	try {
		string name_file;
		cout << "Introdu numele fisierului: ";
		cin >> name_file;
		srv.get_coscurent().export_list_file(name_file);
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::raport_tip() {
	try {
		const Myvector  < DTO_tip_locatar > v = srv.raport_type();
		for (const DTO_tip_locatar& x : v)
			cout << "Apartamentul cu tipul '" << x.get_type() << "' apare de " << x.get_cnt() << " ori " << '\n';
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::undo() {
	try {
		srv.undo();
	}
	catch (const UndoError& e)
	{
		cout << e.get_msg();
	}
	catch (const CevaEroare& e)
	{
		cout << e.get_msg();
	}
}

void UI::meniu() {
	cout << "----------------------------------Meniu----------------------------------" << '\n';
	cout << "1-Adaugare locatar!\n2-Afisare locatari!\n3-Stergere locatar!\n4-Update locatar!\n5-Cautare locatar!\n";
	cout << "6-Filtrare dupa tip!\n7-Filtrare dupa suprafata!\n8-Sortare dupa nume prorietar!\n";
	cout << "9-Sortare dupa suprafata!\n10-Sortare dupa tip apartament+suprafata!\n11-Adaugare in lista de notificare!\n";
	cout << "12-Golire lista de notificare!\n13-Adaugare random!\n14-Afisare lista de notificare!\n15-Export!\n";
	cout << "16-Raport tip apartament!\n17-Undo!\n";
	cout << "-------------------------------------------------------------------------" << '\n';

}

void UI::run() {

	while (true)
	{
		meniu();
		int cmd;
		try {

			cmd = read_integer("Dati o comanda: ");
			switch (cmd)
			{
			case 1:
				add_locatar();
				break;
			case 2:
				get_all_locatari();
				break;
			case 3:
				delete_locatar();
				break;
			case 4:
				update_locatar();
				break;
			case 5:
				search();
				break;
			case 6:
				filtrebytype();
				break;
			case 7:
				filtrebyspr();
				break;
			case 8:
				sortbyname();
				break;
			case 9:
				sortbyspr();
				break;
			case 10:
				sortmp();
				break;
			case 11:
				add_list();
				break;
			case 12:
				golire();
				break;
			case 13:
				add_random();
				break;
			case 14:
				get_all_list();
				break;
			case 15:
				export_file_list();
				break;
			case 16:
				raport_tip();
				break;
			case 17:
				undo();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!\n";
			}
			getchar();
		}
		catch (const ValueError& e)
		{
			cout << e.get_msg(); 
		}
		cout << "Numarul de apartamente din lista este: " << size_list() << '\n';
		do {
			cout << "\nPress Enter!\n";
		} while (getchar() != '\n');

	}
}