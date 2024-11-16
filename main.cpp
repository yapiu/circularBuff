#include <iostream>
#include <thread>
#include "circularBuff.h"

using namespace std;

void subtraction_thread(void){
	for (int  i = 0; i < 65; i++) {
		this_thread::sleep_for(chrono::duration<int, std::ratio<1,100>>(9));
		cout << "-";
	}
}

void addition_thread(int number){
	for (int  i = 0; i < number; i++) {
		this_thread::sleep_for(chrono::duration<int, std::ratio<1,100>>(100));
		cout << "+";
	}
}

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