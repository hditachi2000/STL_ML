#ifndef STL_MCU_H
#define STL_MCU_H

#include "HashKernel_optimazed.h"

HashKernel_optimazer haser;

  /**
   * @brief : kiến trúc cặp pair dùng cho unordered_map
   * @param key   : biến uint8_t có khoảng biểu diễn 1-255 . Giá trị 0 là giá trị mặc định được khởi tạo 
   * @param value : biến uint8_t có khoảng biểu diễn 0-255 . 
   */
struct pair {
    uint8_t key;
    uint8_t value;
    // Constructor mặc định, sử dụng trong quá trình khởi tạo map
    pair(){};
    // Constructor sử dụng cho khởi tạo biến pair tùy chỉnh (vd: pair p(2,3))
    pair(uint8_t key,uint8_t value){
      this->key = key;
      this->value = value;
    }
    /**
      * @brief trả về phần tử thứ nhất(key) trong cặp pair 
      */
    uint8_t first() const {
        return key;
    }
    /**
      * @brief trả về phần tử thứ hai(value) trong cặp pair 
      */
    uint8_t second() const {
        return value;
    }
};
// ----------------------------------------- HashKernel --------------------------------------------

/** @brief Lớp hạt nhân chứa cấu trúc băm, dùng chung cho unordered_set và unordered_map */
class hashKernel {
protected:

    uint16_t djb2Hash(uint8_t key,uint16_t hash) const {
        return ((hash << 5) + hash) + key;
    }
public:
    /**
     * @brief : tạo index cho (key,value) trong map từ key bằng hàm băm
     *
     * @return : trả về index trong map của cặp (key,value)
    */
    uint8_t hashFunction(uint8_t TABLE_SIZE,uint8_t key,uint16_t hash) const {
        return djb2Hash(key,hash) % TABLE_SIZE;
    }
    /**
     * @brief : trượt tuyến tính trong map khi bảng băm xảy ra va chạm . 
     * @pre : Tối ưu hóa làm đầy map
     *
     * @return : trả về index tiếp theo trong map của cặp (key,value) khi xảy ra va chạm 
    */
    uint8_t linearProbe(uint8_t TABLE_SIZE,uint8_t index,uint8_t attempt) const {
        // trượt/ dò tuyến tính
        return (index + attempt) % TABLE_SIZE;
    }
};

// --------------------------------------Unordered_Map -------------------------------------

/**
 * @brief kiến trúc unordered_map giả lập cho MCU
 * @pre . khởi tạo kích thước của map dựa trên số phần tử dự tính.
 */
