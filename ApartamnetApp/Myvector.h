#pragma once
#include "Locatar.h"
#include "Iterator_myvector.h"
#include <memory>
#define INITIAL_CAPACITY 1
using std::unique_ptr;
using std::make_unique;


template < typename ElementT >
class Iterator_myvector;

template < typename ElementT >
class Myvector
{

private:
	
	int cp;

	int n;

	unique_ptr <ElementT[]> elem;

	void redim();

public:

	friend class Iterator_myvector< ElementT >;

	Myvector() :cp{ INITIAL_CAPACITY }, n{ 0 }, elem{ make_unique<ElementT[]>(INITIAL_CAPACITY) } {
	}

	Myvector(int cp) :cp{ cp }, n{ 0 }, elem{ make_unique<ElementT[]>(cp) } {
	}


	Myvector(const Myvector& ot);

	Myvector& operator=(const Myvector& ot);

	ElementT& operator[](int poz);

	void push_back(const ElementT& elem);

	int size() const noexcept ;

	ElementT& at(int poz) const noexcept;

	void erase(const Iterator_myvector< ElementT >& it);

	Iterator_myvector< ElementT > iterator() const noexcept;

	Iterator_myvector< ElementT > begin() const noexcept; 

	Iterator_myvector< ElementT > end() const noexcept;

	~Myvector();

	Myvector& operator=(Myvector&& ot);
	Myvector(Myvector&& ot);
};

template< typename ElementT > 
Myvector< ElementT >::Myvector(const Myvector< ElementT >& ot) {
	//std::cout << "copy constructor"<<'\n';
	elem = make_unique<ElementT[]>(ot.cp);
	cp = ot.cp;
	n = ot.n;
	for (int i = 0; i < n; i++)
		elem[i] = ot.elem[i];
}

template < typename ElementT > 
Myvector< ElementT >& Myvector< ElementT >::operator=(const Myvector< ElementT >& ot) {
	//std::cout << "assigment oerator"<<'\n';
	if (this == &ot) {
		return *this; //trateaza a==a
	}
	elem = make_unique<ElementT[]>(ot.cp);
	n = ot.n;
	cp = ot.cp;
	for (int i = 0; i < n; i++)
		elem[i] = ot.elem[i];
	return *this;
}

template < typename ElementT > 
void Myvector< ElementT >::redim() {

	unique_ptr<ElementT[]> aux = make_unique<ElementT[]>(2 * this->cp);

	for (int i = 0; i < this->n; i++)
		aux[i] = this->elem[i];
	this->cp = 2 * this->cp;
	elem.reset();
	std::swap(elem, aux);
}

/*
* Functia dauga un lement de tip ElementT in vector 
* Date de intrare:-un element de tip ElementT 
* Date de iesire:vectorul va contine o lista in care a fost adaugat si elementul
*/
template < typename ElementT >
void Myvector< ElementT >::push_back(const ElementT& ot) {
	if (n == cp)
	{
		redim();
	}
	elem[n] = ot; //operator de atribuire rules of three ElementT!Aici se face o copie prin assigment operator
	              //=>=>rezulta locatii de memorie diferite la string !De aceea se numeste copie
	n++;
}

/*
* Functia retunreaza numerul de elemente din lista
* Date de intrare:-
* Date de iesire:nr de lemente :int
*/
template < typename ElementT >
int Myvector< ElementT >::size() const noexcept {
	return n;
}

/*
* Functia retuneaza elmentul de pe o pozitie
* Date de intraee:poz-pozitia erlementuli ce trebuie intors/:int
* Date de iesire:-elementul de poz pozitia poz
*/
template < typename ElementT >
ElementT& Myvector< ElementT >::at(int poz) const noexcept {
	//if (poz >= 0 && poz < n)
	return elem[poz];
}

/*
* Se intoarece un iterator pe vector
*/
template < typename ElementT >
Iterator_myvector< ElementT > Myvector< ElementT >::iterator() const noexcept {
	return Iterator_myvector< ElementT >(*this);
}

/*
* Intoarece un itrator pozitonat pe prinul element din vector
*/
template < typename ElementT >
Iterator_myvector< ElementT > Myvector< ElementT >::begin() const noexcept {
	return Iterator_myvector< ElementT >(*this);
}

/*
* Intoarece un iterator pozitionat dupa ultimul element din vector
*/
template < typename ElementT >
Iterator_myvector< ElementT > Myvector< ElementT >::end() const noexcept {
	return Iterator_myvector< ElementT >(*this, n);
}

template < typename ElementT >
void Myvector< ElementT >::erase(const Iterator_myvector< ElementT >& it) {

	for (int i = it.poz + 1; i < n; i++)
	{
		elem[i - 1] = elem[i];
	}
	n--;

}

template < typename ElementT >
Myvector < ElementT >::~Myvector() {
	//delete[] elem;
}

template < typename ElementT >
Myvector < ElementT >& Myvector< ElementT >::operator=(Myvector < ElementT > && ot){
	if (this == &ot)
	{
		return *this;
	}
	
	//delete[] elem; //ai ceva in assigment move
	
	n = ot.n;
	cp = ot.cp;
	//elem = ot.elem;

	elem.reset();
	std::swap(elem, ot.elem);

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.
	ot.elem = nullptr; //Pentru a evita a se sterge elemen cu tot cu Locatari obiecte cand se apeleaza destructorul clasei temporare
	ot.n = 0;
	ot.cp = 0;

	return *this;
}

template < typename ElementT >
Myvector < ElementT >::Myvector(Myvector < ElementT >&& ot) {

	n = ot.n;
	cp = ot.cp;
	elem.reset();
	std::swap(elem, ot.elem);
	
	ot.n = 0;
	ot.cp = 0;
	ot.elem = nullptr;
}

template < typename ElementT > 
ElementT& Myvector < ElementT >::operator[](int poz) {
	return elem[poz];
}