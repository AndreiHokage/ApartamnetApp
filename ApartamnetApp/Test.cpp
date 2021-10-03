#include "Test.h"
#include "Locatar.h"
#include "Validator.h"
#include "Error.h"
#include "Repo_locatari.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Myvector.h"
#include "Controller_Locatari.h"
#include "Iterator_myvector.h"
#include "DTO_tip_locatar.h"
#include "Repo_locatari_file.h"
using std::vector;
using std::string;

void Test::run_all_tests()
{
	test_sortbyname();
	test_filtrebyspr();
	test_add_myvector();
	test_locatar();
	test_set_locatar();
	test_validare_locatar();
	test_add_repo();
	test_delete_repo();
	test_update_repo();
	test_add_service();
	test_delete_service();
	test_update_service();
	test_search_repo();
	test_search_service();
	test_get_all_myvector();
	test_delete_myvector();
	test_filtrebytype();
	test_sortbyspr();
	test_sortmp();
	test_add_list();
	test_raport_type();
	test_undo_add();
	test_undo_delete();
	test_undo_update();
}

void Test::test_delete_myvector()
{
	Myvector< Locatar > v;
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	Locatar locatar3{ 127,342,"Radu","garsoniera" };
	v.push_back(locatar1);
	v.push_back(locatar2); 
	v.push_back(locatar3);

	Myvector < Locatar > copie = v;
	assert(copie.size() == 3);
	Locatar rez = v.at(0);
	assert(rez == locatar1);
	assert(rez.get_nume_pr() == "Mihai");

	assert(v.size() == 3);
	rez = v.at(2);
	assert(rez == locatar3);

	v.erase(v.begin() + 1);
	assert(v.size() == 2);
	rez = v.at(0);
	assert(rez == locatar1);
	rez = v.at(1);
	assert(rez == locatar3);
	v.erase(v.begin());
	assert(v.size() == 1);

}

void Test::test_get_all_myvector()
{
	Myvector< Locatar > v ;
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	v.push_back(locatar1);
	v.push_back(locatar2);
	int pret = 0;
	for (const Locatar& x : v)
		pret += x.get_spr();
	assert(pret == 1489 + 342);
}

void Test::test_add_myvector()
{
	Myvector< Locatar > v;
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	v.push_back(locatar1);
	assert(v.size() == 1);
	v.push_back(locatar2);
	assert(v.size() == 2);
	Myvector < int > a, b;
	a.push_back(1);
	a.push_back(2);
	b = a;
	a = a;
}

void Test::test_set_locatar()
{
	Locatar locatar = Locatar(30, 2000, "Andrei", "gara");
	locatar.set_nume_pr("Cosmin");
	locatar.set_tip("pent");
	locatar.set_spr(3000);
	assert(30 == locatar.get_apart());
	assert(3000 == locatar.get_spr());
	assert("Cosmin" == locatar.get_nume_pr());
	assert("pent" == locatar.get_tip());
}

void Test::test_locatar()
{
	Locatar locatar{12,1200,"Mihai","penthouse"};
	assert(12 == locatar.get_apart());
	assert(1200 == locatar.get_spr());
	assert("Mihai" == locatar.get_nume_pr());
	assert("penthouse" == locatar.get_tip()); 
	Locatar loc = Locatar(12,2000,"Andrei","gara");
	assert(locatar == loc);
	std::stringstream sout;
	sout << loc;
	string mesaj = sout.str();
	assert(mesaj.compare("/Apartament: 12/Suprafata: 2000/Nume proprietar: Andrei/Tip: gara") == 0);
}

void Test::test_validare_locatar()
{
	Locatar locatar{12,1200,"Mihai","penthouse" };
	Validator vd;
	try {
		vd.valideaza(locatar);
		assert(true);
	}
	catch (const LocatarError& e)
	{
		assert(e.get_msg().compare("") == 0);
		assert(false);
	}
	Locatar loc{-12, -13, "", "" }; 
	try{
		vd.valideaza(loc);
		assert(false);
	}
	catch (const LocatarError& e)
	{
		assert(0==e.get_msg().compare("Suprafata trebe sa fie pozitiva!\nApartament invalid!\nNume proprietar invalid!\nTip apartamnet invalid!\n"));
	}

}

void Test::test_add_repo()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Locatar locatar1{12,1489,"Mihai","penthouse"}; 
	Locatar locatar2{126,342,"Cosmin","garsoniera" }; 
	Repo_locatari_file repo("apar_test.txt");
	assert(repo.size() == 0);
	repo.add_locatar(locatar1);
	repo.add_locatar(locatar2); 
	assert(repo.size() == 2);
	try {
		repo.add_locatar(locatar1);
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul exista deja in lista!\n"));
		assert(true);
	}
}

