#ifndef __GENE_H
#define __GENE_H

#include "common.h"
#define CHROMOSOME_COUNT 25

/* CpG Islands*/
typedef struct Cpg{
	long from;		/*	from position */
	long to;		/*	to position */
	int spanCount;		/*	the number of tss which is spanned by one CpG	*/
}Cpg;

typedef struct CpgArray{
	Cpg *cpgs;
	long capacity;
	long length;	
}CpgArray;

typedef struct Tss{
	long position; /* tss position*/
}Tss;

typedef struct TssArray{
	Tss * tss;
	long capacity;
	long length;
}TssArray;

typedef struct Gene{
	char name[20];	/* the name of Gene*/
	long start;
	long end;
	long cpgCount;		/* the number of CpG islands in one Gene */
	long tssCount;		/* the number of tss in one Gene */
	Tss firstTss;		/* the first tss in gene*/
	CpgArray cpgArray;		/* CpG���� */
	TssArray tssArray;
}Gene;

typedef struct GeneArray{
	Gene * genes;	/* �����ַ*/
	long capacity;	/* ���������*/
	long length;	/*	��ǰ��ʹ�õ�����*/
}GeneArray;

typedef struct Chromosome{
	char name[10];		/* the name of chromosome */
	long geneCount;		/* the number of genes in one Chromosome */
	long cpgCount;		/* the number of CpG islands in one Chromosome */
	long tssCount;		/* the number of tss in one Chromosome */
	GeneArray geneArray;/* �������� */
	CpgArray cpgArray;	
}Chromosome;

extern Chromosome chromosomes[CHROMOSOME_COUNT];/*24�� 0�ŵ�Ԫ����*/

int init();

/* process data according to your intention*/
int processGene(GBuff *gb);

void print_chromosomes();
int getChromosomeIndex(char *p);
void print_Total();

#endif