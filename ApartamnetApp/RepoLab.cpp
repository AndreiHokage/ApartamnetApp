#include "RepoLab.h"
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
using std::vector;

void RepoLab::exceptie()
{
	const double op = ((double)rand() / RAND_MAX);
	if ( op > ((double)prob ))
		throw CevaEroare("some error!\n");
}

void RepoLab::add_locatar(const Locatar& locatar) {
	exceptie();
	if(repo.find(locatar.get_apart())!=repo.end())
		throw RepoError{ "Locatarul exista deja in lista!\n" };
	repo.insert({ locatar.get_apart(), locatar });
}

int RepoLab::size()const noexcept {
	return repo.size();
}

Locatar RepoLab::delete_locatar(int id) {
	exceptie();
	if (repo.find(id) == repo.end())
		throw RepoError{ "Locatarul nu exista in lista!\n" };
	Locatar locatar = repo[id];
	repo.erase(id);
	return locatar;
}

Locatar RepoLab::update_locatar(const Locatar& locatar) {
	exceptie();
	int id = locatar.get_apart();

	if (repo.find(id) == repo.end())
		throw RepoError{ "Locatarul nu exista in lista!\n" };

	Locatar x = repo[id]; 
	repo[id].set_nume_pr(locatar.get_nume_pr());
	repo[id].set_tip(locatar.get_tip());
	repo[id].set_spr(locatar.get_spr());
	return x;
}

const Locatar& RepoLab::search(int id)
{
	exceptie();
	if(repo.find(id)==repo.end())
		throw RepoError{ "Locatarul nu exista in lista!\n" };

	return repo[id];
}

const Myvector< Locatar >& RepoLab::get_all() noexcept
{

	Myvector < Locatar > aux;
	vec = aux;
	for (auto x : repo)
		vec.push_back(x.second);
	
	return vec;
}