#ifndef TSSES_H
#define TSSES_H

#include <vector>
#include <algorithm>
#include "tss.h"
#include "util.h"

class tsses{
 public:
  vector <tss> tssList;
  void sort();
  tsses();
  void push(tss);
};

tsses::tsses(){
}

void tsses::sort(){
  std::sort(tssList.begin(), tssList.end());
}

void tsses::push(tss t){
  tssList.push_back(t);
}

#endif
