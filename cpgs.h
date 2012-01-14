#ifndef CPGS_H
#define CPGS_H

#include <vector>
#include <string>
#include <algorithm>
#include "cpg.h"
#include "util.h"

using namespace std;

class cpgs{
 public:
  vector <cpg> cpgList;
  void sort();
  cpgs();
  void push(cpg);
};

cpgs::cpgs(){
  
}

void cpgs::sort(){
  std::sort(cpgList.begin(),cpgList.end());
}

void cpgs::push(cpg c){
  cpgList.push_back(c);
}

#endif
