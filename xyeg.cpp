#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "cpg_ucsc.h"
#include "genes_ucsc.h"
#include "tss_dbtss.h"


using namespace std;

int main(int argc, char * argv[]){
  cpg_ucsc cpgs = cpg_ucsc(argv[1]);
  cout << "CpG Done" << endl;
  cout << cpgs.cpgs[0].getChromStart()<< endl;
  cout << cpgs.cpgs[1].getChromStart()<< endl;
  cout << (cpgs.cpgs[1] < cpgs.cpgs[0]) << endl;
  //genes_ucsc genes = genes_ucsc(argv[2]);
  //cout << "Genes Done" << endl;
  //tss_dbtss tsses = tss_dbtss(argv[3]);
  //cout << "TSS Done" << endl;

  //cout << tsses.tsses[0].getChrom() << endl;
  return 0;
}
