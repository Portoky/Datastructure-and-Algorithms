#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <assert.h>
//#include "ExtendedTest2.cpp"

using namespace std;

bool relation(TComp e1, TComp e2) {
	return e1 <= e2;
}

void test()
{
	SortedBag sb(relation);
	sb.add(6);
	sb.add(5);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	sb.add(5);

	assert(sb.elementsWithThisFrequency(1) == 4);
	assert(sb.elementsWithThisFrequency(3) == 1);
	try {
		sb.elementsWithThisFrequency(0);
	}
	catch (std::exception)
	{
		cout << "Exception catched\n";
	}
}

int main() {
	testAll();
	testAllExtended();
	test();
	cout << "Test over" << endl;
	system("pause");
}
