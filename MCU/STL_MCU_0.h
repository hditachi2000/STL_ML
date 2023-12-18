#ifndef STL_MCU_H
#define STL_MCU_H

#include <cstdint>
  /**
   * @brief kiến trúc cặp pair dùng cho unordered_map
   * @param key biến uint8_t có khoảng biểu diễn 1-255 . Giá trị 0 là giá trị mặc định được khởi tạo 
   * @param value biến uint8_t có khoảng biểu diễn 0-255 . 
   */
struct pair {
    uint8_t key;
    uint8_t value;
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

/** @brief Lớp hạt nhân chứa cấu trúc băm, dùng chung cho unordered_set và unordered_map */
class hashKernel {
protected:
    uint16_t djb2Hash(uint8_t key) const {
        uint16_t hash = 5381;

        while (key) {
            uint8_t c = key % 10; // Lấy chữ số cuối
            key /= 10;            // xóa chữ số cuối
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }
public:
    /**
     * @brief : tạo index cho (key,value) trong map từ key bằng hàm băm
     *
     * @return : trả về index trong map của cặp (key,value)
    */
    uint8_t hashFunction(uint8_t TABLE_SIZE,uint8_t key) const {
        return djb2Hash(key) % TABLE_SIZE;
    }
    /**
     * @brief : trượt tuyến tính trong map khi bảng băm xảy ra va chạm . 
     * @pre : Tối ưu hóa làm đầy map
     *
     * @return : trả về index tiếp theo trong map của cặp (key,value) khi xảy ra va chạm 
    */
    uint8_t linearProbe(uint8_t TABLE_SIZE,uint8_t index, uint8_t attempt) const {
        // trượt/ dò tuyến tính
        return (index + attempt) % TABLE_SIZE;
    }
};

/**
 * @brief kiến trúc unordered_map giả lập cho MCU
 * @pre . khởi tạo kích thước của map dựa trên số phần tử dự tính.
 */
template <uint8_t TABLE_SIZE>
class unordered_map : public hashKernel {
private:
  pair table[TABLE_SIZE];
  uint8_t size;
public:
    // using hashKernel<TABLE_SIZE>::hashFunction;
    // using hashKernel<TABLE_SIZE>::linearProbe;
    unordered_map() {
        // Khởi tạo map
        for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
            table[i].key = 0; // 0 là giá trị key mặc định, đại diện cho vị trí trống trong map 
        }
        size = 0;
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
    bool insert(uint8_t key, int16_t value) {
        uint8_t index = hashFunction(TABLE_SIZE,key);
        uint8_t attempt = 0;

        // Trùng index - vị trí trong map 
        // Tìm kiếm key đã tồn tại và trùng với key mới đang được thêm vào . Vòng lặp dừng lại khi gặp key trùng lặp 
        while (table[index].key != 0 && table[index].key != key) {
            // Trượt tuyến tính tìm ô trống 
            index = linearProbe(TABLE_SIZE,index, ++attempt); 
            if(attempt >= TABLE_SIZE - 1) return false;         // bảng đã đầy và không có key trùng lặp 
                                                               // sửa lỗi hàm sẽ rơi vào vòng lặp vô hạn. 
        } // sau vòng while này, tìm được vị trí trống để chèn cặp (key,value)
        // chèn cặp (key,value) vào ô trống tìm được 
        table[index].key = key;
        table[index].value = value;
        size++;
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
        uint8_t index = hashFunction(TABLE_SIZE,p.first());
        uint8_t attempt = 0;
        // Tìm kiếm key đã tồn tại và trùng với key mới đang được thêm vào . Vòng lặp dừng lại khi gặp key trùng lặp 
        while (table[index].key != 0 && table[index].key != key) {
            // Trượt tuyến tính tìm ô trong bảng hash chứa key đang tồn tại 
            index = linearProbe(TABLE_SIZE,index, ++attempt); 
            // return true;
            if(attempt >= TABLE_SIZE - 1) return false;         // bảng đã đầy và không có key trùng lặp  
                                                               // sửa lỗi hàm sẽ rơi vào vòng lặp vô hạn. 
        }
        table[index].key = p.first();
        table[index].value =p.second();
        size++;
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
    bool get(uint8_t key, int16_t& value) {
        uint8_t index = hashFunction(TABLE_SIZE,key);
        uint8_t attempt = 0;

        // tìm kiếm, trượt tuyến tính nếu tìm thấy va chạm 
        while (table[index].key != 0) {
            if (table[index].key == key) {
                value = table[index].value;
                return true; // tìm thấy key
            }
            // tìm thấy va chạm, trượt tuyến tính 
            index = linearProbe(TABLE_SIZE,index, ++attempt);
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
        uint8_t index = hashFunction(TABLE_SIZE,key);
        uint8_t attempt = 0;

        // tìm khóa , trượt tuyến tính cho các trường hợp va chạm 
        while (table[index].key != 0) {
            if (table[index].key == key) {
                return table[index].value; // Key found
            }
            // Va chạm, dò tuyến tính
            index = linearProbe(TABLE_SIZE,index, ++attempt);
        }

        return 111; // giá trị báo lỗi
    }
    /**
     * @brief : xóa 1 cặp (key,value) bằng key
     *
     * @param key : khóa dùng để xóa 
    */
    void remove(uint8_t key) {
        uint8_t index = hashFunction(TABLE_SIZE,key);
        uint8_t attempt = 0;
        // dò tuyến tính 
        while (table[index].key != 0) {
            if (table[index].key == key) {  // tìm thấy khóa
                table[index].key = 0; 
                size--;
                return; 
            }
            // cặp (key,value) này xảy ra va chạm khi được thêm vào, sử dụng dò tuyến tính 
            index = linearProbe(TABLE_SIZE,index, ++attempt);
        }
    }
    /**
     * @brief : lấy về số cặp (key,value) trong map
     *
     * @return : trả về kích thước của map (uint8_t)
    */
    uint8_t Size() {
        return size;
    }
    /**
     * @brief : kiểm tra xem map đã đầy hay chưa
     *
     * @return : true nếu map đã đầy
    */
    bool isFull(){
      if(size>=TABLE_SIZE) return true;
      return false;
    }
    /**
     * @brief : kiểm tra xem map rỗng hay không
     *
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
      for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
          table[i].key = 0;
      }
      size = 0;
    }

};

template <uint8_t TABLE_SIZE>
/**
 * @brief : Kiến trúc unordered_set giả lập cho MCU 
 * @pre   : Khởi tạo với số phần tử dự tính 
*/
class unordered_set : public hashKernel {
  uint8_t table[TABLE_SIZE];
  uint8_t size;
public:
  // using hashKernel<TABLE_SIZE>::hashFunction;
  // using hashKernel<TABLE_SIZE>::linearProbe;
    unordered_set() {
        // Initialize the table
        for (uint8_t i = 0; i < TABLE_SIZE; ++i) {
            table[i] = false;
        }
        size = 0;
    }
    /**
     * @brief       : Thêm 1 phần tử vào set
     * @pre         : Các phần tử được xếp vào set cho tới khi set đầy
     * @param value : phần tử thêm vào, phải được chuẩn hóa 1-255 trước khi thêm vào set
     * @return      : true nếu thêm vào thành công , false khi set đã đầy 
    */
    bool insert(uint8_t value) {
        if (size == TABLE_SIZE) {    // set đầy
            return false;
        }
        uint8_t attempt = 0;
        uint8_t index;
        do {
            index = linearProbe(TABLE_SIZE,value, attempt); 
            attempt++;
        } while (table[index]);  // va chạm

        // Tìm thấy ô chèn 
        size++;
        table[index] = true;
        return true;
    }

    /**
     * @brief      : Tìm kiếm phần tử trong set
     * @param value : Giá trị được tìm kiếm (uint8_t)
     * @return      : True nếu phần tử có trong set
    */
    bool contains(uint8_t value) {
        uint8_t attempt = 0;
        uint8_t index;

        do {
            index = linearProbe(TABLE_SIZE,value, attempt);
            if (table[index] && value == index) {
                return true;
            }
            attempt++;
        } while (table[index]);

        return false;
    }
    /**
     * @brief       : xóa 1 phần tử khỏi set
     * @param value : Phần tử xóa (uint8_t)
    */
    void remove(uint8_t value) {
        uint8_t attempt = 0;
        uint8_t index;
        do {
            index = linearProbe(TABLE_SIZE,value, attempt);
            if (table[index] && value == index) {
                size--;
                table[index] = false;
                return;
            }
            attempt++;
        } while (table[index]);
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
          table[i] = false;
      }
      size = 0;
    }
};

#endif // STL_MCU_H