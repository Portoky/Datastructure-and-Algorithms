#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

void merge(TComp* array, int begin, int mid, int end, Relation r)
{
	int n1 = mid - begin + 1; //number of elements;
	int n2 = end - mid;

	TComp* arr1 = new TComp[n1];
	TComp* arr2 = new TComp[n2];

	for (int i = 0; i < n1; ++i)
		arr1[i] = array[begin + i];
	for (int i = 0; i < n2; ++i)
		arr2[i] = array[mid + i + 1];
	
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n1 && j < n2)
	{
		if (r(arr1[i], arr2[j]))
		{
			array[begin + k] = arr1[i++];
		}
		else
		{
			array[begin + k] = arr2[j++];
		}
		++k;
	}

	while (i < n1)
	{
		array[begin + k] = arr1[i];
		++k;
		++i;
	}
	while (j < n2)
	{
		array[begin + k] = arr2[j];
		++k;
		++j;
	}

	delete[] arr1;
	delete[] arr2;

}

void mergeSort(TComp* array, int begin, int end, Relation r)
{
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid, r);
	mergeSort(array, mid + 1, end, r);
	merge(array, begin, mid, end, r);
}

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->array = new TComp[b.n+1];
	this->size = 0;
	this->index = 0;


	for (int i = 0; i < b.m; ++i)
	{
		if (b.hashTable[i] != nullptr)
		{
			Node* current = b.hashTable[i];
			while (current != nullptr)
			{
				array[size++] = current->info;
				current = current->next;
			}
		}
	}
	//bubble sorting
	//TODO OPTIMIZE WITH MERGE SORT done :)
	/*for (int i = 0; i < this->size - 1; ++i)
	{
		for (int j = i + 1; j < this->size; ++j)
		{
			if (!b.relation(array[i], array[j]))
			{
				TComp tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}*/

	mergeSort(this->array, 0, this->size-1, b.relation);

	//setting the first pos;
	first();
}
//theta(capacity) + O(nlogn) (bubble sort) = O(m + nlogn)

SortedBagIterator::~SortedBagIterator()
{
	delete[] this->array;
}



TComp SortedBagIterator::getCurrent() {
	if (!this->valid())
		throw std::exception();
	return this->array[this->index];
}
//Theta(1)

bool SortedBagIterator::valid() {
	return this->index < this->size;
}
//Theta(1)

void SortedBagIterator::next() {
	if (!valid())
		throw std::exception();
	++this->index;
}
//Theta(1)

void SortedBagIterator::first() {
	this->index = 0;
}
//Theta(1)

