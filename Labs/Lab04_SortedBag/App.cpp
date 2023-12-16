#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include <crtdbg.h>
#include <assert.h>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

bool therelation(TComp e1, TComp e2) {
	return e1 <= e2;
}

void test()
{
	SortedBag sb(therelation);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	sb.add(13);
	sb.add(5);
	assert(sb.removeAll() == 3);
	assert(sb.search(5) == false);
}

int main() {
	testAll();
	testAllExtended();
	test();
	cout << "Test over" << endl;
	//system("pause");

	_CrtDumpMemoryLeaks();
}
