#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "cpg_ucsc.h"
#include "genes_ucsc.h"
#include "tss_dbtss.h"


using namespace std;

int main(int argc, char * argv[]){
  cpg_ucsc cpgs = cpg_ucsc(argv[1]);
  cout << "CpG Done" << endl;
  
  /*for(int i = 0; i < 1000; i++)
    cout << cpgs.cpgList.cpgList[i].getChrom() 
    << ":" << cpgs.cpgList.cpgList[i].getChromStart()<< endl;*/

  /*tss_dbtss tsses = tss_dbtss(argv[2]);
  cout << "TSS Done" << endl;

  for(int i = 0; i < 40; i++)
    cout << tsses.tssList.tssList[i].getChrom()
    << ":" << tsses.tssList.tssList[i].getPos() << endl;*/

  
  genes_ucsc genes = genes_ucsc(argv[2]);
  cout << "Genes Done" << endl;
  /*for(int i = 0; i < 4; i++)
    cout << genes.genes[0].getChrom() 
    << ":" << genes.genes[i].getStart() << endl;*/
  
  //cout << genes.genes[1].findCpgs(cpgs.cpgList).cpgList.length() << endl;
  vector<gene>::iterator it;
  for(it = genes.genes.begin(); it != genes.genes.end(); it++){
    it->findCpgs(cpgs.cpgList);
  }

  return 0;
}