template <uint8_t TABLE_SIZE>
class unordered_map : public hashKernel {
private:
  pair table[TABLE_SIZE];
  uint8_t size;
  uint8_t attempt;  // bước dịch tuyến tính
  uint16_t hasher;  // trị số hash dành cho hàm băm 
public:
    // using hashKernel<TABLE_SIZE>::hashFunction;
    // using hashKernel<TABLE_SIZE>::linearProbe;
    unordered_map() {
        // Khởi tạo map
        for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
            table[i].key = 0;                       // 0 là giá trị key mặc định, đại diện cho vị trí trống trong map  
            table[i].value = 0;                     // Khoảng giá trị : - Key 1-255 (Map có tối đa 255 cặp phần tử)
        }                                           //                  - Value 0-255 
        size = 0;                                    
        attempt = haser.calStep(TABLE_SIZE);
        hasher = haser.bestHasher16[TABLE_SIZE-1];
    }
    /**
     * @brief : Thêm 1 cặp (key,value) mới vào map 
     *
     * @pre - Nếu trùng index (vị trí trong map) 
              + Nếu key giống, cập nhật giá trị value mới.
              + Nếu key khác : thăm dò tuyến tính cho đến khi tìm thấy một ô còn trống trong map.
            - Nếu bảng hash đầy và không có key trùng lặp, hàm không chèn cặp (key,value) mới 
     * @param key : biến uint8_t unique , Phải được chuẩn hóa về 1-255 trước khi thêm vào
     * @param value : biến uint8_t non unique , Phải được chuẩn hóa về 0-255 trước khi thêm vào
     *
     * @return - true nếu chèn thành công, false nếu chèn thất bại 
     */
    bool insert(uint8_t key, int8_t value) {
         if(key == 0) return false;
        uint8_t index = hashFunction(TABLE_SIZE,key,hasher);
        uint8_t collision = 0;
        // Trùng index - vị trí trong map 
        // Tìm kiếm key đã tồn tại và trùng với key mới đang được thêm vào . Vòng lặp dừng lại khi gặp key trùng lặp 
        while (table[index].key != 0 && table[index].key != key) {
            if(collision >= TABLE_SIZE - 1) return false; 
            index = linearProbe(TABLE_SIZE,index, attempt); 
            collision++;
            if(table[index].key == key){                // trượt và tìm thấy ô trùng key
                table[index].value = value;
                return true;       
            }
        } // sau vòng while này, tìm được vị trí trống để chèn cặp (key,value)

        if(table[index].key != key){            // Vị trí tìm được là ô mới - thêm phần tử mới
                table[index].key = key;
                size++;     
            }
        table[index].value = value;             // vị trí tìm được là ô trùng key - cập nhật value
        return true;
    }
    /**
     * @brief : Thêm 1 pair(key,value) vào map  
     *
     * @pre - Nếu trùng index (vị trí trong map) 
              + Nếu key giống, cập nhật giá trị value mới.
              + Nếu key khác : thăm dò tuyến tính cho đến khi tìm thấy một ô còn trống trong map.
            - Nếu bảng hash đầy và không có key trùng lặp, hàm không chèn cặp (key,value) mới 
     * @param pair : pair với cặp giá trị (uint8_t,uint8_t)
     * @return - true nếu chèn thành công, false nếu chèn thất bại 
     */
    bool insert(pair p) {
        if(p.key <= 0 || p.key >255 | p.value <= 0 || p.value > 255) return false;
        uint8_t index = hashFunction(TABLE_SIZE,p.first(),hasher);
        uint8_t collision = 0;
        // Tìm kiếm key đã tồn tại và trùng với key mới đang được thêm vào . Vòng lặp dừng lại khi gặp key trùng lặp 
        while (table[index].key != 0 && table[index].key != p.first()) {
            if(collision>= TABLE_SIZE - 1) return false;                                                                    
            // Trượt tuyến tính tìm ô trong bảng hash chứa key đang tồn tại 
            index = linearProbe(TABLE_SIZE,index, attempt); 
            if(table[index].key == p.first())  {
                table[index].value =p.second();
                return true;
            }
            collision++;
        }
        if(table[index].key != p.first())
        {
            size++;
            table[index].key = p.first();
        }
        table[index].value =p.second();
        return true;
    }

    /**
     * @brief : lấy về giá trị của value bằng khóa 
     *
     * @param key   : khóa dùng để tìm kiếm
     * @param value : biến tham chiếu được truyền vào giá trị của value
     *
     * @return - true nếu tìm kiếm thành công, false nếu không tìm được value với key truyền vào 
    */
    bool getValue(uint8_t key, int16_t& value) {
        if(key <=0 || key> 255) return false;
        uint8_t index = hashFunction(TABLE_SIZE,key,hasher);
        // tìm kiếm, trượt tuyến tính nếu tìm thấy va chạm 
        while (table[index].key != 0) {
            if (table[index].key == key) {
                value = table[index].value;
                return true; // tìm thấy key
            }
            // tìm thấy va chạm, trượt tuyến tính 
            index = linearProbe(TABLE_SIZE,index, attempt);
        }
        // không tìm thấy key
        return false;
    }
    /**
     * @brief : lấy về giá trị của value bằng khóa 
     *
     * @param key : khóa dùng để tìm kiếm
     *
     * @return - true nếu tìm kiếm thành công, false nếu không tìm được value với key truyền vào 
               - Giá trị 111 là giá trị báo lỗi , xem xét kết hợp với hàm getValue() khi giá trị này xuất hiện 
    */
    uint8_t getValue(uint8_t key) {
        if(key <= 0 || key > 255) return 0;
        uint8_t index = hashFunction(TABLE_SIZE,key,hasher);
        // uint8_t attempt = 0;

        // tìm khóa , trượt tuyến tính cho các trường hợp va chạm 
        while (table[index].key != 0) {
            if (table[index].key == key) {
                return table[index].value; // Key found
            }
            // Va chạm, dò tuyến tính
            index = linearProbe(TABLE_SIZE,index, attempt);
        }

        return 0; // giá trị báo lỗi
    }
    /**
     * @brief : xóa 1 cặp (key,value) bằng key
     * @param key : khóa dùng để xóa 
    */
    void remove(uint8_t key) {
        uint8_t index = hashFunction(TABLE_SIZE,key,hasher);
        // dò tuyến tính 
        while (table[index].key != 0) {
            if (table[index].key == key) {  // tìm thấy khóa
                table[index].key = 0; 
                size--;
                return; 
            }
            // cặp (key,value) này xảy ra va chạm khi được thêm vào, sử dụng dò tuyến tính 
            index = linearProbe(TABLE_SIZE,index, attempt);
        }
    }
    /**
     * @brief : lấy về số cặp (key,value) trong map
     * @return : trả về kích thước của map (uint8_t)
    */
    uint8_t Size() {
        return size;
    }
    /**
     * @brief : kiểm tra xem map đã đầy hay chưa
     * @return : true nếu map đã đầy
    */
    bool isFull(){
      if(size>=TABLE_SIZE) return true;
      return false;
    }
    /**
     * @brief : kiểm tra xem map rỗng hay không
     * @return : true nếu map không chứa phần tử nào
    */
    bool isEmpty(){
      if(size == 0) return true;
      return false;
    }
    /**
     * @brief : xóa tất cả phần tử trong map
    */
    void clear() {
      for (uint8_t i = 0; i < TABLE_SIZE; i++) {
          table[i].key = 0;
      }
      size = 0;
    }

};

