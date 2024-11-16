#include "circularBuff.h"
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>


void seed() {
  time_t curtime;
  time(&curtime);
  srand((unsigned int)curtime);
}

int random_number() { return rand() % 10; }

circularBuff::circularBuff(int length) {
  size = length;
  IIN = 0;
  IOUT = 0;
  buff = new int[size];

  try {
    if (buff == NULL) {
      throw buff;
    }
  } catch (...) {
    std::cout << "Error: memory could not be allocated" << std::endl;
  }
}

circularBuff::~circularBuff() { delete[] buff; }

void circularBuff::write(int numberOfIterations) {
  seed();
  for (int i = 0; i < numberOfIterations; i++) {
    std::this_thread::sleep_for(
        std::chrono::duration<int, std::ratio<1, 100>>(200));
    buff[IIN] = random_number();
    printf("[%d]: %d \n",IIN, buff[IIN]); // дебаг
    IIN++;
    if (IIN == size) {
      IIN = 0;
    }
  }
  std::cout << "Buffer have written" << std::endl;
}

void circularBuff::read(int numberOfIterations) {
  std::this_thread::sleep_for(std::chrono::duration<int, std::ratio<1, 100>>(400));

  // std::cout << IIN << std::endl;
  // std::cout << IOUT << std::endl;

  if (IOUT < IIN) {
    for (int i = 0; IOUT < IIN; i++) {
      std::this_thread::sleep_for(std::chrono::duration<int,std::ratio<1,100>>(100));
      IOUT++;
      numberOfIterations--;
      copyBuff.push_back(buff[i]);
    }
  }

  if (IOUT >= IIN) {
    for (int i = 0; i < numberOfIterations; i++) {
      std::this_thread::sleep_for(std::chrono::duration<int,std::ratio<1,100>>(300));
      copyBuff.push_back(buff[IOUT]);
      IOUT++;
      if (IOUT == size) { // ПОЧЕМУ НЕ МИНУС ОДИН(((((())))))
        IOUT = 0;
      }
    }
  }

  if (IIN == IOUT - 1) {
    std::cout << "err" << std::endl;
    exit(-1);
  }
  std::cout << "Buffer have read" << std::endl;
}

void circularBuff::printCopyAr() {
  for (int i = 0; i < copyBuff.size(); i++) {
    printf("%d ", copyBuff[i]);
  }
}

void circularBuff::print() {
  for (int i = 0; i < size; i++) {
    printf("%d ", buff[i]);
  }
}
