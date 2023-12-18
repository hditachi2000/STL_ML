// Simple Hash Table for Arduino with DJB2 hash function
#include "STL.h"


const int TABLE_SIZE = 10;

struct Node {
  int value;
  Node* next;  // Pointer to the next element in case of collision
};

class unordered_set {
private:
  Node* table[TABLE_SIZE];

  unsigned long djb2Hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
  }

  int hashFunction(int key) {
    return djb2Hash(reinterpret_cast<const char*>(&key)) % TABLE_SIZE;
  }

public:
  unordered_set() {
    // Initialize the table
    for (int i = 0; i < TABLE_SIZE; ++i) {
      table[i] = nullptr;
    }
  }

  ~unordered_set() {
    // Free memory allocated for linked lists
    for (int i = 0; i < TABLE_SIZE; ++i) {
      Node* current = table[i];
      while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
      }
    }
  }

  void insert(int value) {
    int index = hashFunction(value);

    // Check if the value already exists
    Node* current = table[index];
    while (current != nullptr) {
      if (current->value == value) {
        return; // Value already exists, do nothing
      }
      current = current->next;
    }

    // Value not found, create a new node
    Node* newNode = new Node{value, nullptr};
    newNode->next = table[index];
    table[index] = newNode;
  }

  bool contains(int value) {
    int index = hashFunction(value);

    // Search for the value in the linked list at the specified index
    Node* current = table[index];
    while (current != nullptr) {
      if (current->value == value) {
        return true; // Value found
      }
      current = current->next;
    }

    // Value not found
    return false;
  }

  void remove(int value) {
    int index = hashFunction(value);

    Node* current = table[index];
    Node* prev = nullptr;

    // Search for the value in the linked list at the specified index
    while (current != nullptr) {
      if (current->value == value) {
        // Value found, remove the node from the linked list
        if (prev != nullptr) {
          prev->next = current->next;
        } else {
          table[index] = current->next;
        }

        // Free memory for the removed node
        delete current;
        return;
      }

      prev = current;
      current = current->next;
    }
  }
};
//---------------------------------- Vector ---------------------------------
class SimpleVector {
private:
  int* array;
  int size;
  int capacity;

public:
  SimpleVector() {
    capacity = INITIAL_CAPACITY;
    array = new int[capacity];
    size = 0;
  }

  ~SimpleVector() {
    delete[] array;
  }

  void push_back(int value) {
    if (size == capacity) {
      // Double the capacity if the vector is full
      resize(2 * capacity);
    }

    array[size++] = value;
  }

  void resize(int newCapacity) {
    int* newArray = new int[newCapacity];
    for (int i = 0; i < size; ++i) {
      newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
  }

  void insert(int index, int value) {
    if (index >= 0 && index <= size) {
      if (size == capacity) {
        // Double the capacity if the vector is full
        resize(2 * capacity);
      }

      for (int i = size; i > index; --i) {
        array[i] = array[i - 1];
      }

      array[index] = value;
      ++size;
    } else {
      // Handle invalid index
      Serial.println("Invalid index for insertion.");
    }
  }

  void erase(int index) {
    if (index >= 0 && index < size) {
      for (int i = index; i < size - 1; ++i) {
        array[i] = array[i + 1];
      }
      --size;
    } else {
      // Handle invalid index
      Serial.println("Invalid index for erasure.");
    }
  }

  int at(int index) {
    if (index >= 0 && index < size) {
      return array[index];
    } else {
      // Handle out-of-bounds access
      Serial.println("Index out of bounds.");
      return -1;
    }
  }

  int getSize() {
    return size;
  }

  bool empty() {
    return size == 0;
  }
};
//--------------------------------unordered_map-------------------------------
const int TABLE_SIZE = 10;

struct KeyValue {
  int key;
  int value;
  KeyValue* next;  // Pointer to the next element in case of collision
};

class unordered_map {
private:
  KeyValue* table[TABLE_SIZE];

  unsigned long djb2Hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
  }

  int hashFunction(int key) {
    return djb2Hash(reinterpret_cast<const char*>(&key)) % TABLE_SIZE;
  }

public:
  unordered_map() {
    // Initialize the table
    for (int i = 0; i < TABLE_SIZE; ++i) {
      table[i] = nullptr;
    }
  }

