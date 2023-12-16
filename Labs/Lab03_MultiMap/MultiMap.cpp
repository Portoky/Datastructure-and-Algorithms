#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

struct MultiMap::DLLANode
{
	TElem info;
	int next;
	int prev;
};

MultiMap::MultiMap() {
	head = -1;
	tail = -1;
	capacity = 10;
	nodes = new DLLANode[capacity];
	for (int i = 0; i < capacity - 1; ++i)
	{
		nodes[i].next = i + 1;
		nodes[i].prev = i - 1;
	}
	nodes[capacity - 1].next = -1;
	nodes[capacity - 1].prev = capacity - 2;

	firstFree = 0;
	length = 0;
}
//Theta(capacity)

int MultiMap::allocatePosition()
{
	if (this->firstFree == -1)
	{
		//reenitialize, and copy
		this->capacity *= 2;
		PNode newnodes = new DLLANode[capacity];
		for (int i = 0; i < capacity - 1; ++i)
		{
			newnodes[i].next = i + 1;
			newnodes[i].prev = i - 1;
		}
		newnodes[capacity - 1].next = -1;
		newnodes[capacity - 1].prev = capacity - 2; //so everything remains okay if we want to add more element to the multimap

		//copy previous elements
		for (int i = 0; i < this->length; ++i)
		{
			newnodes[i] = this->nodes[i];
		}

		//delete[] this->nodes;
		this->nodes = newnodes;
		
		this->firstFree = capacity / 2;
	}
	int newFreepos = this->firstFree;
	this->firstFree = nodes[firstFree].next;
	return newFreepos;
}
//bestcase Theta(1) //when we still have free space
//worst case Theta(capacity*2) //when there is no more free pcae and we need to allcoate more
//overall Theta(capacity*2)

 
void MultiMap::freePosition(int pos)
{
	this->nodes[pos].next = firstFree;
	//this->nodes[pos].prev = tail;
	this->nodes[pos].info = NULL_TELEM;
	firstFree = pos;
}
//Theta(1)

//here well do an insertfirst
void MultiMap::add(TKey c, TValue v) {
	int newPosition = allocatePosition();
	/*this->nodes[newPosition].info = std::make_pair(c, v);
	this->nodes[newPosition].next = -1;
	this->nodes[newPosition].prev = tail;
	if (head == -1) //elemenet at all
	{
		head = newPosition;
		tail = newPosition;
	}
	else
	{
		this->nodes[tail].next = newPosition;
		this->nodes[newPosition].prev = tail;
		tail = newPosition;
	}
	++length;*/

	if (head == -1) //no element at all
	{
		head = newPosition;
		tail = newPosition;
		this->nodes[newPosition].info = std::make_pair(c, v);
		this->nodes[newPosition].next = -1;
		this->nodes[newPosition].prev = -1;
	}
	else
	{
		this->nodes[newPosition].info = std::make_pair(c, v);
		this->nodes[newPosition].next = head;
		this->nodes[newPosition].prev = -1;
		this->nodes[head].prev = newPosition;
	}
	head = newPosition;
	++length;

}
//same complexity as allocate position

bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int current = head;
	int prev = -1;
	while (current != -1 && (this->nodes[current].info.first != c || this->nodes[current].info.second != v))
	{
		prev = current;
		current = this->nodes[current].next;
	}
	if(current == -1)
		return  false;
	if (current == head)
		head = this->nodes[head].next;
	if (current == tail)
	{
		tail = this->nodes[tail].prev;
	}
	if(current != tail && current != head)
	{
		this->nodes[prev].next = this->nodes[current].next;
		this->nodes[this->nodes[current].next].prev = this->nodes[current].prev; //= prev
	}
	freePosition(current);
	--length;
	if (length == 0)
	{
		//delete[] this->nodes;
		head = -1;
		tail = -1;
		capacity = 10;
		nodes = new DLLANode[capacity];
		for (int i = 0; i < capacity - 1; ++i)
		{
			nodes[i].next = i + 1;
			nodes[i].prev = i - 1;
		}
		nodes[capacity - 1].next = -1;
		nodes[capacity - 1].prev = capacity - 2;

		firstFree = 0;
		length = 0;
	}
	return true;
}
//Best case: the searched element on first position: Theta(1)
//Worst case: the searched element on last position Theta(n)
//overall O(n)

vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation
	std::vector<TValue> result;
	int current = head;
	while (current != -1)
	{
		if (this->nodes[current].info.first == c)
			result.push_back(this->nodes[current].info.second);
		current = this->nodes[current].next;
	}
	return result;

}
//Theta(n)

vector<TValue> MultiMap::removeKey(TKey key)
{
	vector<TValue> result;
	int current = head;
	int prev = -1;
	int tmp;
	while (current != -1)
	{
		if (this->nodes[current].info.first == key)
		{
			tmp = current;
			result.push_back(this->nodes[current].info.second);
			if (current == head)
				head = this->nodes[head].next;
			else if (current == tail)
			{
				tail = this->nodes[tail].prev;
			}
			else if (current != tail && current != head)
			{
				this->nodes[prev].next = this->nodes[current].next;
				this->nodes[this->nodes[current].next].prev = this->nodes[current].prev; //= prev
			}
			prev = current;
			current = this->nodes[current].next;
			freePosition(tmp);
			length--;
		}
		else
		{
			prev = current;
			current = this->nodes[current].next;
		}

	}
	
	if (length == 0)
	{
		head = -1;
		tail = -1;
		capacity = 10;
		nodes = new DLLANode[capacity];
		for (int i = 0; i < capacity - 1; ++i)
		{
			nodes[i].next = i + 1;
			nodes[i].prev = i - 1;
		}
		nodes[capacity - 1].next = -1;
		nodes[capacity - 1].prev = capacity - 2;

		firstFree = 0;
		length = 0;
	}
	return result;
}
int MultiMap::size() const {
	//TODO - Implementation
	return length;
}
//Theta(1)

bool MultiMap::isEmpty() const {
	//TODO - Implementation
	return length == 0;
}
//Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
//Theta(1)

MultiMap::~MultiMap() {
	delete[] nodes;
}
//Theta(1)
