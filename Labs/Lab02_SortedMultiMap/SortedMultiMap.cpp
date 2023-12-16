#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->head = NULL;
	this->compare = r;
	this->length = 0;
}
//Theta(1)
SortedMultiMap::SortedMultiMap(const SortedMultiMap& map)
{
	this->head = map.head;
	this->compare = map.compare;
	this->length = map.length;
}
//theta(1)
struct SortedMultiMap::SLLNode {
	TElem info;
	PNode next;
	SLLNode(TElem e, PNode n);
};

SortedMultiMap::SLLNode::SLLNode(TElem e, PNode n)
{
	info = e;
	next = n;
}
//theta(1)
void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	TElem e = std::make_pair(c, v); //elem to Be added
	PNode node = new SLLNode(e, NULL);
	PNode current = this->head;
	PNode prev = NULL;
	while (current != NULL && this->compare(current->info.first, e.first))
	{
		prev = current;
		current = current->next;
	}
	if (current == this->head) // we have to insert to the head
	{
		if(this->size() == 0) //empty list
			head = node;
		else
		{
			node->next = head;
			head = node;
		}
	}
	else if (current == NULL) //we are at the end of the linked list
	{
		prev->next = node;
	}
	else //normal state
	{
		node->next = prev->next;
		prev->next = node;
	}
	++this->length;
}
//best case: O(1)
//worst case: O(n)
//average case: O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> result;
	PNode current = this->head;
	while (current != NULL)
	{
		if (current->info.first == c)
			result.push_back(current->info.second);
		current = current->next;
	}
	return result;
}
//best case: Theta(1) //todo description
//worst case: Theta(n)
//overall : O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	PNode prev = NULL;
	PNode current = head;
	TElem e = std::make_pair(c, v);
	while (current != NULL && current->info != e)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return false;
	if (current == head)
	{
		head = head->next;
	}
	else 
	{
		prev->next = current->next;
	}

	delete current;
	--this->length;

	return true;
}
//Best case: O(1)
//Worst case: O(n)
//Average case: O(n)

int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->length;
}
//Theta(1)
bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	if (this->head == NULL)
		return true;
	return false;
}
//Theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

vector<TValue> SortedMultiMap::valueBag() const
{
	vector<TValue> values;
	PNode current = this->head;
	while (current != NULL)
	{
		values.push_back(current->info.second);
		current = current->next;
	}
	return values;
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	while (head != NULL)
	{
		PNode p = head;
		head = head->next;
		delete p;
	}
	
}
//Theta(n)

