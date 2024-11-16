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
	//seed();
	// thread th1(subtraction_thread);
	// thread th2(addition_thread, 8);

	// cout << "start thread" << endl;

	// th1.join();
	// th2.join();

	// cout << "thread complete" << endl;

	circularBuff test(5);

	thread th1(&circularBuff::write, &test, 10);
	thread th2(&circularBuff::read, &test, 10);

	th1.join();
	th2.join();

	// test.write(6);
	// test.read();
	test.print();
	cout << endl;
	test.printCopyAr();

	return 0;
}