#include <iostream>
#include "usage.h"
using namespace std;

int main() {
   Usage masterClass(cin);
   // pass the standard input stream into the constructor
   masterClass.printStats();
   return 0;
}
