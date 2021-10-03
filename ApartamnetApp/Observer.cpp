#include "Observer.h"

void Observable::addsubsriber(Observer* obs) {
	subscribers.push_back(obs);
}

void Observable::removesubsriber(Observer* obs) {
	subscribers.erase(std::remove(begin(subscribers), end(subscribers), obs), subscribers.end());
}

void Observable::notify() {
	for (Observer* obs : subscribers) //nu pune const!!Update modifica obiectul!Mai ales ca e transmin prin pointer
		obs->update();
}