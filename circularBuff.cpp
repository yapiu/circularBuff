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
      throw NULL;
    }
  } catch (...) {
    std::cout << "Error: memory could not be allocated" << std::endl;
  }
}

circularBuff::~circularBuff() { delete[] buff; }

void circularBuff::write(std::vector<int> &copyBuff, int numberOfIterations) {
  seed();
  std::cout << "This is circularBuff:" << std::endl;
  for (int i = 0; i < numberOfIterations; i++) {
    std::this_thread::sleep_for(
        std::chrono::duration<int, std::ratio<1, 1000>>(40)); // 10

    buff[IIN] = random_number();
    printf("%d ", buff[IIN]); // дебаг
    IIN++;

    if (IIN == size) {
      IIN = 0;
      std::cout << std::endl; // дебаг
    }
    //   if (IIN == IOUT - 1) {
    //   std::cout << "buff overflow" << std::endl;
    //   exit(-1);
    // }// дает ложный оверфлоу без него все норм работает
  }
  std::cout << "Buffer have written" << std::endl;
}

void circularBuff::read(std::vector<int> &copyBuff, int numberOfIterations) {
  // std::this_thread::sleep_for(std::chrono::duration<int, std::ratio<1, 1000>>(
  //     100)); // 100 время ломает все

  // std::cout << IIN << std::endl;
  // std::cout << IOUT << std::endl;

  if (IOUT < IIN) {
    for (int i = 0; IOUT < IIN; i++) {
      std::this_thread::sleep_for(
          std::chrono::duration<int, std::ratio<1, 1000>>(25)); // 25
      IOUT++;
      numberOfIterations--;
      copyBuff.push_back(buff[i]);
    }
  }

  if (IOUT >= IIN) {
    for (int i = 0; i < numberOfIterations; i++) {
      std::this_thread::sleep_for(
          std::chrono::duration<int, std::ratio<1, 1000>>(75)); // 75
      copyBuff.push_back(buff[IOUT]);
      IOUT++;
      if (IOUT == size) {
        IOUT = 0;
      }
    }
 }

  // if (IIN == IOUT - 1) {
  //   std::cout << "err" << std::endl;
  //   exit(-1);
  // }
  std::cout << "Buffer have read" << std::endl;
}

void circularBuff::printCopyAr(std::vector<int> &copyBuff) {
  std::cout << "This is copyBuff:" << std::endl;
  int flag = 0;
  for (int i = 0; i < copyBuff.size(); i++) {
    printf("%d ", copyBuff[i]);
    flag++;
    if (flag == size) {
      flag = 0;
      std::cout << std::endl;
    }
  }
}

void circularBuff::print() {
  for (int i = 0; i < size; i++) {
    printf("%d ", buff[i]);
  }
}
