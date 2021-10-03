#pragma once
#include "Repo_locatari.h" 
#include "Validator.h"
#include "Locatar.h"
#include "Myvector.h"
#include <string>
#include <functional>
#include <vector>
#include "Cos.h"
#include "DTO_tip_locatar.h"
#include "UndoAction.h"
using std::function;
using std::string;

class Controller_Locatari
{

private:
	Repo& repo;
	Validator& vd;
	Cos coscurent; //MOSTENIRE VS AGREGARE

	vector < unique_ptr<UndoAction> > UndoList;

	//Myvector < Locatar > filtregeneral(function<bool(const Locatar&)> fct) const;

	//Myvector < Locatar > sortgeneral(function<bool(const Locatar& x, const Locatar& y)> fct) const;

public:

	Controller_Locatari(Repo& repo, Validator& vd) noexcept :repo{ repo }, vd{ vd }, coscurent{ repo } {

	}

	Controller_Locatari(const Controller_Locatari& ot) = delete;

	void undo();

	/*
	* Functia adauga un locatar
	* Date de intrare:apart-int:nr de apartament
	*				  spr-int:suprafata apartamentului
	*				  nume_pr-string:numele proprietarului
	*				  tip-string:tipul apartamentului
	* Date de iesire:Functia adauga locatarul 
	* Functia ridica exceptii de tip RepoError daca locatarul exitsa deja
	* Functia ridica exceptii de tip LocatarError daca locatarul este invalid
	*/
	void add_locatari(int apart, int spr, string nume_pr, string tip);

	/*
	* Functia sterge un locatar
	* Date de intrare:id-un int ce reprezinta nr de apartamnet al lcatarului
	* Date de iesire:lista din care se elimina locatarul
	* Functia ridica exceptii de tip RepoError daca locatarul nu esste gasit
	*/
	void delete_locatari(int id); 


	/*
	* Functia updateaza un locatar
	* Date de intrare:apart-int:nr de apartament 
	*				  spr-int:suprafata apartamentului
	*				  nume_pr-string:numele proprietarului
	*				  tip-string:tipul apartamentului
	* Date de iesire:Functia updateaza locatarul daca il gaseste
	* Functia ridica exceptii de tip RepoError daca locatarul nu esste gasit
	* Functia ridica exceptii de tip LocatarError daca locatarul este invalid
	*/
	void update_locatari(int apart, int spr, string nume_pr, string tip);

	/*
	* Functia cauta un locatar dupa apartamnet
	* Date de intrare:id-un int
	* Date de iesire:un obiect de tip locatar
	* Functia arunca exceptii de tip RepoError daca elemntul nu este gasit
	*/
	const Locatar& search(int id) ;

	/*
	* Functia intoarce o referinta constanta spre lista locatarilor 
	* Date de intrare:- 
	* Date de iesire:0 referinta constanta la lista de locatari
	*/
	const Myvector< Locatar >& get_all() const noexcept;

	Myvector <Locatar> filtrebyspr(int spr) const;

	Myvector < Locatar > filtrebytype(string type) const;

	/*
	* Functia sorteza dupa nume
	*/
	Myvector < Locatar > sortbyname() const; 

	/*
	* Functia sorteza dupa suprafata
	*/
	Myvector < Locatar > sortbyspr() const; 

	Myvector < Locatar > sortbytypespr() const;

	Myvector < DTO_tip_locatar > raport_type();

	Cos& get_coscurent() noexcept{
		return coscurent;
	}

};

