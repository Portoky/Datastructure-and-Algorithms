#include "MultiMapIterator.h"
#include "MultiMap.h"

struct MultiMap::DLLANode
{
	TElem info;
	int next;
	int prev;
};

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//TODO - Implementation
	currentElement = col.head;
}
//Theta(1)
TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if(this->valid())
		return col.nodes[currentElement].info;
	throw exception();
}
//Theta(1)
bool MultiMapIterator::valid() const {
	//TODO - Implementation
	return currentElement != -1;
}
//Theta(1)
void MultiMapIterator::next() {
	//TODO - Implementation
	if (this->valid())
		currentElement = col.nodes[currentElement].next;
	else
		throw exception();
}
//Theta(1)
void MultiMapIterator::first() {
	//TODO - Implementation
	currentElement = col.head;
}
//Theta(1)
