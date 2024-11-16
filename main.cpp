#include <iostream>
#include <thread>
#include "circularBuff.h"

using namespace std;

int main()
{
	circularBuff test(5);

	thread th1(&circularBuff::write, &test, 10);
	thread th2(&circularBuff::read, &test, 10);

	th1.join();
	th2.join();

	test.print();
	cout << endl;
	test.printCopyAr();

	return 0;
}