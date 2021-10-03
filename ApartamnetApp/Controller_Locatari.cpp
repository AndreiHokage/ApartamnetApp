#include "Controller_Locatari.h"
#include "Locatar.h"
#include "Error.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <chrono>
#include <random>
#include "DTO_tip_locatar.h"
using std::function;
using std::unordered_map;

/*
* Myvector < Locatar > Controller_Locatari::filtregeneral(function<bool(const Locatar&)> fct) const{
	Myvector < Locatar > rez;
	const Myvector< Locatar >& v = repo.get_all();
	for (const Locatar& locatar : v)
		if (fct(locatar))
			rez.push_back(locatar); //Se face o cipe mienuz
	return rez; ///Atentie ca retunezi o copie!Nu conteaza ca rez contine locatarii originali din lista de repo
	            ///Prin returul de copie lista se copieaza si odata cu aceasta si elementele ei
				///Cum am respectat rules of three o sa avem locatari diferiti!Daca ii modific
				/// nu se reflecta si in lista din repo
}

Myvector < Locatar > Controller_Locatari::sortgeneral(function<bool(const Locatar& x, const Locatar& y)> fct) const {
	Myvector < Locatar > rez = repo.get_all();
	const int n = rez.size();
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if (fct(rez[j], rez[i]))
			{
				const Locatar aux = rez[i];
				rez[i] = rez[j]; //assigmnet operator petru elementle ElmenentT(Locatari in cazul nostru)
				rez[j] = aux;
			}
	return rez;
}
*/


void Controller_Locatari::undo() {

	if (!UndoList.size())
		throw UndoError("Nu se mai pot executa operatii undo!\n");

	UndoList.back()->doUndo();
	UndoList.pop_back();
}

void Controller_Locatari::add_locatari(int apart, int spr, string nume_pr, string tip){
	Locatar locatar{apart,spr,nume_pr,tip };
	vd.valideaza(locatar);
	repo.add_locatar(locatar);
	UndoList.push_back(make_unique<UndoAdauga>(repo, locatar)); //nu pot trimite copie pentru ca locatar se distruge dupa 
													//ce iese din functia add_locatri din service!
}

void Controller_Locatari::delete_locatari(int id) {
	Locatar locatar=repo.delete_locatar(id);
	UndoList.push_back(make_unique<UndoSterge>(repo, locatar));
}

void Controller_Locatari::update_locatari( int apart, int spr, string nume_pr, string tip) {
	Locatar locatar{apart,spr,nume_pr,tip };
	vd.valideaza(locatar);
	Locatar x=repo.update_locatar(locatar);
	UndoList.push_back(make_unique<UndoModifica>(repo,x));
}

const Myvector< Locatar >& Controller_Locatari:: get_all() const noexcept{
	return repo.get_all();
}

const Locatar& Controller_Locatari::search(int id){
	return repo.search(id);
}


Myvector < Locatar > Controller_Locatari::filtrebyspr(int spr) const{


	const Myvector < Locatar >& arr = repo.get_all();
	vector < Locatar > v, dest;
	for (const Locatar& x : arr)
		v.push_back(x);

	copy_if(v.begin(), v.end(), std::back_inserter(dest), [spr](const Locatar& locatar) noexcept {
		return locatar.get_spr() < spr;
		});

	Myvector < Locatar > rez;
	for (const Locatar& x : dest)
		rez.push_back(x);

	return rez;
}

Myvector < Locatar > Controller_Locatari::filtrebytype(string type) const {

	const Myvector < Locatar >& arr = repo.get_all();
	vector < Locatar > v,dest;
	for (const Locatar& x : arr)
		v.push_back(x);

	copy_if(v.begin(),v.end(),std::back_inserter(dest), [&type](const Locatar& locatar)  {
		return locatar.get_tip() == type;
		});

	Myvector < Locatar >rez;
	for (const Locatar& x : dest)
		rez.push_back(x);

	return rez;
}

Myvector < Locatar > Controller_Locatari::sortbyname() const {

	const Myvector < Locatar >& arr = repo.get_all();

	vector < Locatar > v;

	for (const Locatar& x : arr)
		v.push_back(x);

	sort(v.begin(),v.end(), [](const Locatar& x, const  Locatar& y) {
		return x.get_nume_pr() < y.get_nume_pr();
		});

	Myvector < Locatar > rez;

	for (const Locatar& x : v)
		rez.push_back(x);

	return rez;
}

Myvector < Locatar > Controller_Locatari::sortbyspr() const{
	
	const Myvector < Locatar >& arr = repo.get_all();
	vector < Locatar > v;

	for (const Locatar& x : arr)
		v.push_back(x);

	sort(v.begin(),v.end(), [](const Locatar& x, const Locatar& y) noexcept {
		return x.get_spr() < y.get_spr();
		});

	Myvector < Locatar > rez;
	for (const Locatar& x : v)
		rez.push_back(x);
	return rez;
}

Myvector < Locatar > Controller_Locatari::sortbytypespr() const {
	
	const Myvector < Locatar >& arr = repo.get_all();

	vector < Locatar > v;
	for (const Locatar& x : arr)
		v.push_back(x);
	
	sort(v.begin(), v.end(), [](const Locatar& x, const Locatar& y) {
		if (x.get_tip() == y.get_tip())
			return x.get_spr() < y.get_spr();

		return x.get_tip() < y.get_tip();
		});

	Myvector < Locatar > rez;
	for (const Locatar& x : v)
		rez.push_back(x);
	return rez;

}

Myvector < DTO_tip_locatar > Controller_Locatari::raport_type()  {
	unordered_map < string, DTO_tip_locatar > dict;
	unordered_map < string, DTO_tip_locatar > ::iterator it;
	Myvector < DTO_tip_locatar > ans;
	const Myvector < Locatar >& lista = repo.get_all();
	for (const Locatar& locatar : lista)
	{
		it = dict.find(locatar.get_tip());
		if (it == dict.end())
			dict.insert(std::make_pair < string, DTO_tip_locatar >(locatar.get_tip(), DTO_tip_locatar(locatar.get_tip())));
		else
			dict[locatar.get_tip()].increase_cnt();
	}
	for (it = dict.begin(); it != dict.end(); it++)
	{
		ans.push_back(it->second);
	}
	return ans;
}

