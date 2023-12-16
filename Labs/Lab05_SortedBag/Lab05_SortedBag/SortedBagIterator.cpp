#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	stackSize = -1;
	stackCapacity = bag.capacity;

	stack = new int[stackCapacity];
	for (int i = 0; i < stackCapacity; ++i)
		stack[i] = -1; //unnecessary
	int node = bag.root;
	while (node != -1)
	{
		stack[++stackSize] = node; //push
		node = bag.left[node];
		
	}
	if (stackSize >= 0)
	{
		currentNode = stack[stackSize--]; //pop!!
	}
	else
		currentNode = -1;
}
//WC: O(n);
//BC: Theta(log2n)
//overall O(n);

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (!this->valid())
		throw std::exception();
	return bag.elems[currentNode];
}
//theta(1)

bool SortedBagIterator::valid() {
	//TODO - Implementation
	return currentNode != -1;
}
//theta(1)

void SortedBagIterator::next() {
	//TODO - Implementation
	if (!this->valid())
		throw std::exception();
	int node = bag.right[currentNode];
	while (node != -1)
	{
		stack[++stackSize] = node;
		node = bag.left[node];
	}
	if (stackSize >= 0)
	{
		currentNode = stack[stackSize--];
	}
	else
	{
		currentNode = -1;
	}
}
//WC: O(n);
//BC: Theta(1)
//overall O(n);

void SortedBagIterator::first() {
	currentNode = bag.root;
	stackSize = 0;
	for (int i = 0; i < stackCapacity; ++i)
		stack[i] = -1; //unnecessary
	int node = bag.root;
	while (node != -1)
	{
		stack[++stackSize] = node; //push
		node = bag.left[node];

	}
	if (stackSize >= 0)
	{
		currentNode = stack[stackSize--]; //pop!!
	}
	else
		currentNode = -1;
}
//WC: O(n);
//BC: Theta(log2n)
//overall O(n);