// -------------------------------------------Unordered_set -----------------------------------------

template <uint8_t TABLE_SIZE> // 
/**
 * @brief : Kiến trúc unordered_set giả lập cho MCU     
 * @pre   : Khởi tạo với số phần tử dự tính 
*/
class unordered_set : public hashKernel {           // ban đầu, table có kiểu dữ liệu bool . Như vậy 1 mảng tối đa chỉ luôn chiếm 256 bit/32 byte
  uint8_t table[TABLE_SIZE];                        // Tuy nhiên, không chắc rằng VĐK đang sử dụng hỗ trợ cờ 1 bit hay không .Thông thường ,
  uint8_t size;                                     // 1 đơn vị bộ nhớ xử lý ở mức nhỏ nhất là 1 byte. 
  uint16_t hasher;
  uint8_t attempt;
public:
  // using hashKernel<TABLE_SIZE>::hashFunction;
  // using hashKernel<TABLE_SIZE>::linearProbe;
    unordered_set() {
        // Initialize the table
        for (uint8_t i = 0; i < TABLE_SIZE; ++i) {          // NOTE : Khoảng giá trị được thêm vào set : 1-255
            table[i] = 0;                                   //        Set chứa tối đa 256 phần tử 
        }
        size = 0;
        hasher = haser.bestHasher16[TABLE_SIZE-1];
        attempt = haser.calStep(TABLE_SIZE);
    }
    /**
     * @brief       : Thêm 1 phần tử vào set
     * @pre         : Các phần tử được xếp vào set cho tới khi set đầy
     * @param value : phần tử thêm vào, cần được chuẩn hóa 1-255 trước khi thêm vào set
     * @return      : true nếu thêm vào thành công , false khi set đã đầy 
    */
    bool insert(uint8_t value) {
        if(value <= 0 || value > 255) return false;
        if (size == TABLE_SIZE) {    // set đầy
            return false;
        }
        uint8_t collision = 0;
        uint8_t index = hashFunction(TABLE_SIZE,value,hasher);
        while (table[index]!=0){
            if(table[index] == value) return false;
            index = linearProbe(TABLE_SIZE,index, attempt); 
            collision++;
            if(collision>TABLE_SIZE) return false;
        }   // va chạm

        // Tìm thấy ô chèn 
        size++;
        table[index] = value;
        return true;
    }

    /**
     * @brief      : Tìm kiếm phần tử trong set
     * @param value : Giá trị được tìm kiếm (uint8_t)
     * @return      : True nếu phần tử có trong set
    */
    bool contains(uint8_t value) {
        if(value <= 0 || value > 255) return false;
        uint8_t index = hashFunction(TABLE_SIZE,value,hasher);
        // index có chứa value
        while (table[index] != 0) {
            if (value == table[index]) {       // ktra va chạm
                return true;
            }
            index = linearProbe(TABLE_SIZE,index, attempt); // va chạm, dịch tuyến tính
            // attempt++;
        } 
        // index trống 
        return false;
    }
    /**
     * @brief       : xóa 1 phần tử khỏi set
     * @param value : Phần tử xóa (uint8_t)
    */
    void remove(uint8_t value) {
        if(value <= 0 || value > 255) return;
        uint8_t index = hashFunction(TABLE_SIZE,value,hasher);
        while (table[index] != 0) {
            if (value == table[index]) {
                size--;
                table[index] = 0;
                return;
            }
            index = linearProbe(TABLE_SIZE,index, attempt);
        } 
    }
    /**
     * @return : trả về số phần tử đang có trong set 
    */
    uint8_t Size() const {
        return size;
    }
    /** @return :  true nếu set đầy */
    bool isFull(){
      if(size>=TABLE_SIZE) return true;
      return false;
    }
    /** @return : true nếu set đang rỗng */
    bool isEmpty(){
      if(size == 0) return true;
      return false;
    }
    /** @brief : xóa toàn bộ phần tử trong set*/
    void clear() {
      for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
          table[i] = 0;
      }
      size = 0;
    }
};

