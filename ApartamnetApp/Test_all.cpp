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
#include "RepoLab.h"

void Test_all :: run_all() {
	run_all_tests();
	test_repolab_add();
	test_repolab_update();
	test_repolab_delete();
	test_repolab_search();
}

void Test_all::test_repolab_add()
{
	std::ofstream ofs("apar_test.txt", std::ios::trunc);
	ofs.close();
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	RepoLab repo(2);
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

void Test_all:: test_repolab_delete()
{
	
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	RepoLab repo(2);
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

void Test_all::test_repolab_search()
{
	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	RepoLab repo(2);
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

void Test_all::test_repolab_update()
{

	Locatar locatar1{ 12,1489,"Mihai","penthouse" };
	Locatar locatar2{ 126,342,"Cosmin","garsoniera" };
	RepoLab repo(2);
	repo.add_locatar(locatar1);
	repo.add_locatar(locatar2);
	repo.get_all();
	repo.update_locatar(Locatar{ 12,20,"Radu","bucatarie" });

	const Myvector < Locatar >& v = repo.get_all();
	const Locatar& rez = v.at(0);
	assert(0 == rez.get_tip().compare("bucatarie"));
	assert(rez.get_spr() == 20);
	assert(rez.get_apart() == 12);

	assert(v.size() == 2);
	const Myvector < Locatar >& v2 = repo.get_all();
	assert(v2.size() == 2);

	try {
		repo.update_locatar(Locatar{ 20,20,"Radu","bucatarie" });
		assert(false);
	}
	catch (const RepoError& e)
	{
		assert(0 == e.get_msg().compare("Locatarul nu exista in lista!\n"));
	}

	RepoLab repo2(0);
	try {
		repo2.add_locatar(locatar1);
		assert(false);
	}
	catch (const CevaEroare& e)
	{
		assert(e.get_msg() == "some error!\n");
	}
}
