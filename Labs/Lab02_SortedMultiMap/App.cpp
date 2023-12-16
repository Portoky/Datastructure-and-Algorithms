#include <iostream>
#include <assert.h>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
typedef int TValue;
bool therelation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}


int main(){
    testAll();
	testAllExtended();

	//test for valueBag()
	{
		SortedMultiMap map(therelation1);

		map.add(1, 2);
		map.add(5, 6);
		map.add(7, 2);
		map.add(2, 2);

		std::vector<TValue> result = map.valueBag();
		assert(result.size() == 4);
		map.remove(7, 2);
		result = map.valueBag();
		assert(result.size() == 3);
		SMMIterator it = map.iterator();
		int count = 0;
		while (it.valid())
		{
			std::cout << it.getCurrent().second << " " << result[count++] << "\n";
			it.next();
		}
	}

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
