#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Repo_locatari.h"
#include "Error.h"
#include "Myvector.h"
#include "Iterator_myvector.h"
#include "Locatar.h"
using std::unordered_map;
using std::vector;

class RepoLab:public Repo
{

private:
	double prob;
	unordered_map<int, Locatar> repo;
	Myvector < Locatar > vec;

	void exceptie();

public:

	RepoLab() = default;

	RepoLab(double prob):Repo(),prob{prob}{}

	RepoLab(const RepoLab&) = delete;

	virtual void add_locatar(const Locatar& locatar) override;

	virtual int size() const noexcept override;

	virtual Locatar delete_locatar(int id) override;

	virtual Locatar update_locatar(const Locatar& locatar) override;

	virtual const Locatar& search(int id) override;

	virtual const Myvector< Locatar >& get_all() noexcept override;
};

