#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBag::SortedBag(Relation r) {
	if (r == NULL)
		throw exception();
	this->compare = r;
	this->capacity = 10;
	this->nmUniqueElements = 0;
	this->elements = new TElem[this->capacity];
	this->frequency = new int[this->capacity];
}

void SortedBag::add(TComp e) {
	//in this case we create new arrays and copy the elements

	if (SortedBag::search(e) == false)
	{
		if (this->nmUniqueElements == this->capacity)
		{
			TElem* new_elements = new TElem[this->capacity * 2];
			int* new_frequency = new int[this->capacity * 2];

			for (int i = 0; i < this->nmUniqueElements; ++i)
			{
				new_elements[i] = this->elements[i];
				new_frequency[i] = this->frequency[i];
			}
			delete[] this->elements;
			delete[] this->frequency;
			this->elements = new_elements;
			this->frequency = new_frequency;
			this->capacity *= 2;
			for (int i = this->nmUniqueElements;i < this->capacity; ++i)
			{
				this->elements[i] = NULL_TCOMP;
				this->frequency[i] = 0;
			}
		}
		//now we add the new elements; we move elements further 
		int index_to_put = 0;
		while (index_to_put < this->nmUniqueElements && !this->compare(e, this->elements[index_to_put]))
		{
			++index_to_put;
		}
		for (int i = this->nmUniqueElements; i > index_to_put; --i)
		{
			this->elements[i] = this->elements[i - 1];
			this->frequency[i] = this->frequency[i - 1];
		}
		++this->nmUniqueElements;
		this->elements[index_to_put] = e;
		this->frequency[index_to_put] = 1;
	}
	else
	{
		int index_to_increase = 0;
		while (this->elements[index_to_increase] != e)
		{
			++index_to_increase;
		}
		++this->frequency[index_to_increase];
	}
}
//bestcase theta(1)
//worstcase theta(n)
//Theta(n)

bool SortedBag::remove(TComp e) {
	int index_to_remove = 0;
	while (index_to_remove < this->nmUniqueElements && this->elements[index_to_remove] != e)
		++index_to_remove;
	if (index_to_remove < this->nmUniqueElements && this->elements[index_to_remove] == e)
	{
		--this->frequency[index_to_remove];
		if (this->frequency[index_to_remove] == 0)
		{
			for (int i = index_to_remove; i < this->nmUniqueElements - 1; ++i)
			{
				this->elements[i] = this->elements[i + 1];
				this->frequency[i] = this->frequency[i + 1];
			}
			--this->nmUniqueElements;
		}
		return true;
	}
	return false;
}
//bestcase: Theta(1);
//worstcase: theta(n)
//Theta(n)

bool SortedBag::search(TComp elem) const {
	for (int i = 0; i < this->nmUniqueElements; ++i)
	{
		if (this->elements[i] == elem)
			return true;
	}
	return false;
}
//Theta(n)

int SortedBag::nrOccurrences(TComp elem) const {
	int index_for_occurences;
	for (index_for_occurences = 0; index_for_occurences < this->nmUniqueElements && this->elements[index_for_occurences] != elem; ++index_for_occurences);
	if (index_for_occurences < this->nmUniqueElements)
		return this->frequency[index_for_occurences];
	return 0;
}
//Theta(n)


int SortedBag::size() const {
	int sum = 0;
	for (int i = 0; i < this->nmUniqueElements; ++i)
		sum += this->frequency[i];
	return sum;
}
//Theta(n)

bool SortedBag::isEmpty() const {
	return this->nmUniqueElements == 0;
}
//Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)

SortedBag::~SortedBag() {
	delete[] this->elements;
	delete[] this->frequency;
}
//Theta(1)

int SortedBag::removeAll()
{
	int counter = 0;
	for (int i = 0; i < this->nmUniqueElements; ++i)
	{
		counter += this->frequency[i];
		this->frequency[i] = 0;
		this->elements[i] = -1;
	}
	this->nmUniqueElements = 0;
	return counter;
}
//Theta(n)