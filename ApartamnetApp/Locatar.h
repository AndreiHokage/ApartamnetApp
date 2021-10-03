#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string> 
#include <iostream>
using std::string;
using std::ostream;

class Locatar
{
private:
	int apart;
	int spr; 
	string nume_pr;
	string tip; 

public: 
	
	Locatar() noexcept{
		apart = 0;
		spr = 0;
	}

	Locatar(int apart, int spr, const string& nume_pr,const string& tip) : apart{ apart }, spr{ spr }, nume_pr{ nume_pr }, tip{ tip }{

	}

	Locatar(const Locatar& locatar) : apart{ locatar.apart }, spr{ locatar.spr }, nume_pr{ locatar.nume_pr }, tip{ locatar.tip }{
		//std::cout << "S a copiat" << '\n';
	}

	/*
	* Getter method
	* returneaza tipul proprietarului
	*/
	string get_tip() const {
		return tip;
	}

	/*
	* Getter method
	* returneaza numele propritarului
	*/
	string get_nume_pr() const {
		return nume_pr;
	}

	/*
	* Getter method
	* returneaza nr apartamentului
	*/
	int get_apart() const noexcept {
		return apart;
	} 

	/*
	* Getter method 
	* returneaza suprafata
	*/
	int get_spr() const noexcept {
		return spr; 
	}

	/*
	* Setter method
	* seteaza suprafata 
	*/
	void set_spr(int spr) noexcept; 

	/*
	* Setter method
	* seteaza tipul
	*/
	void set_tip(string tip); 

	/*
	* Setter method
	* seteaza numele propritarului
	*/
	void set_nume_pr(string nume_pr);

	bool operator ==(const Locatar& locatar) const noexcept;

	friend ostream& operator<<(ostream& os, const Locatar& ob);


	Locatar& operator=(const Locatar& ot) = default;
	~Locatar() = default;

	Locatar (Locatar&& ot) = default;
	Locatar& operator=(Locatar && ot) = default;

};

