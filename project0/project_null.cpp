#include <iostream>
#include "mr_line.h"
using namespace std;

int main()
{
  // remember that integers are 4 bytes each, so ... 5 * 4 + 100 * 4 = 420 ;-)
  auto m1 = MrLine(5);
  auto m2 = MrLine(100);
  // we never actually freed this memory because we were bad.  
  auto m3 = m2;
  // one uses assignment one uses copy constructor
  auto m4(m3);
  return 0;
}
