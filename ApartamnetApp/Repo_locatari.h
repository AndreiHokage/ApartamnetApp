#pragma once
#define _CRTDBG_MAP_ALLOC
#include <vector> 
#include <crtdbg.h>
#include "Locatar.h"
#include "Myvector.h"
using std::vector; 


class Repo
{
public:


	/*
	* Functia adauga un locatar
	* Date de intrare:locatar-o referinta constanta la un locatar ce se va adauga
	* Date de iesire:lista cu locatarul adaugat
	* Functia ridica exceptii de tip RepoError daca locatarul exista deja
	*/
	virtual void add_locatar(const Locatar& locatar) = 0;

	/*
	* Functia returneaza nr de locatari
	* Date de intrare:-
	* Date de iesire:nr de locatari din lista
	*/
	virtual int size() const noexcept = 0;

	/*
	* Functia sterge un locatar
	* Date de intrare:id-un int ce reprezinta nr de apartamnet al lcatarului
	* Date de iesire:lista din care se elimina locatarul
	* Functia ridica exceptii de tip RepoError daca locatarul nu esste gasit
	*/
	virtual Locatar delete_locatar(int id) = 0;

	/*
	* Functia updateaza un locatar
	* Date de intrare:locatar-o referinta constanta la un locatar pe baza carei se va face update ul
	* Date de iesire:Functia updateaza locatarul daca il gaseste
	* Functia ridica exceptii de tip RepoError daca locatarul nu esste gasit
	*/
	virtual Locatar update_locatar(const Locatar& locatar) = 0;

	/*
	* Functia cauta un locatar dupa apartamnet
	* Date de intrare:id-un int
	* Date de iesire:o referinta la un obiect de tip locatar
	* Functia arunca exceptii de tip RepoError daca elemntul nu este gasit
	*/
	virtual const Locatar& search(int id) = 0;

	virtual const Myvector< Locatar >& get_all() noexcept = 0;

	virtual ~Repo() = default;
};

class Repo_locatari :public Repo
{
private:
	Myvector< Locatar > repo_locatari; 

public:

	Repo_locatari() = default;

	Repo_locatari(const Repo_locatari&) = delete;

	/*
	* Functia adauga un locatar
	* Date de intrare:locatar-o referinta constanta la un locatar ce se va adauga
	* Date de iesire:lista cu locatarul adaugat
	* Functia ridica exceptii de tip RepoError daca locatarul exista deja
	*/
	virtual void add_locatar(const Locatar& locatar) override; 

	/*
	* Functia returneaza nr de locatari 
	* Date de intrare:- 
	* Date de iesire:nr de locatari din lista
	*/
	virtual int size() const noexcept override;

	/*
	* Functia sterge un locatar
	* Date de intrare:id-un int ce reprezinta nr de apartamnet al lcatarului
	* Date de iesire:lista din care se elimina locatarul
	* Functia ridica exceptii de tip RepoError daca locatarul nu esste gasit
	*/
	virtual Locatar delete_locatar(int id) override; 

	/*
	* Functia updateaza un locatar
	* Date de intrare:locatar-o referinta constanta la un locatar pe baza carei se va face update ul
	* Date de iesire:Functia updateaza locatarul daca il gaseste 
	* Functia ridica exceptii de tip RepoError daca locatarul nu esste gasit
	*/
	virtual Locatar update_locatar(const Locatar& locatar) override; 

	/*
	* Functia cauta un locatar dupa apartamnet 
	* Date de intrare:id-un int  
	* Date de iesire:o referinta la un obiect de tip locatar 
	* Functia arunca exceptii de tip RepoError daca elemntul nu este gasit
	*/
	virtual const Locatar& search(int id) override;

	virtual const Myvector< Locatar >& get_all() noexcept override;


};
