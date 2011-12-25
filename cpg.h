#ifndef CPG_H
#define CPG_H

#include <string>

using namespace std;

class cpg{
  int length, num, chromStart, chromEnd;
  string chrom;
public:
  cpg(int,int,int,int,string);
  int getLength(){return length;};
  int getNum(){return num;};
  int getChromStart(){return chromStart;};
  int getChromEnd(){return chromEnd;};
  string getChrom(){return chrom;};
};

cpg::cpg(int cpgLength, int cpgNum, int cpgChromStart, int cpgChromEnd, string cpgChrom){
    length = cpgLength;
    cpgNum = cpgNum;
    chromStart = cpgChromStart;
    chromEnd = cpgChromEnd;
    chrom = cpgChrom;
}
#endif
