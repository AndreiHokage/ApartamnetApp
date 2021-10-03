#include "Repo_locatari_file.h"
#include <fstream> 
#include <string> 
#include "Locatar.h"
#include "Iterator_myvector.h"
#include "Error.h"
using std::string;

Myvector < string > Repo_locatari_file :: split_string(string S) {
	Myvector < string > v;
	int start = 0;
	int end = S.find(';');
	while (end != -1)
	{
		string aux = S.substr(start, end - start);
		v.push_back(aux);
		start = end + 1;
		end = S.find(';', start);
	}
	v.push_back(S.substr(start, end - start));
	return v;
}

void Repo_locatari_file::loadfromfile()
{
	std::ifstream in(file_name);
	if (!in.is_open())
	{
		throw FileError("Error file: " + file_name);
	}
	while (!in.eof())
	{
		string S;
		getline(in, S);
		if (S == "")
			continue;
		Myvector < string > v=split_string(S);
		const int apart = stoi(v[0]);
		const int spr = stoi(v[1]); 
		string nume_pr = v[2];
		string tip = v[3];
		Locatar locatar{ apart,spr,nume_pr,tip };
		Repo_locatari::add_locatar(locatar);
	}
	in.close();
}

void Repo_locatari_file::storetofile() {
	std::ofstream out(file_name,std::ios::trunc); 
	if (!out.is_open())
	{
		throw FileError("Error file: " + file_name);
	}
	const Myvector < Locatar >& v = Repo_locatari::get_all();
	for (const Locatar& x : v)
	{
		const int apart = x.get_apart();
		const int spr = x.get_spr();
		string nume_pr = x.get_nume_pr();
		string tipe = x.get_tip();
		out << apart << ";" << spr << ";" << nume_pr << ";" << tipe << ";" << '\n';
	}
	out.close();
}

void Repo_locatari_file::add_locatar(const Locatar& locatar) {
	Repo_locatari::add_locatar(locatar);
	storetofile();
}

Locatar Repo_locatari_file::delete_locatar(int id) {
	Locatar locatar=Repo_locatari::delete_locatar(id);
	storetofile();
	return locatar;
}

Locatar Repo_locatari_file::update_locatar(const Locatar& locatar) {
	Locatar locatar_old=Repo_locatari::update_locatar(locatar);
	storetofile();
	return locatar_old;
}