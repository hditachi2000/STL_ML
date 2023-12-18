#ifndef STL_NonPointer_H
#define STL_NonPointer_H

#include <stdint.h>

const int TABLE_SIZE = 100; // Adjust the size as needed

class unordered_set {
private:
  bool table[TABLE_SIZE];
  uint16_t size;

  unsigned long djb2Hash(uint16_t key);

  uint16_t hashFunction(uint16_t key);

public:
  unordered_set();

  void insert(uint16_t value);

  bool contains(uint16_t value);

  void remove(uint16_t value);
  uint16_t Size();
};



#endif