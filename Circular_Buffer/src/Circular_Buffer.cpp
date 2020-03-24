/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 *
 * @brief Implementation of Circular Buffer using a fixes size vector.
 * When the buffer is full the oldest element is overwritten.
 *
 */
#include <iostream>
#include <vector>

template <typename T>
class CircularBuffer {
 public:
  /**
   * @brief Initializing the size of the circular buffer
   *
   * @param[in] x size of circular buffer to be set
   */
  CircularBuffer(int x);
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
  /**
   * @brief function to rest the class variables to deafult value.
   * this happens when buffer is empty.
   *
   */
  void Reset();

 private:
  /**
   * @brief maximum size of circular buffer
   *
   */
  int max_sz = 0;
  /**
   * @brief head of the circular buffer. The head is the oldest element in the
   * circular buffer.
   */
  int head;
  /**
   * @brief the last element of the buffer. It is the most recently added
   * element in the buffer
   */
  int tail;
  /**
   * @brief current size of the buffer
   *
   */
  int sz;
  /**
   * @brief vector which makes the circular buffer.
   *
   */
  std::vector<T> vector_buffer;
};

template <typename T>
CircularBuffer<T>::CircularBuffer(int x) : max_sz(x) {
  vector_buffer.assign(max_sz, 0);
  Reset();
}

template <typename T>
void CircularBuffer<T>::PutC(T var) {
  if (sz == 0) {
    Reset();
  }
  tail = (tail + 1) % max_sz;
  vector_buffer[tail] = var;
  if (tail == head && sz != 0) {
    head = (head + 1) % max_sz;
  }
  sz = (sz >= max_sz) ? max_sz : ++sz;
}

template <typename T>
T* CircularBuffer<T>::GetC() {
  if (sz == 0) {
    return nullptr;
  }
  --sz;
  const int temp = head;
  head = (head + 1) % max_sz;
  return &vector_buffer[temp];
}

template <typename T>
void CircularBuffer<T>::Reset() {
  head = 0;
  tail = -1;
  sz = 0;
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
  CircularBuffer<char> cb(3);
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