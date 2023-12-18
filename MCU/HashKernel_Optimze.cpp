#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <random>

#include "HashKernel_optimazed.h"

using namespace std;

HashKernel_optimazer Haser;

  /* Hàm hash dưới đây gồm 2 công thức , tuy nhiên công thức dưới đơn giản hơn và
    ánh xạ được tới nhiều vị trí hơn so với cùng 1 số lượng đầu vào : Công thức bên trên chỉ ánh xạ 
    tới tối đa 10 vị trí : [0->9] + hash*33 
  */
  uint16_t djb2Hash(uint8_t key,uint16_t hash = 5381) {
        // while (key) {
        //     uint8_t c = key % 10; // Lấy chữ số cuối
        //     key /= 10;            // xóa chữ số cuối
        //     hash = ((hash << 5) + hash) + c; // hash * 33 + c
        // }
        hash = ((hash << 5) + hash) + key; // hash * 33 + c
        return hash;
    }
    uint8_t hashFunction(uint8_t TABLE_SIZE,uint8_t key,uint16_t hash = 5381) {
        return djb2Hash(key,hash) % TABLE_SIZE;
    }
    uint8_t linearProbe(uint8_t TABLE_SIZE,uint8_t index, uint8_t attempt) {
        // trượt/ dò tuyến tính
        return (index + attempt) % TABLE_SIZE;
    }

// tim uoc chung lon nhat
uint8_t gcd(uint8_t a, uint8_t b) {
    while (b != 0) {
        uint8_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint8_t HashKernel_optimazed::calStep(uint8_t a) {
    if(a<=10) return 1;
    if(a>10 && a<=20) {
      if(a==14 || a==18) return 5;
      return a/2 + a%2 -1;
      
    }
    uint8_t b = a /10 - 1;      // công thức bước dịch chuẩn cho đa số trường hợp, để tối giản phép tính trong quá trình trượt tuyến tính,step nhỏ  
                            // hơn TABLE_SIZE ít nhất 10 lần

    // NOTE : điều kiện bước dịch để quá trình trượt tuyến tính không rơi vào vòng lặp vô hạn : 
    //        - bước nhảy ko là ước của 10 
    //        - ko có ước chung với TABLE_SIZE
    while (b % 10 == 0 || gcd(a, b) > 1) {
        b = b - 1;
    }
    return b;
}


uint8_t main() {
  // hashKernel hasher
  bool breakFlag = false;
  uint8_t total = 0;
  uint8_t totalbreak = 0;

  for(uint8_t TABLE_SIZE = 228; TABLE_SIZE <=255;TABLE_SIZE++){
    uint16_t hash ;
    uint16_t hashMin = 0;
    uint8_t crashMin = 9999;
    uint8_t step = TABLE_SIZE/10-1;

    // NOTE: nếu TABLE_SIZE là lẻ , step là chẵn và ngược lại 
    step = Haser.calStep(TABLE_SIZE);
    unordered_set<int> set;   // NOTE: 

    for(hash = 1;hash<=65534;hash++){
      // cout << "new loop" << endl;
      uint8_t collisions[TABLE_SIZE] = {0};
      uint8_t crashCounter = 0;
      while(set.size() <TABLE_SIZE) {
        uint8_t key;
        do{
          key = rand()%(255)+1;
          // cout << "key: " << key << endl;
        }while(set.find(key)!=set.end());
        // cout << " key found" << endl;
        set.insert(key);
        uint8_t index = hashFunction(TABLE_SIZE, key,step);
        uint8_t attempt = 0;

        while (collisions[index] != 0) {
          index = linearProbe(TABLE_SIZE, index, step);      // công thức tính bước dịch tuyến tính : = TABLE_SIZE/10 - 1
          // cout << "index: " << index << endl;
          // cout << " here1" << endl; 
          attempt ++;
          if(attempt > 254){
            cout << "break at table_size: " << TABLE_SIZE << endl;
            breakFlag = true;
            totalbreak++;
            break;
          }
        }
        collisions[index] = 1;
        if(breakFlag){
          break;
        } 
        crashCounter += attempt;
        // count++;
      }
      // cout <<"Tong so va cham : " << crashCounter << endl;
      if(crashCounter < crashMin){
        hashMin = hash;
        crashMin = crashCounter;
      }
      set.clear();
    }
    if(breakFlag){
      breakFlag = false;
      continue;
    }else{
      // cout << "TABLE_SIZE " << TABLE_SIZE <<" - ";
      // cout << "Best hasher: " << hashMin << " - ";
      // cout << "So va cham: " << crashMin << endl;
      total += crashMin;
      cout << hashMin <<",";
    }
  }
  cout << endl;
  cout <<"Total crash: " << total << endl;
  cout <<" Total break: " << totalbreak << endl;
}
