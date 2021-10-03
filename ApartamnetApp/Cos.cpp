#include "Cos.h"
#include "Myvector.h"
#include <unordered_map> 
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
using std::unordered_map;


void Cos::add_list(int id) {

	const Locatar& locatar = repo.search(id);
	list.push_back(locatar);
	notify();
}

int Cos::size_list() noexcept {
	return list.size();
}

const Myvector < Locatar >& Cos::get_all_list() const noexcept
{
	return list;
}

void Cos::goleste() {
	Myvector < Locatar > nou_list;
	list = nou_list;
	notify();
}

void Cos::random_list(int numar) {
	const Myvector < Locatar >& v = repo.get_all();

	if (!v.size())
		throw ListError("Nu exista elemente de adaugat!\n");
	std::mt19937 generator{ std::random_device{}() };

	const std::uniform_int_distribution<> dist(0, v.size() - 1);
	while (numar)
	{
		const int id = dist(generator);
		list.push_back(v.at(id));
		numar--;
	}

	notify();
}

void Cos::export_list_file(const string& name_file) const {
	size_t found = name_file.find(".csv"); 
	if (found == string::npos)
		throw ListError("Fisierul nu este de tip 'csv' !\n");
	std::ofstream fout(name_file, std::ios::trunc);
	for (const Locatar& x : list)
		fout << x.get_apart() << ',' << x.get_spr() << ',' << x.get_nume_pr() << ',' << x.get_tip() << '\n';
	fout.close();
}