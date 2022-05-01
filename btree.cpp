#include <iostream>
#include <string>
#include "btree.h"
#include <cmath>
using namespace std;

template <typename T>
bool btree<T>::insert(T v) {
  
  if(empty()) {
    root = new node<T>();
    root->data.push_back(v);
    root->next.push_back(nullptr);
    root->next.push_back(nullptr);
    return true;
  }
  return insert(v, root);
  
}
template <typename T>
bool btree<T>::insert(T v, node<T>* cur) {
  
  int idx = 0;
  while(idx < cur->data.size() && v > cur->data[idx]) {
    idx++;
  }
  if(idx < cur->data.size() && v == cur->data[idx]) {
    return false;
  }
  if(cur->next[idx]) {
    return insert(v, cur->next[idx]);
  }
  cur->data.insert(cur->data.begin() + idx, v);
  cur->next.push_back(nullptr);
  
  if(cur->next.size() > deg) {
    split(cur);
  }
  return true;
}
template <typename T>
void btree<T>::split(node<T>* left) {
  
  int idx = left->data.size() / 2 + left->data.size() % 2 - 1;
  int val = left->data[idx];
  
  node<T>* right = new node<T>();
  
  right->data.insert(right->data.begin(), left->data.begin() + idx + 1, left->data.end());
  right->next.insert(right->next.begin(), left->next.begin() + idx + 1, left->next.end());
  right->level = left->level;
  left->data.erase(left->data.begin() + idx, left->data.end());
  left->next.erase(left->next.begin() + idx + 1, left->next.end());
  
  for(int i = 0; i < right->next.size(); i++) {
    if(right->next[i]) {
      right->next[i]->par = right;
    }
  }
  if(left == root) {
    root = new node<T>();
    root->data.push_back(val);
    root->next.push_back(left);
    root->next.push_back(right);
    left->par = root;
    right->par = root;
    addLevel(root, 1);
  } else {
    right->par = left->par;
    idx = 0;
    while(left->par->next[idx] != left) {
        idx++;
    }
    left->par->data.insert(left->par->data.begin() + idx, val);
    left->par->next.insert(left->par->next.begin() + idx + 1, right);
    if(left->par->next.size() > deg) {
      split(left->par);
    }
  }
  
}
template <typename T>
void btree<T>::addLevel(node<T>* cur, T level) {
  
  cur->level = level;
  level++;
  if(cur->next[0]) {
    for(int i = 0; i < cur->next.size(); i++) {
      addLevel(cur->next[i], level);
    }
  }
  return;
}

template <typename T>
T btree<T>::height() {
  
  if(empty()) {
    return 0;
  }
  node<T>* cur = root;
  while(cur->next[0]) {
    cur = cur->next[0];
  }
  return cur->level;
  
}

template <typename T>
void btree<T>::print_height(ostream& out) {
  
  out << "Height=" << height() << endl;
  
}

template <typename T>
void btree<T>::levelCall(ostream& out, T level) {

  if(level == -1) {
    inorder(out, root);
    cout << endl;
    out << endl;
    return;
  }
  if(empty() || level > height() || level == 0) {
    cout << "empty";
    out << "empty";
  } else {
    traverse(out, level, root);
  }
  cout << endl;
  out << endl;
  return;
  
}
template <typename T>
void btree<T>::traverse(ostream& out, T level, node<T>* cur) {
  if (cur->level == level) {
    for(int i = 0; i < cur->data.size(); i++) {
      cout << cur->data[i] << " ";
      out << cur->data[i] << " ";
    }
  } else {
    for(int i = 0; i < cur->next.size(); i++)
      traverse(out, level, cur->next[i]);
  }
  return;
}
template <typename T>
void btree<T>::inorder(ostream& out, node<T>* cur) {

  if(cur == nullptr) {
    return;
  }
  int i;
  for (i = 0; i < cur->data.size(); i++) {
    if(cur != nullptr) {
      inorder(out, cur->next[i]);
    }
    cout << cur->data[i] << " ";
    out << cur->data[i] << " ";
  }
  if(cur != nullptr) {
    inorder(out, cur->next[i]);
  }
  
}