#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

using namespace std;

class util{
  static const int BIG = 10000;
public:
  static vector<string> strsplit(string str, string del){
    unsigned end=0;
    vector<string> fields;
    while(1){
      end = str.find(del);
      if(end > str.size()){
	fields.push_back(str);
	break;
      }
      fields.push_back(str.substr(0, end));
      str = str.substr(end+1, str.size());
    }
    return fields;
  }
};
#endif