  ~unordered_map() {
    // Free memory allocated for linked lists
    for (int i = 0; i < TABLE_SIZE; ++i) {
      KeyValue* current = table[i];
      while (current != nullptr) {
        KeyValue* next = current->next;
        delete current;
        current = next;
      }
    }
  }

  void insert(int key, int value) {
    int index = hashFunction(key);

    // Check if the key already exists, update if it does
    KeyValue* current = table[index];
    while (current != nullptr) {
      if (current->key == key) {
        current->value = value;
        return;
      }
      current = current->next;
    }

    // Key not found, create a new key-value pair
    KeyValue* newNode = new KeyValue{key, value, nullptr};
    newNode->next = table[index];
    table[index] = newNode;
  }

  int get(int key) {
    int index = hashFunction(key);

    // Search for the key in the linked list at the specified index
    KeyValue* current = table[index];
    while (current != nullptr) {
      if (current->key == key) {
        return current->value;
      }
      current = current->next;
    }

    // Key not found
    return -1; // You might want to consider using a different value for indicating "not found"
  }

  void remove(int key) {
    int index = hashFunction(key);

    KeyValue* current = table[index];
    KeyValue* prev = nullptr;

    // Search for the key in the linked list at the specified index
    while (current != nullptr) {
      if (current->key == key) {
        // Key found, remove the node from the linked list
        if (prev != nullptr) {
          prev->next = current->next;
        } else {
          table[index] = current->next;
        }

        // Free memory for the removed node
        delete current;
        return;
      }

      prev = current;
      current = current->next;
    }
  }
};

//---------------------------------MAP + SET ---------------------------
const int TABLE_SIZE = 10;

template <typename T>
struct Node {
  int key;
  T value;
  Node* next;  // Pointer to the next element in case of collision
};

template <typename T>
class SimpleHashContainer {
protected:
  Node<T>* table[TABLE_SIZE];

  unsigned long djb2Hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
  }

  int hashFunction(int key) {
    return djb2Hash(reinterpret_cast<const char*>(&key)) % TABLE_SIZE;
  }

public:
  SimpleHashContainer() {
    // Initialize the table
    for (int i = 0; i < TABLE_SIZE; ++i) {
      table[i] = nullptr;
    }
  }

  ~SimpleHashContainer() {
    // Free memory allocated for linked lists
    for (int i = 0; i < TABLE_SIZE; ++i) {
      Node<T>* current = table[i];
      while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
      }
    }
  }

  void insert(int key, T value) {
    int index = hashFunction(key);

    // Check if the key already exists, update if it does
    Node<T>* current = table[index];
    while (current != nullptr) {
      if (current->key == key) {
        current->value = value;
        return;
      }
      current = current->next;
    }

    // Key not found, create a new key-value pair
    Node<T>* newNode = new Node<T>{key, value, nullptr};
    newNode->next = table[index];
    table[index] = newNode;
  }

  bool contains(int key) {
    int index = hashFunction(key);

    // Search for the key in the linked list at the specified index
    Node<T>* current = table[index];
    while (current != nullptr) {
      if (current->key == key) {
        return true; // Key found
      }
      current = current->next;
    }

    // Key not found
    return false;
  }

  void remove(int key) {
    int index = hashFunction(key);

    Node<T>* current = table[index];
    Node<T>* prev = nullptr;

    // Search for the key in the linked list at the specified index
    while (current != nullptr) {
      if (current->key == key) {
        // Key found, remove the node from the linked list
        if (prev != nullptr) {
          prev->next = current->next;
        } else {
          table[index] = current->next;
        }

        // Free memory for the removed node
        delete current;
        return;
      }

      prev = current;
      current = current->next;
    }
  }
};

template <typename T>
class unordered_set : public SimpleHashContainer<T> {
public:
  // Additional methods specific to unordered_set, if needed
};

template <typename T>
class unordered_map : public SimpleHashContainer<T> {
public:
  T get(int key) {
    int index = this->hashFunction(key);

    // Search for the key in the linked list at the specified index
    Node<T>* current = this->table[index];
    while (current != nullptr) {
      if (current->key == key) {
        return current->value;
      }
      current = current->next;
    }

    // Key not found
    return T(); // Default value for the type T; adjust as needed
  }
};
