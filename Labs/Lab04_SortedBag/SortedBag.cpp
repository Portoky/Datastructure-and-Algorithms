#include <cmath>
#include "SortedBag.h"
#include "SortedBagIterator.h"



SortedBag::SortedBag(Relation r) {
	this->m = 2;
	this->n = 0;
	this->loadFactor = 0.7;
	this->hashTable = new Node * [this->m];
	this->relation = r;
	
	for (int i = 0; i < this->m; ++i)
		this->hashTable[i] = nullptr;
}
//Theta(m)

int SortedBag::hashFunction(TComp element) const //a basic hashing function, not so optimal
{
	if (element < 0)
		element = abs(element);
	return element % this->m;
}
//Theta(1)

void SortedBag::resize()
{
	this->m *= 2;
	Node** newTable = new Node * [this->m];
	Node* current;
	int pos;

	for (int i = 0; i < this->m; ++i)
		newTable[i] = nullptr;

	//creating new hashtable
	for (int i = 0; i < this->m / 2; ++i)
	{
		current = this->hashTable[i];
		while (current != nullptr)
		{
			pos = this->hashFunction(current->info);
			Node* newNode = new Node;
			newNode->info = current->info;
			newNode->next = newTable[pos]; //insertfirst
			newTable[pos] = newNode;

			current = current->next;

		}
	}

	//deleting the old one
	Node* next;
	for (int i = 0; i < this->m / 2; ++i)
	{
		current = this->hashTable[i];
		if (current == nullptr)
			delete current;
		else {
			while (current != nullptr)
			{
				next = current->next;
				delete current;
				current = next;
			}
		}
	}
	//done
	delete[] this->hashTable;
	this->hashTable = newTable;
}
//Theta(m+n) -:Theta(m)

void SortedBag::add(TComp e) {
	
	if (this->loadFactor <= (double)this->n / this->m)
		resize();

	int pos = this->hashFunction(e);
	Node* newNode = new Node;
	//insertfirst
	newNode->info = e;
	newNode->next = this->hashTable[pos];
	this->hashTable[pos] = newNode;
	++this->n;

}
//BC Theta(1) -> when we just insert an element
//WC Theta(resize()) //in case we need to resize the hashtable first
//Overall: O(resize())

bool SortedBag::remove(TComp e) {
	int pos = this->hashFunction(e);

	if(this->hashTable[pos] == nullptr)
		return false;

	Node* current = this->hashTable[pos];
	Node* prev = nullptr;
	//if on the first place
	if (current->info == e)
	{
		this->hashTable[pos] = current->next;
		delete current;

		--this->n;
		return true;
	}


	while (current != nullptr && current->info != e)
	{
		prev = current;
		current = current->next;
	}
	if(current == nullptr) //not found;
		return false;

	prev->next = current->next;
	delete current;
	--this->n;
	return true;
}
//BC:Theta(1) the result of the hash 
//WC: O(number of elements in the linked list)
//overall: O(number of elements in the linked list)

int SortedBag::removeAll()
{
	int count = 0;
	Node* next;
	Node* current;
	Node* start;
	for (int i = 0; i < this->m; ++i)
	{
			int countToRemove = 0;
			start = this->hashTable[i];
			current = this->hashTable[i];
			while(start !=  nullptr){
				countToRemove = 0;
				
				while (current != nullptr)
				{
					next = current->next;
					if (current->info == start->info)
						countToRemove++;
					current = next;
				}
				if (countToRemove >= 2)
				{
					TComp info = start->info;
					for (int j = 0; j < countToRemove; ++j)
						remove(info);
					count += countToRemove;
					start = this->hashTable[i];
					current = this->hashTable[i];
				}
				else
				{
					start = start->next;
					current = start;
				}
			}
	}

	//reinitialize

	return count;
}
//Theta(m + n);

bool SortedBag::search(TComp elem) const {
	int pos = this->hashFunction(elem);
	if(this->hashTable[pos] == nullptr)
		return false;

	Node* current = this->hashTable[pos];
	while (current != nullptr)
	{
		if (current->info == elem)
			return true;
		current = current->next;
	}
	return false;
}
//BC:Theta(1) the result of the hash 
//WC: O(number of elements in the linked list)
//overall: O(number of elements in the linked list)

int SortedBag::nrOccurrences(TComp elem) const {
	int pos = this->hashFunction(elem);

	Node* current = this->hashTable[pos];
	int count = 0;
	while (current != nullptr)
	{
		if (current->info == elem)
			++count;
		current = current->next;
	}

	return count;
}
//Theta(number of elements in the linked list);


int SortedBag::size() const {

	return this->n;
}
//theta(1)

bool SortedBag::isEmpty() const {
	
	return this->n == 0;
}
//theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	Node* next;
	Node* current;
	for (int i = 0; i < this->m; ++i)
	{
		current = this->hashTable[i];
		if (current == nullptr)
			delete current;
		else {
			while (current != nullptr)
			{
				next = current->next;
				delete current;
				current = next;
			}
		}
	}

	delete[] this->hashTable;
}
//theta(m+n)