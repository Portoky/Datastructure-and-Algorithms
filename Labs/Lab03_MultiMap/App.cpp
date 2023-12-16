#include <iostream>
#include <assert.h>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;



int main() {

	//test
	 {
		MultiMap map;
		map.add(1, 2);
		map.add(1, 3);
		map.add(2, 4);
		MultiMapIterator it = map.iterator();
		vector<TValue> res = map.removeKey(1);
		assert(res.size() == 2);
		assert(map.size() == 1);
	}
	/*testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");*/

}
