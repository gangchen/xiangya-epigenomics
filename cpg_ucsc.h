#ifndef CPG_UCSC_H
#define CPG_UCSC_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "cpg.h"
#include "util.h"

using namespace std;

class cpg_ucsc{
public:
  vector <cpg> cpgs;
  cpg_ucsc(char *);
};

cpg_ucsc::cpg_ucsc(char* filename){
  string strCpg;
  vector<string> fields;
  ifstream  inputFile(filename);
  int curLine = 0;

  if(!inputFile) cerr << "Cannot open UCSC CpG file" << endl;
  
  if(inputFile.is_open()){
    while(inputFile.good()){
      getline(inputFile, strCpg);
      curLine++;
      fields = util::strsplit(strCpg, "\t");
      if(curLine > 1){
	cpg c = cpg(atoi(fields[5].c_str()), 
		    atoi(fields[6].c_str()),
		    atoi(fields[2].c_str()),
		    atoi(fields[4].c_str()),
		    atoi(fields[1].c_str()));
	cpgs.push_back(c);
      }
    }
  }

  inputFile.close();
}
#endif
