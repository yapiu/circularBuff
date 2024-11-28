#include <vector>

class circularBuff {
protected:
// убрать это отсюда переписать вывод
  char IIN, IOUT;
  int size;
  int* buff;
public:
  circularBuff(int length = 1); 
  ~circularBuff();
  void write(std::vector<int>&,int);
  void read(std::vector<int>&, int);
  void print();
  void printCopyAr(std::vector<int> &copyBuff);
};