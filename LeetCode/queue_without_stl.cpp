/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2022-08
 * Last Edit Date: 2022-08
 *
 */

#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

template <typename T> struct Node {
  Node *prev;
  Node *next;
  T val{};
  Node() : prev(nullptr), next(nullptr) {}
  Node(Node *prev, Node *next, T val) : prev(prev), next(next), val(val) {}
};

template <typename T> class Queue {
public:
  Queue() {
    prev_head = new Node<T>();
    prev_dangling = prev_head;
  }

  void push_front(const T &val) {
    const std::lock_guard<std::mutex> lock(mtx);
    front_head = new Node<T>(prev_head, nullptr, val);
    prev_head->next = front_head;
    prev_head = prev_head->next;
    if (back_head == nullptr) {
      back_head = front_head;
    }
    front_head = front_head->next;
  }

  T back() const { return back_head->val; }

  void pop_back() {
    const std::lock_guard<std::mutex> lock(mtx);
    Node<T> *temp = back_head;
    back_head = back_head->next;
    delete temp;
  }

  void print(bool reverse = false) const {
    recursive_print(back_head, reverse);
  }

  ~Queue() {
    delete prev_dangling;
    while (back_head) {
      Node<T> *temp = back_head;
      back_head = back_head->next;
      delete temp;
    }
  }

private:
  Node<T> *front_head = nullptr;
  Node<T> *prev_head = nullptr;
  Node<T> *back_head = nullptr;
  Node<T> *prev_dangling = nullptr;
};

template <typename T> void recursive_print(Node<T> *head, const bool reverse) {
  if (head) {
    if (!reverse) {
      std::cout << head->val << std::endl;
    }
    recursive_print(head->next, reverse);
    if (reverse) {
      std::cout << head->val << std::endl;
    }
  }
}

void add_elements(Queue<int> &q) {
  for (int i = 0; i < 10; ++i) {
    q.push_front(i);
  }
}

int main(void) {
  Queue<int> q;
  std::thread thd1(add_elements, std::ref(q));
  std::thread thd2(add_elements, std::ref(q));
  thd1.join();
  thd2.join();
  q.print();

  return 0;
}
