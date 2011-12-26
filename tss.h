#ifndef TSS_H
#define TSS_H

using namespace std;

class tss{
  int pos;
  string chrom;
public:
  tss(int, string);
  int getPos(){return pos;};
  string getChrom(){return chrom;};
  bool operator < (const tss);
};

tss::tss(int tssPos, string tssChrom){
  pos = tssPos;
  chrom = tssChrom;
}

bool tss::operator < (const tss t){
  return(pos < t.pos);
}

#endif
