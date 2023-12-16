#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	//TODO - Representation
	TComp* elems;
	int* left;
	int* right;
	int* parent;
	int* next;
	int firstEmpty;
	int root;
	int capacity;
	int length;
	Relation compare;

public:
	//constructor
	SortedBag(Relation r);



	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	void customRemove(int curr);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	void resize();

	int findMin(int currentNode);

	int findTheSame(int startNode, TComp elem);

	int elementsWithThisFrequency(int frequency);

	int elementsWithThisFrequencyUtil(int frequency, int currentNode, TElem* checked, int checkedLength);


	//destructor
	~SortedBag();

	void printStatus();
};