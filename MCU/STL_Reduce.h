#ifndef STL_Reduce_H
#define STL_Reduce_H

#include <cstdint>

const uint16_t TABLE_SIZE = 100; // Adjust the size as needed

struct KeyValue {
  uint8_t key;
  int16_t value;
};

class hashKernel {
protected:
  uint16_t size;

  uint16_t djb2Hash(uint16_t key) {
    uint16_t hash = 5381;

    while (key) {
      uint8_t c = key % 10; // Get the last digit
      key /= 10;           // Remove the last digit
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
  }

  uint16_t hashFunction(uint16_t key) {
    return djb2Hash(key) % TABLE_SIZE;
  }

public:
  uint16_t Size() {
    return size;
  }
};

class UnorderedSet : public hashKernel {
private:
  bool table[TABLE_SIZE];

public:
  UnorderedSet() {
    // Initialize the table
    for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
      table[i] = false;
    }
  }

  void insert(uint16_t value) {
    uint16_t index = hashFunction(value);
    size++;
    table[index] = true;
  }

  bool contains(uint16_t value) {
    uint16_t index = hashFunction(value);
    return table[index];
  }

  void remove(uint16_t value) {
    uint16_t index = hashFunction(value);
    size--;
    table[index] = false;
  }
};

class UnorderedMap : public hashKernel {
private:
  KeyValue table[TABLE_SIZE];

public:
  UnorderedMap() {
    // Initialize the table
    for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
      table[i].key = -1; // Use a sentinel value to indicate an empty slot
    }
    size = 0;
  }

  void insert(uint8_t key, int16_t value) {
    uint8_t index = hashFunction(key);

    // Check if the key already exists, update value if it does
    if (table[index].key == key) {
      table[index].value = value;
    } else {
      // Key not found, create a new (key, value) pair
      table[index].key = key;
      table[index].value = value;
      size++;
    }
  }

  bool get(uint8_t key, int16_t& value) {
    uint8_t index = hashFunction(key);
    if (table[index].key == key) {
      value = table[index].value;
      return true;
    } else {
      return false; // Key not found
    }
  }

  void remove(uint8_t key) {
    uint8_t index = hashFunction(key);
    table[index].key = -1; // Use a sentinel value to indicate an empty slot
    size--;
  }
};

#endif // HASH_CONTAINER_H
