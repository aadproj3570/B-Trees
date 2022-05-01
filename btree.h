#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
struct node {
  T level;
  node<T>* par;
  vector<T> data;
  vector<node<T>*> next;
  node(){level = 1; par = nullptr;}
};

template <typename T>
class btree {
  private:
    node<T>* root;
    T deg;
    bool insert(T val, node<T>* cu);
    void split(node<T>* l);
    void addLevel(node<T>* cu, T level);
    void levelCall(ostream& out, node<T>* cu);
    void traverse(ostream& out, T level, node<T>* cu);
    void inorder(ostream& out, node<T>* cu);

  public:
    btree(int d){root = nullptr; deg = d;}
    bool empty(){return root == nullptr;}
    bool insert(T val);
    T height();
    void print_height(ostream& out);
    void levelCall(ostream& out, T level);

};