#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector> //guide permits vector<T>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  int m_;
  PComparator c_;
  std::vector<T> data_;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  m_ = m;
  c_ = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty()const{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size()const{
  return data_.size();
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap Underflow, no top element");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_.front();

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap Underflow, no element to pop");

  }

  data_[0] = data_.back();
  data_.pop_back();
  size_t top = 0;
  //swtiches multiple times
  while(true){
    //check if there is no children
    
    size_t newt = top;

    //1 switch
    for(int i=1; i<=m_; ++i){
      //find node that needs to be at root
      size_t walk = m_ * top + i;
      if(walk<data_.size()){
        if(c_(data_[walk], data_[newt])){
          newt = walk;
        }
      }
    }
    if(newt == top){
      break;
    }
    std::swap(data_[top], data_[newt]);
    top = newt;
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  data_.push_back(item);
  int sze = data_.size()-1;

  while(sze > 0 ){
    int p = (sze - 1)/m_;
    if(c_(data_[sze], data_[p])){
      std::swap(data_[sze], data_[p]);
      sze = p;
    }
    else{
      break;
    }
  }
  return;
}

#endif

