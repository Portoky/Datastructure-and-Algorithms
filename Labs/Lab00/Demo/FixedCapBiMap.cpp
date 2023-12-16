#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 5)
		throw exception();
	this->capacity = capacity;
	this->nmPairs = 0;
	this->elements = new TElem[this->capacity];

}
//Theta(capacity)

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}
//Theta(1)

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->capacity == this->nmPairs)
		throw exception();
	int index = 0;
	int count = 0;
	while (count < 2 && index < this->nmPairs)
	{
		if (this->elements[index].first == c)
			++count;
		++index;
	}
	if (count == 2)
	{
		return false;
	}
	else
	{
		this->elements[this->nmPairs].first = c;
		this->elements[this->nmPairs].second = v;
		++this->nmPairs;
		return true;
	}
}
//Best Case: Theta(1)
//Worst Case: Theta(nmParis) => total complexity Tehta(nmPairs)

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair found;
	found.first = NULL_TVALUE;
	found.second = NULL_TVALUE;
	for(int i = 0; i < this->nmPairs && found.second == NULL_TVALUE; ++i)
		if (this->elements[i].first == c)
		{
			if (found.first == NULL_TVALUE)
				found.first = this->elements[i].second;
			else
				found.second = this->elements[i].second;
		}
	return found;
}
//Best Case: Theta(1)
//Worst Case: Theta(nmParis) => total complexity Tehta(nmPairs)

bool FixedCapBiMap::remove(TKey c, TValue v){
	int index = 0;
	bool found = false;
	while (index < this->nmPairs && found == false)
	{
		if (this->elements[index].first == c && this->elements[index].second == v)
			found = true;
		else
			++index;
	}
	if (found == true)
	{
		this->elements[index] = this->elements[this->nmPairs - 1];
		--this->nmPairs;
		return true;
	}

	return false;
}
//Best Case: Theta(1)
//Worst Case: Theta(nmParis) => total complexity Tehta(nmPairs)

//these are Theta of 1
int FixedCapBiMap::size() const {
	return this->nmPairs;
}

bool FixedCapBiMap::isEmpty() const{
	if (this->nmPairs == 0)
		return true;
	return false;
}

bool FixedCapBiMap::isFull() const {
	if (this->nmPairs == this->capacity)
		return true;
	return false;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



