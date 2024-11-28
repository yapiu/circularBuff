#include <iostream>
#include <thread>
#include "circularBuff.h"

using namespace std;

int main()
{
	circularBuff test(50); //50
	std::vector<int> copyBuff;

	thread th1(&circularBuff::write, &test, std::ref(copyBuff), 500); //500
	thread th2(&circularBuff::read, &test, std::ref(copyBuff), 500);

	th1.join();
	th2.join();

	//test.print();
	cout << endl;
	test.printCopyAr(copyBuff);

	return 0;
}