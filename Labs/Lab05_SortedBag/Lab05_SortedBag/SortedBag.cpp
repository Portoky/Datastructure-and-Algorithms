#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;

SortedBag::SortedBag(Relation r) {
	length = 0;
	capacity = 128;
	firstEmpty = 0;
	root = -1;
	compare = r;
	elems = new TComp[capacity];
	left = new int[capacity];
	right = new int[capacity];
	next = new int[capacity];
	parent = new int[capacity];

	for (int i = 0; i < capacity; ++i)
	{
		next[i] = i + 1;
		elems[i] = NULL_TCOMP;
		left[i] = -1;
		right[i] = -1;
		parent[i] = -1;
	}
	next[capacity  - 1] = -1;
}
//Theta capacity


void SortedBag::add(TComp e) {
	//TODO - Implementation
	if (next[firstEmpty] == -1 || length == capacity-1)
		resize();
	if (length == 0)
	{
		root = firstEmpty;
		elems[root] = e;
		left[root] = -1;
		right[root] = -1;
		firstEmpty = next[firstEmpty];
	}
	else
	{
		//search its position
		int current = root;
		int previous = -1;
		while (current != -1)
		{
			previous = current;
			if (compare(e, elems[current]))
			{
				current = left[current];
			}
			else
			{
				current = right[current];
			}
		}

		int pos = firstEmpty;
		firstEmpty = next[firstEmpty];
		if (compare(e, elems[previous]))
		{
			left[previous] = pos;
		}
		else if(right[previous] == -1)
		{
			right[previous] = pos;
		}
		parent[pos] = previous;
		left[pos] = -1;
		right[pos] = -1;
		elems[pos] = e;
		int k = 0;
	}
	++length;
}
//BC Theta(logn);
//WC O(n);
//overall O(n);

bool SortedBag::remove(TComp e) {
	//TODO - Implementation
	if (length == 0)
		return false;
	if (length == 1)
	{
		if (elems[root] == e)
		{
			elems[root] = NULL_TCOMP;
			parent[root] = -1;
			left[root] = -1;
			right[root] = -1;
			next[root] = firstEmpty;
			firstEmpty = root;
			root = -1;
			--length;
			return true;
		}
		return false;
	}

	//finding the element
	int current = root;
	int previous = -1;
	while (current != -1 && elems[current] != e)
	{
		previous = current;
		if (compare(e, elems[current]))
		{
			current = left[current];
		}
		else
		{
			current = right[current];
		}
	}
	if (current == -1)
		return false;

	//counting the kiddos
	int kids = 0;
	if (left[current] != -1)
		++kids;
	if (right[current] != -1)
		++kids;

	if (kids == 0) 
	{
		//destroying the link with parent
		if (left[previous] == current)
			left[previous] = -1;
		else
			right[previous] = -1;
		
		//destroying node
		elems[current] = NULL_TCOMP;
		parent[current] = -1;
		left[current] = -1;
		right[current] = -1;
		next[current] = firstEmpty;
		firstEmpty = current;
	}
	else if (kids == 1)//what about if it is root?
	{
		//getting the child node;
		int childNode = -1;
		if (left[current] != -1)
			childNode = left[current];
		else
			childNode = right[current];

		if (root == current)
		{
			root = childNode;
			//std::cout << "\nROOT CHANGED TO: " << root << "\n";
		}
		//relinking to the child non root
		else if (left[previous] == current)
			left[previous] = childNode;
		else
			right[previous] = childNode;
		parent[childNode] = previous;

		

		//destroying node
		elems[current] = NULL_TCOMP;
		parent[current] = -1;
		left[current] = -1;
		right[current] = -1;
		next[current] = firstEmpty;
		firstEmpty = current;

	}
	else if (kids == 2)
	{
		int rightChild = right[current];
		int minNode = findMin(rightChild);
		elems[current] = elems[minNode];
		//todo
		customRemove(minNode);

		//fix?? case that was not mentioend when storing duplicates in bst
		//int pos =  findTheSame(rightChild, elems[current]);
		if (elems[current] == elems[rightChild]) {
			int newRightChild = right[rightChild];
			minNode = findMin(rightChild);
			left[minNode] = left[current];
			left[current] = rightChild;
			right[current] = newRightChild;
			right[rightChild] = -1;
		}
		/*if (pos != -1 && parent[pos] != current) {
			int newRightChild = right[pos];
			minNode = findMin(pos);
			int parentNode = parent[pos];
			left[parentNode] = right[pos];
			right[pos] = -1;

			left[minNode] = left[current];
			left[current] = pos;
			right[pos] = -1;
		}
		else if (pos != -1)
		{
			int newRightChild = right[rightChild];
			minNode = findMin(rightChild);
			left[minNode] = left[current];
			left[current] = rightChild;
			right[current] = newRightChild;
			right[rightChild] = -1;
		}*/

	}
	--length;
	return true;
}
//Best Case Theta(logn)
//Worts Case O(n)

