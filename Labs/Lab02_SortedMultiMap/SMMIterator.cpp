#include "SMMIterator.h"
#include "SortedMultiMap.h"

struct SortedMultiMap::SLLNode {
	TElem info;
	PNode next;
	SLLNode(TElem e, PNode n);
};

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	this->currentElement = d.head;
}
//Theta(1)
void SMMIterator::first(){
	//TODO - Implementation
	this->currentElement = map.head;
}
//Theta(1)
void SMMIterator::next(){
	//TODO - Implementation
	if (this->currentElement == NULL) throw exception();
	this->currentElement = this->currentElement->next;
}
//Theta(1)
bool SMMIterator::valid() const{
	//TODO - Implementation
	return currentElement != NULL;
}
//Theta(1)
TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (currentElement == NULL) throw exception();
	return currentElement->info;
}
//Theta(1)

