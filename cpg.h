#ifndef CPG_H
#define CPG_H

class cpg{
  int length, num, chromStart, chromEnd, chrom;
public:
  cpg(int,int,int,int,int);
  int getLength(){return length;};
  int getNum(){return num;};
  int getChromStart(){return chromStart;};
  int getChromEnd(){return chromEnd;};
  int getChrom(){return chrom;};
};

cpg::cpg(int cpgLength, int cpgNum, int cpgChromStart, int cpgChromEnd, int cpgChrom){
    length = cpgLength;
    cpgNum = cpgNum;
    chromStart = cpgChromStart;
    chromEnd = cpgChromEnd;
    chrom = cpgChrom;
}
#endif
