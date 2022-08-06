/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2022-08
 * Last Edit Date: 2022-08
 *
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *dummyhead = new ListNode();
    ListNode *curr = dummyhead;

    int carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
      int x = (l1) ? l1->val : 0;
      int y = (l2) ? l2->val : 0;
      const int sum = x + y + carry;
      curr->next = new ListNode(sum % 10);
      curr = curr->next;
      carry = sum / 10;
      l1 = l1 ? l1->next : nullptr;
      l2 = l2 ? l2->next : nullptr;
    }
    return dummyhead->next;
  }
};