void Test::test_delete_repo()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" }; 
	Repo_locatari_file repo{ "apar_test.txt" };
	assert(0 == repo.size());
	repo.add_locatar(locatar1);
	repo.add_locatar(locatar2);
	assert(2 == repo.size());
	repo.delete_locatar(12); 
	try {
		repo.delete_locatar(12);
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}
	Repo_locatari_file repo1{ "apar_test.txt" }; //Doar ca sa acopere
}

void Test::test_update_repo()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	Repo_locatari_file repo{ "apar_test.txt" };
	repo.add_locatar(locatar1);
	repo.add_locatar(locatar2); 
 
	repo.update_locatar(Locatar{ 12,20,"Radu","bucatarie" });
	const Myvector< Locatar >& v = repo.get_all();
	const Locatar& rez = v.at(0);

	assert(v.size() == 2);
	assert(0 == rez.get_tip().compare("bucatarie"));
	assert(rez.get_spr() == 20);
	assert(rez.get_apart() == 12);

	try {
		repo.update_locatar(Locatar{ 20,20,"Radu","bucatarie" });
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}
}

void Test::test_add_service()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Repo_locatari_file repo{ "apar_test.txt" };
	Validator vd; 
	Controller_Locatari srv{ repo,vd };
	assert(0 == repo.size());
	srv.add_locatari(31, 1200, "Cosmin", "penthouse");
	srv.add_locatari(45, 2302, "Mihai","Garsoniera");
	assert(2 == repo.size());
	try {
		srv.add_locatari(-23, -23, "", "");
		assert(false);
	}
	catch (const LocatarError& e)
	{
		assert(0 == e.get_msg().compare("Suprafata trebe sa fie pozitiva!\nApartament invalid!\nNume proprietar invalid!\nTip apartamnet invalid!\n"));
	}

	try {
		srv.add_locatari(45, 3453, "Tata", "fsf");
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul exista deja in lista!\n"));
	}
}

void Test::test_delete_service()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{ repo,vd }; 
	assert(0 == repo.size());
	srv.add_locatari(31, 1200, "Cosmin", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	assert(2 == repo.size()); 

	srv.delete_locatari(31);
	assert(1 == repo.size());

	try {
		srv.delete_locatari(31);
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}
}

void Test::test_update_service()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd; 
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{ repo,vd };

	srv.add_locatari(31, 1200, "Cosmin", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");

	srv.update_locatari(31, 61, "Gaga", "mama");
	const Myvector< Locatar >& v = srv.get_all();
	const Locatar& rez = v.at(0);

	assert(2 == v.size());
	assert(0 == rez.get_tip().compare("mama"));
	assert(rez.get_spr() == 61);
	assert(rez.get_apart() == 31); 

	try {
		srv.update_locatari(49, 2302, "Mihai", "Garsoniera");
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}
	
}

void Test::test_search_service()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{repo,vd};

	srv.add_locatari(31, 1200, "Cosmin", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera"); 

	const Locatar& rez = srv.search(31);
	assert(0 == rez.get_tip().compare("penthouse"));
	assert(rez.get_spr() == 1200);
	assert(rez.get_apart() == 31);

	try {
		srv.search(49);
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}
}

void Test::test_search_repo()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	Repo_locatari_file repo{ "apar_test.txt" };
	repo.add_locatar(locatar1);
	repo.add_locatar(locatar2);

	const Locatar& rez = repo.search(12);
	assert(0 == rez.get_tip().compare("penthouse"));
	assert(rez.get_spr() == 1489);
	assert(rez.get_apart() == 12);

	try {
		repo.search(49);
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}

	try {
		throw ValueError("andrei");
	}
	catch (const ValueError e)
	{
		assert(0 == e.get_msg().compare("andrei"));
	}
}

void Test::test_filtrebyspr()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo_locatari{ "apar_test.txt" };
	Controller_Locatari srv{ repo_locatari,vd };

	srv.add_locatari(31, 1200, "Cosmin", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 5000, "Radu", "Bucatarie");

	Myvector <Locatar> rez = srv.filtrebyspr(6000);
	assert(rez.at(0).get_apart() == 31);
	assert(rez.at(1).get_apart() == 45);
	assert(rez.at(2).get_apart() == 50);
	Locatar& rezq = rez.at(0);
	rezq.set_nume_pr("AAAAAAAAAAA");
	rez = srv.filtrebyspr(1300);
	assert(rez.at(0).get_apart() == 31);

}

void Test::test_filtrebytype()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv(repo, vd);
	srv.add_locatari(31, 1200, "Cosmin", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 5000, "Radu", "penthouse");

	Myvector < Locatar > rez = srv.filtrebytype("penthouse");
	assert(rez.size() == 2);
	assert(rez.at(0).get_apart() == 31);
	assert(rez.at(1).get_apart() == 50);

	rez = srv.filtrebytype("gg");
	assert(rez.size() == 0);
}