void SortedBag::customRemove(int curr) //only for nodes with 0 or 1 child to the right
{
	int prev = parent[curr];
	int child = -1;
	if (right[curr] != -1)
		child = right[curr];
	if (right[curr] != -1)
	{
		if (left[prev] == curr)
		{
			left[prev] = child;//!!!!
		}
		else //right[prev] == curr in case there was no left child at all for the right child
		{
			right[prev] = child;
		}
		parent[child] = prev;
	}
	else //no kids!
	{
		if (left[prev] == curr)
			left[prev] = -1;
		else
			right[prev] = -1;
	}
	parent[curr] = -1;
	elems[curr] = NULL_TCOMP;
	next[curr] = firstEmpty;
	left[curr] = -1;
	right[curr] = -1;
	firstEmpty = curr;
}


bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
	int pos = root;
	while (pos != -1)
	{
		if (elem == elems[pos])
			return true;
		if (compare(elem, elems[pos]))
			pos = left[pos];
		else
			pos = right[pos];
	}
	return false;
}
//BC: Theta(logn)
//Wc: O(n)
//Overall O(n)

int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	int nm = 0;
	int pos = root;
	while (pos != -1)
	{
		if (elem == elems[pos])
			++nm;
		if (compare(elem, elems[pos]))
			pos = left[pos];
		else
			pos = right[pos];
	};
	return nm;
}
//BC: Theta(logn)
//WC: O(n)
//Overall O(n)


int SortedBag::size() const {
	//TODO - Implementation
	return length;
}
//theta 1

bool SortedBag::isEmpty() const {
	//TODO - Implementation
	return length == 0;
}
//theta 1

void SortedBag::resize()
{
	//printStatus();
	TComp* newElems = new TComp[capacity * 2];
	int* newNext = new int[capacity * 2];
	int* newLeft = new int[capacity * 2];
	int* newRight = new int[capacity * 2];
	int* newParent = new int[capacity * 2];
	for (int i = 0; i < capacity; ++i)
	{
		newElems[i] = elems[i];
		newNext[i] = next[i];
		newLeft[i] = left[i];
		newRight[i] = right[i];
		newParent[i] = parent[i];
	}
	for (int i = capacity; i < capacity * 2; ++i)
	{
		newElems[i] = NULL_TCOMP;
		newNext[i] = i+1;
		newLeft[i] = -1;
		newRight[i] = -1;
		newParent[i] = -1;
	}

	delete[] elems;
	delete[] next;
	delete[] left;
	delete[] right;
	delete[] parent;

	elems = newElems;
	next = newNext;
	left = newLeft;
	right = newRight;
	parent = newParent;
	next[firstEmpty] = capacity;
	capacity *= 2;
	//printStatus();
}
//Theta(capacity*2);


int SortedBag::findMin(int currentNode)
{
	while (left[currentNode] != -1) {
		currentNode = left[currentNode];
	}
	return currentNode;
}

int SortedBag::findTheSame(int startNode, TComp elem)
{
	int current = startNode;
	while (current != -1)
	{
		if (elems[current] == elem)
			return current;
		current = left[current];
	}
	return -1;
}

int SortedBag::elementsWithThisFrequency(int frequency)
{
	int nmOfElements = 0;
	int node = root;
	if (frequency <= 0)
		throw std::exception();
	
	TElem* checked = new TElem[capacity];
	int checkedlength = 0;

	int result = elementsWithThisFrequencyUtil(frequency, root, checked, checkedlength);

	return result;

}
//Theta(n) * complexity of number of occurences => Theta(n) * O(n) = O(n^2)

int SortedBag::elementsWithThisFrequencyUtil(int frequency, int currentNode, TElem* checked, int checkedLength)
{
	if (currentNode == -1)
		return 0;
	int sum = 0;
	int i;
	for (i = 0; i < checkedLength; ++i)//check if it has been already counted
		if (checked[i] == elems[currentNode])
			break;
	if (i == checkedLength)//no such elements checked yet
	{
		checked[checkedLength++] = elems[currentNode];

		if (nrOccurrences(elems[currentNode]) == frequency)
			sum += 1;
	}
	sum += elementsWithThisFrequencyUtil(frequency, left[currentNode], checked, checkedLength);
	sum += elementsWithThisFrequencyUtil(frequency, right[currentNode], checked, checkedLength);

	return sum;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] elems;
	delete[] next;
	delete[] left;
	delete[] right;
	delete[] parent;
}

void SortedBag::printStatus()
{
	cout << "Root" << root << "\n";
	cout << "Capacity" << capacity << "\n";
	cout << "Size" << length << "\n";
	cout << "Elems:\n";
	for (int i = 0; i < length; ++i)
	{
		cout << elems[i] << " ";
	}
	cout << "\nLeft\n";
	for (int i = 0; i < length; ++i)
	{
		cout << left[i] << " ";
	}
	cout << "\nRight\n";
	for (int i = 0; i < length; ++i)
	{
		cout << right[i] << " ";
	}

}
