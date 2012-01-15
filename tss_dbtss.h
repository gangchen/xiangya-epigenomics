#ifndef TSS_DBTSS_H
#define TSS_DBTSS_H

#include <vector>
#include <fstream>
#include "tsses.h"
#include "util.h"

using namespace std;

class tss_dbtss{
 public:
  tsses tssList;
  tss_dbtss(char *);
};

tss_dbtss::tss_dbtss(char * filename){
  ifstream inputFile(filename);
  string strTss;
  vector<string> fields;
  int curLine = 0;

  if(!inputFile) cerr << "Cannot open DBTSS TSS file" << endl;

  if(inputFile.is_open()){
    while(inputFile.good()){
      getline(inputFile, strTss);
      curLine++;
      fields = util::strsplit(strTss, "\t");
      if(curLine > 1){
	tss t = tss(atoi(fields[5].c_str()),//position
		    fields[3]); // chromosome
	tssList.push(t);
      }
    }
  }
  
  tssList.sort();
  inputFile.close();
}


#endif