void Test::test_sortbyname()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv(repo, vd);
	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 5000, "Cosmin", "penthouse");

	Myvector < Locatar > rez = srv.sortbyname();
	assert(rez.size() == 3);
	assert(rez[0].get_nume_pr().compare("Cosmin") == 0);
	assert(rez[1].get_nume_pr().compare("Mihai") == 0);
	assert(rez[2].get_nume_pr().compare("Radu") == 0);
}

void Test::test_sortbyspr()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv(repo, vd);
	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse"); 

	Myvector < Locatar > rez = srv.sortbyspr();
	assert(rez[0].get_apart() == 50);
	assert(rez[1].get_apart() == 31);
	assert(rez[2].get_apart() == 45);
}

void Test::test_sortmp()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv(repo, vd);
	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse");

	Myvector < Locatar > rez = srv.sortbytypespr();
	assert(rez[0].get_apart() == 45);
	assert(rez[1].get_apart() == 50);
	assert(rez[2].get_apart() == 31);
}

void Test::test_add_list()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{ repo,vd };

	try {
		srv.get_coscurent().random_list(4);
		assert(false);
	}
	catch (const ListError& e)
	{
		assert(e.get_msg() == "Nu exista elemente de adaugat!\n");
	}

	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse");

	srv.get_coscurent().add_list(31);
	srv.get_coscurent().add_list(45);
	srv.get_coscurent().add_list(31);
	srv.get_coscurent().add_list(45);

	assert(4 == srv.get_coscurent().size_list());
	const	Myvector < Locatar >& rez = srv.get_coscurent().get_all_list();
	assert(rez.at(0).get_apart() == 31);
	assert(rez.at(1).get_apart() == 45);
	assert(rez.at(2).get_apart() == 31);
	assert(rez.at(3).get_apart() == 45);
	//for (const Locatar& x : rez) std::cout << x << '\n';
	try {
		srv.get_coscurent().add_list(657);
		assert(false);
	}
	catch(const RepoError & e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}

	srv.get_coscurent().goleste();
	assert(srv.get_coscurent().size_list() == 0);

	srv.get_coscurent().add_list(45);
	assert(srv.get_coscurent().size_list() == 1);

	srv.get_coscurent().random_list(2);
	//assert(srv.get_coscurent().size_list() == 3);

	srv.get_coscurent().export_list_file("test-file.csv");

}

void Test::test_raport_type()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{ repo,vd };

	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse");

	Myvector <DTO_tip_locatar> rez = srv.raport_type();

	assert(rez.size() == 2);
	assert(rez.at(0).get_type() == "Garsoniera");
	assert(rez.at(1).get_cnt() == 2);
	assert(rez.at(1).get_type() == "penthouse");
}

void Test::test_undo_add() {
	std::ofstream out("apar_test.txt", std::ios::trunc);
	out.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{ repo,vd };

	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse");

	assert(repo.size() == 3);
	srv.undo();
	assert(repo.size() == 2);
	try {
		srv.search(50);
		assert(false);
	}
	catch (const RepoError& e)
	{
		e.get_msg();
		assert(true);
	}
	srv.undo();
	srv.undo();
	try {
		srv.undo();
		assert(false);
	}
	catch (const UndoError& e)
	{
		assert(e.get_msg() == "Nu se mai pot executa operatii undo!\n");
	}
}

void Test::test_undo_delete() {
	std::ofstream out("apar_test.txt", std::ios::trunc);
	out.close();
	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv(repo, vd); 

	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse");

	srv.delete_locatari(45);
	srv.delete_locatari(31);
	assert(repo.size() == 1);
	srv.undo();
	srv.undo();
	assert(repo.size() == 3);
	srv.undo();
	assert(repo.size() == 2);
}

void Test::test_undo_update() {
	std::ofstream out("apar_test.txt", std::ios::trunc);
	out.close();

	Validator vd;
	Repo_locatari_file repo{ "apar_test.txt" };
	Controller_Locatari srv{ repo,vd }; 

	srv.add_locatari(31, 1200, "Radu", "penthouse");
	srv.add_locatari(45, 2302, "Mihai", "Garsoniera");
	srv.add_locatari(50, 1000, "Cosmin", "penthouse");

	srv.update_locatari(45, 3000, "gheorghe", "loc");
	const Locatar& locatar = srv.search(45);
	assert(locatar.get_nume_pr() == "gheorghe");

	srv.undo();
	const Locatar& locatar1 = srv.search(45);
	assert(locatar1.get_nume_pr() == "Mihai");

}