class unordered_map_set : public hashKernel{

};

/**
 * @brief : Kiến trúc unordered_set giả lập cho MCU     
 * @pre   : Sử dụng bool đánh dấu vị trí trong mảng thay cho biến giá trị thông thường 
*/
class bool_unordered_set : public hashKernel {           // ban đầu, table có kiểu dữ liệu bool . Như vậy 1 mảng tối đa chỉ luôn chiếm 256 bit/32 byte
  bool table[256];                        // Tuy nhiên, không chắc rằng VĐK đang sử dụng hỗ trợ cờ 1 bit hay không .Thông thường ,
  uint8_t size;                                     // 1 đơn vị bộ nhớ xử lý ở mức nhỏ nhất là 1 byte. 
  uint16_t hasher;
  uint8_t attempt;
public:


    bool_unordered_set() {
        // Initialize the table
        for (uint8_t i = 0; i < 256; ++i) {
            table[i] = false;
        }
        size = 0;
        hasher = haser.bestHasher16[255];
        attempt = haser.calStep(255);
    }
    /**
     * @brief       : Thêm 1 phần tử vào set
     * @pre         : Các phần tử được xếp vào set cho tới khi set đầy
     * @param value : phần tử thêm vào, cần được chuẩn hóa 1-255 trước khi thêm vào set
     * @return      : true nếu thêm vào thành công , false khi set đã đầy 
    */
    bool insert(uint8_t value) {
        if (size == 256) {    // set đầy
            return false;
        }
        uint8_t collision = 0;
        uint8_t index = hashFunction(255,value,hasher);
        while (table[index]){
            index = linearProbe(255,index, attempt); 
            collision++;
            if(collision>256) return false;
        }   // va chạm

        // Tìm thấy ô chèn 
        size++;
        table[index] = true;
        return true;// va chạm
    }


    /**
     * @brief      : Tìm kiếm phần tử trong set
     * @param value : Giá trị được tìm kiếm (uint8_t)
     * @return      : True nếu phần tử có trong set
    */
    bool contains(uint8_t value) {
        // uint8_t attempt = 0;
        uint8_t index = hashFunction(255,value,hasher);

        while (table[index]) {
            if (table[index] && value == index) {
                return true;
            }
            index = linearProbe(255,index, attempt);
        }
        return false;
    }
    /**
     * @brief       : xóa 1 phần tử khỏi set
     * @param value : Phần tử xóa (uint8_t)
    */
    void remove(uint8_t value) {
        // uint8_t attempt = 0;
        uint8_t index = hashFunction(255,value,hasher);
        while (table[index]) {
            if (table[index] && value == index) {
                size--;
                table[index] = false;
                return;
            }
            index = linearProbe(255,index, attempt);
            // attempt++;
        } 
    }
    /**
     * @return : trả về số phần tử đang có trong set 
    */
    uint8_t Size() const {
        return size;
    }
    /** @return :  true nếu set đầy */
    bool isFull(){
      if(size>=256) return true;
      return false;
    }
    /** @return : true nếu set đang rỗng */
    bool isEmpty(){
      if(size == 0) return true;
      return false;
    }
    /** @brief : xóa toàn bộ phần tử trong set*/
    void clear() {
      for (uint8_t i = 0; i <= 255; ++i) {
          table[i] = false;
      }
      size = 0;
    }
};

// ------------------------------------------- Vector ----------------------------------------

// template <typename T>
class vector {
private:
  uint8_t *array;        // Dynamic array
  uint8_t capacity;  // Capacity of the array
  uint8_t size;      // Number of elements in the array

public:
  // Constructor
  vector(uint8_t initialCapacity = 10) {
    capacity = initialCapacity;
    size = 0;
    array = new uint8_t[capacity];
  }

  // Destructor
  ~vector() {
    delete[] array;
  }

  // Function to add an element to the vector
  void push_back(const uint8_t &element) {
    if (size == capacity) {
      // If the array is full, double the capacity
      capacity *= 2;
      uint8_t *tempArray = new uint8_t[capacity];
      for (uint8_t i = 0; i < size; ++i) {
        tempArray[i] = array[i];
      }
      delete[] array;
      array = tempArray;
    }

    // Add the element to the end of the array
    array[size++] = element;
  }

  // Function to get the element at a specific index
  uint8_t& operator[](uint8_t index) {
    // TODO: Add bounds checking for index
    return array[index];
  }

  // Function to get the number of elements in the vector
  uint8_t getSize() const {
    // TODO: 
    return size;
  }

  // Function to get the capacity of the vector
  uint8_t getCapacity() const {
    return capacity;
  }
};



#endif // STL_MCU_H