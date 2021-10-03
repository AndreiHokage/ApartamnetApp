#pragma once
#include <vector>
using std::vector;

class Observer
{
public:
	virtual void update() = 0;

	virtual ~Observer() = default;
};

class Observable
{

private:
	vector < Observer* > subscribers;

public:

	Observable() = default;

	void addsubsriber(Observer* obs);

	void removesubsriber(Observer* obs);

	void notify();

	~Observable() {

	}
};
