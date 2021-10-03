#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <vector>
#include <algorithm>
#include "Repo_locatari.h"
#include "Error.h"
using std::vector;

void Repo_locatari::add_locatar(const Locatar& locatar)
{
	for (const Locatar& x : repo_locatari)
		if (locatar == x)
			throw RepoError{ "Locatarul exista deja in lista!\n" };

	repo_locatari.push_back(locatar);
}

int Repo_locatari::size() const noexcept{
	return repo_locatari.size();
}

Locatar Repo_locatari::delete_locatar(int id)
{
	int n = 0;
	for (const Locatar& x : repo_locatari)
	{
		if (x.get_apart() == id)
		{
			Locatar loc_del = x;
			repo_locatari.erase(repo_locatari.begin() + n);
			return loc_del;
		}
		n++;
	}
	throw RepoError{ "Locatarul nu exista in lista!\n" };
}

Locatar Repo_locatari::update_locatar(const Locatar& locatar)
{
	
	for(Locatar& x:repo_locatari)
		if (locatar == x)
		{
			Locatar locatar_old = x;
			x.set_nume_pr(locatar.get_nume_pr());
			x.set_spr(locatar.get_spr());
			x.set_tip(locatar.get_tip());
			return locatar_old;
		}
	throw RepoError("Locatarul nu exista in lista!\n");
}

const Myvector< Locatar >& Repo_locatari::get_all()  noexcept {
	return repo_locatari;
}

const Locatar& Repo_locatari::search(int id) {
	for(const Locatar& locatar: repo_locatari)
		if (locatar.get_apart() == id)
		{
			return locatar;
		}
	throw RepoError{ "Locatarul nu exista in lista!\n" };

}