#ifndef GENE_H
#define GENE_H

#include <string>
#include <algorithm>
#include "cpgs.h"

using namespace std;



class gene{
  int start,end;
  string name,chrom;
  cpgs cpgsInGene;

 public:
  void isCpgInGene(cpg);
  gene(int, int, string, string);
  int getStart(){return start;};
  int getEnd(){return end;};
  string getChrom(){return chrom;};
  string getName(){return name;};
  bool operator < (const gene);
  int findCpgs(cpgs);
};

gene::gene(int geneStart, int geneEnd, string geneChrom, string geneName){
  if(geneStart > geneEnd){
    cerr << "ERROR" << endl;
    exit(1);
  }
  start = geneStart;
  end = geneEnd;
  chrom = geneChrom;
  name = geneName;
}

bool gene::operator < (const gene g){
  return(start < g.start);
}

void gene::isCpgInGene(cpg c){
  if(c.getChrom() == chrom){
    if(c.getChromStart() < end || c.getChromEnd() > start){
      cpgsInGene.push(c);
    }
  }
}

int gene::findCpgs(cpgs cs){
  vector<cpg>::iterator it;
  for(it = cs.cpgList.begin(); it != cs.cpgList.end(); it++){
    if(it->getChrom() == chrom){
      if((it->getChromStart() > start && it->getChromStart() < end) ||
	 (it->getChromEnd() < end && it->getChromEnd() > start) ||
	 (it->getChromEnd() < end && it->getChromStart() > start) 
	 ){
	cout << name << "\t"
	     << chrom << "\t"
	     << start << "\t"
	     << end << "\t"
	     << it->getChromStart() << "\t" 
	     << it->getChromEnd() << "\t"
	     << it->getChrom() << endl;
      }
    }
  }
  return 0;
}


#endif
