#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
	TComp* array;
	int index;
	int size;

public:
	~SortedBagIterator();
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

