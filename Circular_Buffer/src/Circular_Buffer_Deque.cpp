/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 *
 * @brief Using Dequeue of STL to implement Circular Buffer of fixes size.
 * When the buffer is full the oldest element is overwritten. 
 *
 */
#include <deque>
#include <iostream>

template <typename T>
class CircularBufferDeque {
 public:
  /**
   * @brief Initializing the size of the circular buffer
   *
   * @param[in] x size of circular buffer to be set
   */
  CircularBufferDeque(int x) : size_(x){};
  /**
   * @brief Add an element to the buffer. If the Buffer is full then remove the
   * oldest element and add the new one.
   *
   * @param[in] var element to add in buffer
   */
  void PutC(const T var);
  /**
   * @brief Get the most oldest element added in buffer and remove it from
   * buffer
   *
   * @return  *T: pointer to oldest_value if exists.
   * @return nullptr: if buffer is empty
   */
  T* GetC();

 private:
  /**
   * @brief class variable to store size of circular buffer
   *
   */
  int size_;
  /**
   * @brief dequeue to act as circular buffer
   *
   */
  std::deque<T> cq_;
  /**
   * @brief Keeps tracks of the oldest values in circular buffer. 
   * 
   */
  T oldest_value{};

};

template <typename T>
void CircularBufferDeque<T>::PutC(const T var) {
  if (cq_.size() == size_) {
    cq_.pop_front();
  }
  cq_.push_back(var);
}

template <typename T>
T* CircularBufferDeque<T>::GetC() {
  if (cq_.size() != 0) {
    oldest_value = cq_.front();
    cq_.pop_front();
    return &oldest_value;
  } else {
    return nullptr;
  }
}
/**
 * @brief Helper function to print value depending upon if pointer is null or
 * not.
 *
 * @param value_ptr pointer to the oldest_value in the circular buffer
 */
template <typename T>
void HelperPrintC(T* value_ptr) {
  if (value_ptr) {
    std::cout << "Oldest Values in Buffer is: " << *value_ptr << std::endl;
  } else {
    std::cout << "Empty Buffer. Please add elements." << std::endl;
  }
}

int main() {
  CircularBufferDeque<char> cb(3);
  cb.PutC('a');
  HelperPrintC(cb.GetC());
  cb.PutC('b');
  HelperPrintC(cb.GetC());
  cb.PutC('c');
  HelperPrintC(cb.GetC());
  HelperPrintC(cb.GetC());
  HelperPrintC(cb.GetC());
  cb.PutC('d');
  cb.PutC('e');
  cb.PutC('f');
  cb.PutC('g');
  cb.PutC('h');
  cb.PutC('i');
  cb.PutC('j');
  HelperPrintC(cb.GetC());
  HelperPrintC(cb.GetC());
  HelperPrintC(cb.GetC());
  HelperPrintC(cb.GetC());

}