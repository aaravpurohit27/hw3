#include "heap.h"
#include <iostream>
#include <string>

int main(){
  try{
    Heap<int> mHeap(2);
    mHeap.push(12);
    mHeap.push(3);
    mHeap.push(14);
    mHeap.push(1);

    std::cout<<"Top of heap " << mHeap.top()<<std::endl;
    mHeap.pop();
    std::cout<<"Top of heap " << mHeap.top()<<std::endl;
  }
  catch(std::exception& e){
    e.what();
  }
  return 0;
}