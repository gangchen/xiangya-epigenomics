#ifndef GENES_UCSC_H
#define GENES_UCSC_H

#include<vector>
#include<fstream>
#include "gene.h"
#include "util.h"

using namespace std;

class genes_ucsc{
 public:
  vector <gene> genes;
  genes_ucsc(char *);
};


genes_ucsc::genes_ucsc(char * filename){
  ifstream inputFile(filename);
  string strGene;
  vector<string> fields;
  int curLine = 0;

  if(!inputFile) cerr << "Cannot open UCSC Genes file" << endl;

  if(inputFile.is_open()){
    while(inputFile.good()){
      getline(inputFile, strGene);
      curLine++;
      fields = util::strsplit(strGene, "\t");
      if(curLine > 1){
	gene g = gene(atoi(fields[3].c_str()),
		      atoi(fields[4].c_str()),
		      fields[1],
		      fields[0]);
	genes.push_back(g);
      }
    }
  }
  

  inputFile.close();
}

#endif
