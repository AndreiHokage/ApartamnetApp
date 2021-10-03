#pragma once
#include "Myvector.h"
#include "Locatar.h"

template < typename ElementT >
class Myvector;

template < typename ElementT >
class Iterator_myvector
{

private:
	const Myvector< ElementT >& v;
	int poz = 0;

public:
	friend class Myvector< ElementT >;

	Iterator_myvector(const Myvector< ElementT >& v) noexcept:v{ v } {

	}

	Iterator_myvector(const Myvector< ElementT >& v, int poz) noexcept :v{ v }, poz{ poz }{

	}

	bool valid() noexcept;

	void next() noexcept; 

	ElementT& element() const noexcept; 

	Iterator_myvector& operator++() noexcept;
	bool operator==(const Iterator_myvector& ot) noexcept;
	bool operator!=(const Iterator_myvector& ot) noexcept;
	Iterator_myvector& operator+(int nr) noexcept;
	ElementT& operator*() const noexcept;
};

template < typename ElementT > 
bool Iterator_myvector< ElementT >::valid() noexcept {
	return poz < v.n;
}

template < typename ElementT >
void Iterator_myvector< ElementT >::next() noexcept {
	poz++;
}

template < typename ElementT >
ElementT& Iterator_myvector< ElementT >::element() const noexcept {
	return v.elem[poz];
}

template < typename ElementT > 
Iterator_myvector< ElementT >& Iterator_myvector< ElementT >::operator++() noexcept {
	next();
	return *this;
}

template < typename ElementT >
bool Iterator_myvector< ElementT >::operator==(const Iterator_myvector< ElementT >& ot)noexcept {
	return (this->poz == ot.poz);
}

template < typename ElementT >
bool Iterator_myvector< ElementT >::operator!=(const Iterator_myvector< ElementT >& ot)noexcept {
	return (this->poz != ot.poz);
}

template < typename ElementT >
ElementT& Iterator_myvector< ElementT >::operator*() const noexcept {
	return element();
}

template < typename ElementT >
Iterator_myvector< ElementT >& Iterator_myvector< ElementT >::operator+(int nr) noexcept {
	this->poz += nr;
	return *this;
}
