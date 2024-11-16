#include <vector>

class circularBuff {
protected:
  std::vector<int> copyBuff;
  int IIN, IOUT;
  int size;
  int* buff;
public:
  circularBuff(int length = 1); 
  ~circularBuff();
  void write(int);
  void read(int);
  void print();
  void printCopyAr();
};