#include <iostream>
#include <assert.h>
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

bool therelation(TComp e1, TComp e2) {
	return e1 <= e2;
}
int main() {
	testAll();
	testAllExtended();
	
	//test
	SortedBag sb(therelation);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	assert(sb.removeAll() == 6);
	assert(sb.isEmpty() == true);
	sb.add(8);
	assert(sb.nrOccurrences(8) == 1);
	assert(sb.isEmpty() == false);


	cout << "Test over" << endl;
	system("pause");
}
