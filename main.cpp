#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
#include "btree.cpp"
using namespace std;

int main(int argc, char* argv[])
{
  ArgumentManager am(argc, argv);
  string ifile = am.get("input"); //get the filename of argument name "input"
  string cfile = am.get("command"); // get the filename of argument name "command"
  string ofile = am.get("output"); //get the filename of argument name "output"
  ifstream input(ifile);
  ifstream command(cfile);
  ofstream output(ofile);

  int vals, degree, level;
  string str;

  command.ignore(7);
  command >> degree;
  cout << degree << endl;
  btree<int>tree(degree);

  while(input >> vals) {
    tree.insert(vals);
    //cout << vals << endl;
  }
  while(command.ignore(256, '\n') && command >> str) {
    if(str.empty()) {
      continue;
    }
    if(str[0] == 'I') {
      tree.levelCall(output, -1);
      continue;
    } else {
      command.ignore(1);
      command >> level;
      tree.levelCall(output, level);
    }
  }

  return 0;
} 