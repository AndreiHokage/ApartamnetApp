#pragma once
#include "Locatar.h"
#include "Myvector.h"
#include "Iterator_myvector.h"
#include "Repo_locatari.h"
#include "Error.h"
#include "Observer.h"

class Cos:public Observable
{
private:
	Myvector <Locatar> list;
	Repo& repo;
public:
	
	Cos(Repo& repo) noexcept:repo{ repo } {

	}

	Cos(const Cos& cos) = delete;

	/*
	* Functia adauga un apartament in cos dupa id 
	* Date de intrare:id-id ul apartamentului
	* Date de iesire:cosul contine apartamentul identificat cu id
	* Functia ridica exceptii de tip RepoError daca id ul este invalid
	*/
	void add_list(int id);

	/*
	* Functia retuneaza r de elemente din cos
	*/
	int size_list() noexcept;

	/*
	* Functia returneaza toate elementele din cos
	* Date de intrare:
	* Date de iesire:o referinta constanta la vectorul de lemente
	*/
	const Myvector < Locatar >& get_all_list() const noexcept;

	/*
	* Functia goleste elementele din cos
	* Date de intrare: 
	* Date de iesire:cosul devine gol
	*/
	void goleste();

	/*
	* Functia adauga random  elemente din repo in cos
	* Date de intrare:numar-nr de elemente de adaugat 
	* Date de iesire:lista contine un numar de 'numar' de apartamente random 
	* Ridica exceptii de tip ListError daca nu exista elemente de adaugat
	*/
	void random_list(int numar);

	/*
	* Functia exporta elementele din cos in fisier 
	* Date de intrare: name_file-un string ce reprezinta numele fiserului csv 
	* Date de iesire:se creeaza fisierul specificat cu elmentele din cos
	* Functia arunca exeptii de tip ListError daca fiserul dat nu este csv
	*/
	void export_list_file(const string& name_file) const;
};

