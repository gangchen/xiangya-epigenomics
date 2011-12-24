#ifndef TSS_H
#define TSS_H

using namespace std;

class tss{
  int pos, chrom;
public:
  tss(int, int);
  int getPos(){return pos;};
  int getChrom(){return chrom;};
};

tss::tss(int tssPos, int tssChrom){
  pos = tssPos;
  chrom = tssChrom;
}

#endif
