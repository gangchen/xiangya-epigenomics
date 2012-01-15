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
  bool operator < (const tss &) const;
};

tss::tss(int tssPos, string tssChrom){
  pos = tssPos;
  chrom = tssChrom;
}

bool tss::operator < (const tss &t) const{
  if(chrom < t.chrom){
    return true;
  }else if(chrom > t.chrom){
    return false;
  }else if(chrom == t.chrom){
    return pos < t.pos;
  }

  cerr << "ERROR" << endl;
  return NULL;
}

#endif
