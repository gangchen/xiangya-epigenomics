#ifndef GENE_H
#define GENE_H

#include <string>

using namespace std;

class gene{
  int start,end,chrom;
  string name;

public:
  gene(int, int, int, string);
  int getStart(){return start;};
  int getEnd(){return end;};
  int getChrom(){return chrom;};
  string getName(){return name;};
  bool operator < (const gene);
};

gene::gene(int geneStart, int geneEnd, int geneChrom, string geneName){
  start = geneStart;
  end = geneEnd;
  chrom = geneChrom;
  name = geneName;
}

bool gene::operator < (const gene g){
  return(start < g.start);
}

#endif
