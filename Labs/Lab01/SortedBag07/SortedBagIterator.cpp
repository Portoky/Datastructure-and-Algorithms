#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->current = 0;
	this->currentUnique = 0;
}
//Theta(1)
TComp SortedBagIterator::getCurrent() {
	if (this->currentUnique == this->bag.nmUniqueElements)
		throw exception();
	else
		return this->bag.elements[currentUnique];
}
//Theta(1)
bool SortedBagIterator::valid() {
	if (this->currentUnique < this->bag.nmUniqueElements)
		return true;
	return false;
}
//Theta(1)
void SortedBagIterator::next() {
	if (this->current < this->bag.frequency[this->currentUnique])
		++this->current;
	if (this->current == this->bag.frequency[this->currentUnique] && this->currentUnique < this->bag.nmUniqueElements)
	{
		this->current = 0;
		++this->currentUnique;
	}
	else if(this->currentUnique == this->bag.nmUniqueElements)
		throw exception();
}
//Theta(1)
void SortedBagIterator::first() {
	this->current = 0;
	this->currentUnique = 0;
}
//Theta(1)
